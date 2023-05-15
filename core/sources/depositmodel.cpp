#include <QJsonObject>
#include <QJsonDocument>

#include "depositmodel.hpp"

DepositModel::DepositModel(const std::string &name, int balance)
    : mName{name}, mBalance{balance} {}

void DepositModel::create()
{
    QJsonObject newDepo {
        {"name", mName.c_str() },
        {"balance", mBalance }
    };

    QNetworkReply *reply = sendCRUDRequest("deposits/", newDepo, "POST");
    replyHandler(reply, "Deposit added successfully!");
}

void DepositModel::read()
{
    QNetworkReply *reply = sendCRUDRequest("deposits/" + mName + '/', {}, "GET");
    replyHandler(reply, "Get request successfully!");

    QJsonDocument jsonResponse = QJsonDocument::fromJson(QString(reply->readAll()).toUtf8());
    QJsonObject object = jsonResponse.object();
    parseJsonObject(object);
}

void DepositModel::update()
{
    QJsonObject selectedDeposit {
        {"name", mName.c_str() },
        {"balance", mBalance }
    };

    QNetworkReply *reply = sendCRUDRequest("deposits/" + mName + '/', selectedDeposit, "PUT");
    replyHandler(reply, "Balance updated successfully!");

}

void DepositModel::remove()
{
    QNetworkReply *reply = sendCRUDRequest("deposits/" + mName + '/', {}, "DELETE");
    replyHandler(reply, "Deposit deleted successfully!");
}

void DepositModel::parseJsonObject(const QJsonObject &object)
{
    mName = object["name"].toString().toStdString();
    mBalance = object["balance"].toInt();
}

const std::string &DepositModel::name() const
{
    return mName;
}

int DepositModel::balance() const
{
    return mBalance;
}

void DepositModel::increaseBalance(int amount)
{
    mBalance += amount;
}

void DepositModel::decreaseBalance(int amount)
{
    mBalance -= amount;
}

