#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setStyleSheet(
        "QMainWindow { background-color: #1e1e2e; }"
        "QLineEdit { background-color: #313244; color: #cdd6f4; padding: 10px; border-radius: 6px; font-size: 14px; border: 1px solid #45475a; }"
        "QPushButton { background-color: #89b4fa; color: #11111b; font-weight: bold; padding: 10px; border-radius: 6px; }"
        "QPushButton:hover { background-color: #b4befe; }"
        "QPushButton:disabled { background-color: #45475a; color: #a6adc8; }"
        "QTextEdit { background-color: #11111b; color: #a6e3a1; font-family: Consolas; font-size: 14px; padding: 10px; border-radius: 6px; border: 1px solid #45475a; }"
        );

    connect(ui->poleTekstowe, &QLineEdit::returnPressed, this, &MainWindow::on_przyciskWykonaj_clicked);
    connect(ui->przyciskCzysc, &QPushButton::clicked, this, &MainWindow::on_przyciskCzysc_clicked);
    connect(ui->przyciskRaport, &QPushButton::clicked, this, &MainWindow::on_przyciskRaport_clicked);

    watekAI = new QThread(this);
    klientAI = new OllamaClient();

    klientAI->moveToThread(watekAI);

    connect(klientAI, &OllamaClient::resultReady, this, &MainWindow::obsluzOdpowiedzAI);
    connect(klientAI, &OllamaClient::analysisReady, this, &MainWindow::obsluzAnalizeAI);
    connect(klientAI, &OllamaClient::errorOccurred, this, &MainWindow::obsluzBladAI);
    connect(watekAI, &QThread::finished, klientAI, &QObject::deleteLater);

    watekAI->start();
}

MainWindow::~MainWindow()
{
    watekAI->quit();
    watekAI->wait();
    delete ui;
}

void MainWindow::on_przyciskWykonaj_clicked()
{
    QString polecenie = ui->poleTekstowe->text();
    if(polecenie.isEmpty()) return;

    ui->oknoWynikow->append("<br><b>Wysyłam prośbę do AI:</b> " + polecenie + "...");
    ui->przyciskWykonaj->setEnabled(false);

    QMetaObject::invokeMethod(klientAI, "askAI", Q_ARG(QString, polecenie));
}

void MainWindow::on_przyciskCzysc_clicked()
{
    ui->oknoWynikow->clear();
}

void MainWindow::on_przyciskRaport_clicked()
{
    QString domyslnaNazwa = "Raport_AI_" + QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss") + ".html";
    QString nazwaPliku = QFileDialog::getSaveFileName(this, "Zapisz Raport", domyslnaNazwa, "Pliki HTML (*.html);;Pliki tekstowe (*.txt)");

    if(nazwaPliku.isEmpty()) return;

    QFile plik(nazwaPliku);
    if(plik.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream strumien(&plik);
        if(nazwaPliku.endsWith(".html")) {
            strumien << ui->oknoWynikow->toHtml();
        } else {
            strumien << ui->oknoWynikow->toPlainText();
        }
        plik.close();
        QMessageBox::information(this, "Sukces", "Raport został zapisany pomyślnie!");
    } else {
        QMessageBox::warning(this, "Błąd", "Nie udało się zapisać pliku.");
    }
}

void MainWindow::obsluzBladAI(const QString &blad)
{
    ui->oknoWynikow->append("<font color='#f38ba8'>❌ BŁĄD:</font> " + blad);
    ui->przyciskWykonaj->setEnabled(true);
}

void MainWindow::obsluzOdpowiedzAI(const QString &komenda)
{
    if(komenda.contains("INVALID_TASK")) {
        ui->oknoWynikow->append("<font color='#f9e2af'>⚠️ Uwaga:</font> To nie wygląda na sensowną komendę. Spróbuj napisać to inaczej.");
        ui->przyciskWykonaj->setEnabled(true);
        return;
    }

    QStringList komendySieciowe = {"ping", "tracert", "curl", "wget", "nslookup", "ipconfig"};
    bool toKomendaSieciowa = false;
    for(const QString &k : komendySieciowe) {
        if(komenda.contains(k, Qt::CaseInsensitive)) {
            toKomendaSieciowa = true;
            break;
        }
    }

    if(toKomendaSieciowa) {
        QTcpSocket gniazdo;
        gniazdo.connectToHost("8.8.8.8", 53);
        if(!gniazdo.waitForConnected(1000)) {
            ui->oknoWynikow->append("<font color='#f38ba8'>🌐 BŁĄD SIECI:</font> Brak połączenia z Internetem. Zablokowano próbę użycia komendy: <b>" + komenda + "</b>");
            ui->przyciskWykonaj->setEnabled(true);
            return;
        }
        gniazdo.close();
    }

    ui->oknoWynikow->append("<font color='#89b4fa'>✅ AI wygenerowało komendę:</font> " + komenda);

    QProcess *proces = new QProcess(this);

    connect(proces, &QProcess::finished, [this, proces]() {
        QString wynik = QString::fromLocal8Bit(proces->readAllStandardOutput());
        QString bledyTerminala = QString::fromLocal8Bit(proces->readAllStandardError());

        if(!wynik.isEmpty()) {
            QString htmlWynik = wynik;
            htmlWynik = htmlWynik.toHtmlEscaped().replace("\n", "<br>");
            ui->oknoWynikow->append("<b>Surowy Wynik:</b><br>" + htmlWynik);

            ui->oknoWynikow->append("<br><font color='#f9e2af'><i>⏳ AI analizuje ten wynik, poczekaj...</i></font>");
            QMetaObject::invokeMethod(klientAI, "analyzeResult", Q_ARG(QString, wynik));
        } else {
            ui->przyciskWykonaj->setEnabled(true);
        }

        if(!bledyTerminala.isEmpty()) {
            bledyTerminala = bledyTerminala.toHtmlEscaped().replace("\n", "<br>");
            ui->oknoWynikow->append("<font color='#f38ba8'>Uwagi z systemu:</font><br>" + bledyTerminala);
            if(wynik.isEmpty()) ui->przyciskWykonaj->setEnabled(true);
        }

        proces->deleteLater();
    });

    proces->start("cmd.exe", QStringList() << "/c" << komenda);
}

void MainWindow::obsluzAnalizeAI(const QString &analiza)
{
    ui->oknoWynikow->append("<font color='#a6e3a1'><b>🧠 Diagnoza AI:</b></font><br>" + analiza + "<br>");
    ui->przyciskWykonaj->setEnabled(true);
}