/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *poleTekstowe;
    QPushButton *przyciskWykonaj;
    QTextEdit *oknoWynikow;
    QPushButton *przyciskCzysc;
    QPushButton *przyciskRaport;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 514);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        poleTekstowe = new QLineEdit(centralwidget);
        poleTekstowe->setObjectName("poleTekstowe");
        poleTekstowe->setGeometry(QRect(220, 30, 391, 41));
        przyciskWykonaj = new QPushButton(centralwidget);
        przyciskWykonaj->setObjectName("przyciskWykonaj");
        przyciskWykonaj->setGeometry(QRect(530, 80, 81, 31));
        oknoWynikow = new QTextEdit(centralwidget);
        oknoWynikow->setObjectName("oknoWynikow");
        oknoWynikow->setGeometry(QRect(60, 140, 691, 281));
        przyciskCzysc = new QPushButton(centralwidget);
        przyciskCzysc->setObjectName("przyciskCzysc");
        przyciskCzysc->setGeometry(QRect(670, 430, 81, 41));
        przyciskRaport = new QPushButton(centralwidget);
        przyciskRaport->setObjectName("przyciskRaport");
        przyciskRaport->setGeometry(QRect(570, 430, 81, 41));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        poleTekstowe->setText(QString());
        przyciskWykonaj->setText(QCoreApplication::translate("MainWindow", "Zatwierd\305\272", nullptr));
        przyciskCzysc->setText(QCoreApplication::translate("MainWindow", "Wyczy\305\233\304\207", nullptr));
        przyciskRaport->setText(QCoreApplication::translate("MainWindow", "Raport", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
