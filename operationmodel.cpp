#include <QJsonObject>
#include <QJsonDocument>

#include "operationmodel.hpp"

OperationModel::OperationModel(int id, const QString &date, const QString &deposit, int amount, const QString &category)
    : mDate{date}, mDeposit{deposit}, mCategory{category}, mId{id}, mAmount{amount} {}

void OperationModel::create()
{
    QJsonObject newOperation {
        {"id", mId },
        {"date", mDate },
        {"deposit", mDeposit },
        {"amount", mAmount },
        {"category", mCategory },
    };

    QNetworkReply *reply = sendCRUDRequest("operations/", newOperation, "POST");
    replyHandler(reply, "Operation added successfully!");
}

void OperationModel::read()
{
    QNetworkReply *reply = sendCRUDRequest("operations/" + QString::number(mId) + '/', {}, "GET");
    replyHandler(reply, "Operation read successfully!");

    QJsonDocument jsonResponse = QJsonDocument::fromJson(QString(reply->readAll()).toUtf8());
    QJsonObject object = jsonResponse.object();
    parseJsonObject(object);
}
