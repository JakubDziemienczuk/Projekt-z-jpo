#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QProcess>
#include <QTcpSocket>
#include "ollamaclient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief Główna klasa interfejsu graficznego aplikacji.
 * * Zarządza interakcją z użytkownikiem, wyświetlaniem logów oraz wielowątkową
 * komunikacją z klasą OllamaClient. Zabezpiecza przed wykonaniem niebezpiecznych komend.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor okna głównego. Inicjalizuje GUI i wątki.
     * @param parent Wskaźnik na widget nadrzędny.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destruktor okna. Zapewnia bezpieczne zamknięcie wątków działających w tle.
     */
    ~MainWindow();

private slots:
    /**
     * @brief Slot wywoływany po kliknięciu "Wykonaj". Rozpoczyna proces komunikacji z AI.
     */
    void on_przyciskWykonaj_clicked();

    /**
     * @brief Slot wywoływany po kliknięciu "Wyczyść". Czyści główne okno tekstowe.
     */
    void on_przyciskCzysc_clicked();

    /**
     * @brief Slot wywoływany po kliknięciu "Zapisz Raport". Zapisuje konwersację do pliku.
     */
    void on_przyciskRaport_clicked();

    /**
     * @brief Slot obsługujący wykonanie komendy wygenerowanej przez sztuczną inteligencję.
     * @param komenda Komenda systemowa w formacie tekstowym.
     */
    void obsluzOdpowiedzAI(const QString &komenda);

    /**
     * @brief Slot wyświetlający przetłumaczoną analizę wyniku z konsoli CMD.
     * @param analiza Tekst wygenerowany przez AI (diagnoza).
     */
    void obsluzAnalizeAI(const QString &analiza);

    /**
     * @brief Slot wyświetlający komunikaty o błędach zgłoszone przez klienta Ollamy.
     * @param blad Treść błędu.
     */
    void obsluzBladAI(const QString &blad);

private:
    Ui::MainWindow *ui;         ///< Wskaźnik na wygenerowany interfejs użytkownika
    OllamaClient *klientAI;     ///< Instancja klienta komunikującego się z AI
    QThread *watekAI;           ///< Wątek poboczny dla klienta AI (zapobiega blokowaniu GUI)
};
#endif // MAINWINDOW_H