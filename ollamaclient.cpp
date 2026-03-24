#include "ollamaclient.h"

OllamaClient::OllamaClient(QObject *parent) : QObject(parent), trybAnalizy(false) {
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &OllamaClient::onReplyFinished);
}

void OllamaClient::askAI(const QString &userInput) {
    trybAnalizy = false;
    QUrl url("http://localhost:11434/api/generate");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["model"] = "llama3";
    json["system"] = "You are a Windows CMD expert. If the user prompt is nonsense, just a number, or not a valid system task, return EXACTLY the word: INVALID_TASK. Otherwise, return ONLY the raw command. No talk.";
    json["prompt"] = userInput;
    json["stream"] = false;

    manager->post(request, QJsonDocument(json).toJson());
}

void OllamaClient::analyzeResult(const QString &cmdOutput) {
    trybAnalizy = true;
    QUrl url("http://localhost:11434/api/generate");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["model"] = "llama3";
    json["system"] = "Jesteś asystentem systemowym. Otrzymasz surowy wynik z konsoli CMD. Przeanalizuj go i napisz po polsku zwięzłe, proste podsumowanie dla użytkownika. Skup się na najważniejszych wnioskach. Używaj formatowania HTML (np. <b>pogrubienia</b>). Nie pokazuj komend, tylko diagnozę.";
    json["prompt"] = cmdOutput;
    json["stream"] = false;

    manager->post(request, QJsonDocument(json).toJson());
}

void OllamaClient::onReplyFinished(QNetworkReply *reply) {
    if (reply->error()) {
        emit errorOccurred("Błąd połączenia z Ollama! Upewnij się, że usługa działa w tle.");
        reply->deleteLater();
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QString response = doc.object().value("response").toString().trimmed();

    if (trybAnalizy) {
        emit analysisReady(response);
    } else {
        emit resultReady(response);
    }

    reply->deleteLater();
}