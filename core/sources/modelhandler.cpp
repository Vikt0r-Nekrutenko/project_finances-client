#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "modelhandler.hpp"

RemoteStatus DataModelHandler::get(const std::string &additionalPath)
{
    QNetworkReply *reply = sendCRUDRequest(additionalPath, {}, "GET");
    RemoteStatus status = replyHandler(reply, "Get request successfully!");
    if(status == RemoteStatus::Failure)
        return RemoteStatus::Failure;

    QJsonDocument jsonResponse = QJsonDocument::fromJson(QString(reply->readAll()).toUtf8());

    QJsonArray array = jsonResponse.array();
    parseJsonArray(array);

    return RemoteStatus::Success;
}
