#include <QJsonObject>
#include <QJsonDocument>
#include "debtmodel.hpp"

DebtModel::DebtModel(int id, const QString &name, int amount)
    : mName{name}, mId{id}, mAmount{amount} {}

void DebtModel::create()
{
    QJsonObject newDebt {
        {"id", mId },
        {"name", mName },
        {"amount", mAmount },
    };

    QNetworkReply *reply = sendCRUDRequest("debts/", newDebt, "POST");
    replyHandler(reply, "Operation added successfully!");
}

void DebtModel::read()
{
    QNetworkReply *reply = sendCRUDRequest("debts/" + QString::number(mId) + '/', {}, "GET");
    replyHandler(reply, "Debt read successfully!");

    QJsonDocument jsonResponse = QJsonDocument::fromJson(QString(reply->readAll()).toUtf8());
    QJsonObject object = jsonResponse.object();
    parseJsonObject(object);
}

void DebtModel::update()
{
    QJsonObject selectedDebt {
        {"id", mId },
        {"name", mName },
        {"amount", mAmount },
    };

    QNetworkReply *reply = sendCRUDRequest("debts/" + QString::number(mId) + '/', selectedDebt, "PUT");
    replyHandler(reply, "Debt updated successfully!");
}

void DebtModel::remove()
{
    QNetworkReply *reply = sendCRUDRequest("debts/" + QString::number(mId) + '/', {}, "DELETE");
    replyHandler(reply, "Debt delete successfully!");
}

void DebtModel::parseJsonObject(const QJsonObject &object)
{
    mId = object["id"].toInt();
    mName = object["name"].toString();
    mAmount = object["amount"].toInt();
}

const QString &DebtModel::name() const
{
    return mName;
}

int DebtModel::id() const
{
    return mId;
}

int DebtModel::amount() const
{
    return mAmount;
}

void DebtModel::increase(int amount)
{
    mAmount += amount;
}

void DebtModel::decrease(int amount)
{
    mAmount -= amount;
}
