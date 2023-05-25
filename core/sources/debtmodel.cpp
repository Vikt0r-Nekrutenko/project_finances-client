#include <QJsonObject>
#include <QJsonDocument>
#include "debtmodel.hpp"

DebtModel::DebtModel(int id, const std::string &name, int amount)
    : mName{name}, mId{id}, mAmount{amount} {}

void DebtModel::create()
{
    QJsonObject newDebt {
        {"id", mId },
        {"name", mName.c_str() },
        {"amount", mAmount },
    };

    QNetworkReply *reply = sendCRUDRequest("debts/", newDebt, "POST");
    replyHandler(reply, "Debt added successfully!");
}

void DebtModel::read()
{
    QNetworkReply *reply = sendCRUDRequest("debts/" + std::to_string(mId) + '/', {}, "GET");
    replyHandler(reply, "Debt read successfully!");

    QJsonDocument jsonResponse = QJsonDocument::fromJson(QString(reply->readAll()).toUtf8());
    QJsonObject object = jsonResponse.object();
    parseJsonObject(object);
}

void DebtModel::update()
{
    QJsonObject selectedDebt {
        {"id", mId },
        {"name", mName.c_str() },
        {"amount", mAmount },
    };

    QNetworkReply *reply = sendCRUDRequest("debts/" + std::to_string(mId) + '/', selectedDebt, "PUT");
    replyHandler(reply, "Debt updated successfully!");
}

void DebtModel::remove()
{
    QNetworkReply *reply = sendCRUDRequest("debts/" + std::to_string(mId) + '/', {}, "DELETE");
    replyHandler(reply, "Debt delete successfully!");
}

void DebtModel::parseJsonObject(const QJsonObject &object)
{
    mId = object["id"].toInt();
    mName = object["name"].toString().toStdString();
    mAmount = object["amount"].toInt();
}

void DebtModel::load(std::ifstream &file)
{
    file >> mId >> mName >> mAmount;
    LocalModel::load(file);
}

void DebtModel::save(std::ofstream &file)
{

}

const std::string &DebtModel::name() const
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
