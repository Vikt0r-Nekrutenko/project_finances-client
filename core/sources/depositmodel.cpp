#include <QJsonObject>
#include <QJsonDocument>

#include "depositmodel.hpp"

DepositModel::DepositModel(const std::string &name, int balance)
    : mName{name}, mBalance{balance} {}

DepositModel::DepositModel(const std::string &name, int balance, int version, bool isDeleted)
    : mName{name}, mBalance{balance}
{
    mVersion = version;
    mIsDeleted = isDeleted;
}

void DepositModel::create()
{
    QJsonObject newDepo {
        {"name", mName.c_str() },
        {"balance", mBalance }
    };

    QNetworkReply *reply = sendCRUDRequest("deposits/", completeJsonObject(newDepo), "POST");
    RemoteStatus status = replyHandler(reply, "Deposit added successfully!");
    mIsCreated = status == RemoteStatus::Failure ? true : false;
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
    RemoteStatus status = replyHandler(reply, "Balance updated successfully!");
    mIsChanched = status == RemoteStatus::Failure ? true : false;
}

void DepositModel::remove()
{
    QNetworkReply *reply = sendCRUDRequest("deposits/" + mName + '/', {}, "DELETE");
    RemoteStatus status = replyHandler(reply, "Deposit deleted successfully!");
    mIsDeleted = status == RemoteStatus::Failure ? true : false;
}

void DepositModel::parseJsonObject(const QJsonObject &object)
{
    mName = object["name"].toString().toStdString();
    mBalance = object["balance"].toInt();
}

void DepositModel::load(std::ifstream &file)
{
    file >> mName >> mBalance;
    LocalModel::load(file);
}

void DepositModel::save(std::ofstream &file)
{
    file << mName << " " << mBalance;
    LocalModel::save(file);
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

