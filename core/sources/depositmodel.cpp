#include <QJsonObject>
#include <QJsonDocument>

#include "depositmodel.hpp"

DepositModel::DepositModel(const std::string &name, int balance)
    : mName{name}, mBalance{balance} {}

DepositModel::DepositModel(const std::string &name, int balance, int version, bool isDeleted)
    : BaseModel{version, isDeleted}, mName{name}, mBalance{balance} { }

void DepositModel::create()
{
    QJsonObject newDepo {
        {"name", mName.c_str() },
        {"balance", mBalance }
    };

    QNetworkReply *reply = sendCRUDRequest("deposits/", completeJsonObject(newDepo), "POST");
    RemoteStatus status = replyHandler(reply, "Deposit added successfully!");
    mIsForCreate = status == RemoteStatus::Failure ? true : false;
    delete reply;
}

void DepositModel::read()
{
    QNetworkReply *reply = sendCRUDRequest("deposits/" + mName + '/', {}, "GET");
    replyHandler(reply, "Get request successfully!");

    QJsonDocument jsonResponse = QJsonDocument::fromJson(QString(reply->readAll()).toUtf8());
    delete reply;
    QJsonObject object = jsonResponse.object();
    parseJsonObject(object);
}

void DepositModel::update()
{
    QJsonObject selectedDeposit {
        {"name", mName.c_str() },
        {"balance", mBalance }
    };

    QNetworkReply *reply = sendCRUDRequest("deposits/" + mName + '/', completeJsonObject(selectedDeposit), "PUT");
    RemoteStatus status = replyHandler(reply, "Balance updated successfully!");
    mIsForUpdate = status == RemoteStatus::Failure ? true : false;
    delete reply;
}

void DepositModel::remove()
{
    QJsonObject selectedDeposit {
        {"name", mName.c_str() },
        {"balance", mBalance }
    };

    QNetworkReply *reply = sendCRUDRequest("deposits/" + mName + '/', completeJsonObject(selectedDeposit), "PUT");
    RemoteStatus status = replyHandler(reply, "Deposit deleted successfully!");
    mIsForDelete = status == RemoteStatus::Failure ? true : false;
    delete reply;
}

void DepositModel::parseJsonObject(const QJsonObject &object)
{
    mName = object["name"].toString().toStdString();
    mBalance = object["balance"].toInt();
    BaseModel::parseJsonObject(object);
}

void DepositModel::load(std::ifstream &file)
{
    file >> mName >> mBalance;
    BaseModel::load(file);
}

void DepositModel::save(std::ofstream &file)
{
    file << mName << " " << mBalance;
    BaseModel::save(file);
}
