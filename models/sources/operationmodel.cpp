#include <QJsonObject>
#include <QJsonDocument>

#include "operationmodel.hpp"

OperationModel::OperationModel(int id, const std::string &date, const std::string &deposit, int amount, const std::string &category)
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

void OperationModel::update()
{
    QJsonObject selectedOperation {
        {"id", mId },
        {"date", mDate },
        {"deposit", mDeposit },
        {"amount", mAmount },
        {"category", mCategory },
    };

    QNetworkReply *reply = sendCRUDRequest("operations/" + QString::number(mId) + '/', selectedOperation, "PUT");
    replyHandler(reply, "Operation updated successfully!");
}

void OperationModel::remove()
{
    QNetworkReply *reply = sendCRUDRequest("operations/" + QString::number(mId) + '/', {}, "DELETE");
    replyHandler(reply, "Operation delete successfully!");
}

void OperationModel::parseJsonObject(const QJsonObject &object)
{
    mId = object["id"].toInt();
    mDate = object["date"].toString();
    mDeposit = object["deposit"].toString();
    mAmount = object["amount"].toInt();
    mCategory = object["category"].toString();
}

int OperationModel::id() const
{
    return mId;
}

const std::string &OperationModel::date() const
{
    return mDate;
}

const std::string &OperationModel::deposit() const
{
    return mDeposit;
}

int OperationModel::amount() const
{
    return mAmount;
}

const std::string &OperationModel::category() const
{
    return mCategory;
}
