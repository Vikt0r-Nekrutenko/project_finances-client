#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "modelhandler.hpp"

void DataModelHandler::get(const QString &additionalPath)
{
    QNetworkReply *reply = sendCRUDRequest(additionalPath, {}, "GET");
    replyHandler(reply, "Get request successfully!");

    QJsonDocument jsonResponse = QJsonDocument::fromJson(QString(reply->readAll()).toUtf8());

    QJsonArray array = jsonResponse.array();
    parseJsonArray(array);
}
