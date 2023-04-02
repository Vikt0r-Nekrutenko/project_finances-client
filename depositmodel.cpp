#include <QJsonObject>
#include <QJsonDocument>

#include "depositmodel.hpp"

DepositModel::DepositModel(const QString &name, int balance)
    : mName{name}, mBalance{balance} {}

void DepositModel::create()
{
    QJsonObject newDepo {
        {"name", mName },
        {"balance", mBalance }
    };

    QNetworkReply *reply = sendCRUDRequest("deposits/", newDepo, Requests[RequestType::POST]);
    replyHandler(reply, "Deposit added successfully!");
}

void DepositModel::read()
{
    QNetworkReply *reply = sendCRUDRequest("deposits/" + mName + '/', {}, Requests[RequestType::GET]);
    replyHandler(reply, "Get request successfully!");

    QJsonDocument jsonResponse = QJsonDocument::fromJson(QString(reply->readAll()).toUtf8());
    QJsonObject object = jsonResponse.object();
    parseJsonObject(object);
}
