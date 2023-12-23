#include <QJsonObject>
#include <QJsonDocument>
#include "debtmodel.hpp"

DebtModel::DebtModel(int id, const std::string &name, int amount)
    : mName{name}, mId{id}, mAmount{amount} {}

DebtModel::DebtModel(int id, const std::string &name, int amount, int version, bool isDeleted)
    : BaseModel{version, isDeleted}, mName{name}, mId{id}, mAmount{amount} { }

void DebtModel::create()
{
    QJsonObject newDebt {
        {"name", mName.c_str() },
        {"amount", mAmount },
    };

    QNetworkReply *reply = sendCRUDRequest("debts/", completeJsonObject(newDebt), "POST");
    RemoteStatus status = replyHandler(reply, "Debt added successfully!");
    mIsForCreate = status == RemoteStatus::Failure ? true : false;

    if(status == RemoteStatus::Success) {
        QJsonDocument jsonResponse = QJsonDocument::fromJson(QString(reply->readAll()).toUtf8());
        QJsonObject object = jsonResponse.object();
        mId = object["id"].toInt();
    }
    delete reply;
}

void DebtModel::read()
{
    QNetworkReply *reply = sendCRUDRequest("debts/" + std::to_string(mId) + '/', {}, "GET");
    replyHandler(reply, "Debt read successfully!");

    QJsonDocument jsonResponse = QJsonDocument::fromJson(QString(reply->readAll()).toUtf8());
    delete reply;
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

    QNetworkReply *reply = sendCRUDRequest("debts/" + std::to_string(mId) + '/', completeJsonObject(selectedDebt), "PUT");
    RemoteStatus status = replyHandler(reply, "Debt updated successfully!");
    mIsForUpdate = status == RemoteStatus::Failure ? true : false;
    delete reply;
}

void DebtModel::remove()
{
    QJsonObject selectedDebt {
                             {"id", mId },
                             {"name", mName.c_str() },
                             {"amount", mAmount },
                             };

    QNetworkReply *reply = sendCRUDRequest("debts/" + std::to_string(mId) + '/', completeJsonObject(selectedDebt), "PUT");
    RemoteStatus status = replyHandler(reply, "Debt delete successfully!");
    mIsForDelete = status == RemoteStatus::Failure ? true : false;
    delete reply;
}

void DebtModel::parseJsonObject(const QJsonObject &object)
{
    mId = object["id"].toInt();
    mName = object["name"].toString().toStdString();
    mAmount = object["amount"].toInt();
    BaseModel::parseJsonObject(object);
}

void DebtModel::load(std::ifstream &file)
{
    file >> mId >> mName >> mAmount;
    BaseModel::load(file);
}

void DebtModel::save(std::ofstream &file)
{
    file << mId << " " << mName << " " << mAmount;
    BaseModel::save(file);
}

void DebtModel::increase(int amount)
{
    mAmount += amount;
}

void DebtModel::decrease(int amount)
{
    mAmount -= amount;
}
