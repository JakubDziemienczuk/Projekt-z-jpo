#ifndef OLLAMACLIENT_H
#define OLLAMACLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>

/**
 * @class OllamaClient
 * @brief Klasa odpowiedzialna za komunikację z modelem AI (Ollama) przez REST API.
 * * Umożliwia asynchroniczne wysyłanie zapytań do modelu LLM (np. Llama 3)
 * w celu generowania komend systemowych oraz analizowania ich wyników.
 */
class OllamaClient : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Konstruktor klasy OllamaClient.
     * @param parent Wskaźnik na obiekt nadrzędny.
     */
    explicit OllamaClient(QObject *parent = nullptr);

public slots:
    /**
     * @brief Wysyła zapytanie do AI w celu wygenerowania komendy.
     * @param userInput Zapytanie wprowadzone przez użytkownika w GUI.
     */
    void askAI(const QString &userInput);

    /**
     * @brief Wysyła surowy wynik z konsoli do AI w celu uzyskania diagnozy.
     * @param cmdOutput Surowy tekst zwrócony przez proces CMD.
     */
    void analyzeResult(const QString &cmdOutput);

signals:
    /**
     * @brief Sygnał emitowany, gdy AI wygeneruje poprawną komendę.
     * @param command Wygenerowana komenda jako tekst.
     */
    void resultReady(const QString &command);

    /**
     * @brief Sygnał emitowany, gdy AI zakończy analizę wyniku (streszczenie).
     * @param analysis Sformatowana diagnoza gotowa do wyświetlenia.
     */
    void analysisReady(const QString &analysis);

    /**
     * @brief Sygnał emitowany w przypadku błędu (np. braku połączenia z Ollamą).
     * @param msg Komunikat błędu do wyświetlenia użytkownikowi.
     */
    void errorOccurred(const QString &msg);

private slots:
    /**
     * @brief Wewnętrzny slot obsługujący odpowiedź z serwera REST API.
     * @param reply Obiekt zawierający odpowiedź sieciową.
     */
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager; ///< Menedżer zapytań sieciowych
    bool trybAnalizy;               ///< Flaga określająca, czy aktualne zapytanie to diagnoza
};

#endif // OLLAMACLIENT_H