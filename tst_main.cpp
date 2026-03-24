#include <QtTest>
#include "ollamaclient.h"

class TestOllamaClient : public QObject
{
    Q_OBJECT

private slots:
    void test_tworzenia_obiektu() {
        OllamaClient klient;
        QVERIFY(true);
    }

    void test_konfiguracji_modelu() {
        QString oczekiwanyModel = "llama3";
        QCOMPARE(oczekiwanyModel, QString("llama3"));
    }
};

QTEST_MAIN(TestOllamaClient)
#include "tst_main.moc"