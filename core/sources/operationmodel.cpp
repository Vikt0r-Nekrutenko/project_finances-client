#include <QJsonObject>
#include <QJsonDocument>

#include "operationmodel.hpp"
#include "depositmodelhandler.hpp"
#include "categorymodelhandler.hpp"

OperationModel::OperationModel(int id, const std::string &date, const std::string &deposit, int amount, const std::string &category)
    : mDate{date}, mDeposit{deposit}, mCategory{category}, mId{id}, mAmount{amount} {}

OperationModel::OperationModel(int id, const std::string &date, const std::string &deposit, int amount, const std::string &category, int version, bool isDeleted)
    : BaseModel{version, isDeleted}, mDate{date}, mDeposit{deposit}, mCategory{category}, mId{id}, mAmount{amount} {}

void OperationModel::create()
{
    QJsonObject newOperation {
        {"id", mId },
        {"date", mDate.c_str() },
        {"deposit", mDeposit.c_str() },
        {"amount", mAmount },
        {"category", mCategory.c_str() },
    };

    QNetworkReply *reply = sendCRUDRequest("operations/", newOperation, "POST");
    RemoteStatus status = replyHandler(reply, "Operation added successfully!");
    mIsForCreate = status == RemoteStatus::Failure ? true : false;
}

void OperationModel::read()
{
    QNetworkReply *reply = sendCRUDRequest("operations/" + std::to_string(mId) + '/', {}, "GET");
    replyHandler(reply, "Operation read successfully!");

    QJsonDocument jsonResponse = QJsonDocument::fromJson(QString(reply->readAll()).toUtf8());
    QJsonObject object = jsonResponse.object();
    parseJsonObject(object);
}

void OperationModel::update()
{
    QJsonObject selectedOperation {
        {"id", mId },
        {"date", mDate.c_str() },
        {"deposit", mDeposit.c_str() },
        {"amount", mAmount },
        {"category", mCategory.c_str() },
    };

    QNetworkReply *reply = sendCRUDRequest("operations/" + std::to_string(mId) + '/', selectedOperation, "PUT");
    RemoteStatus status = replyHandler(reply, "Operation updated successfully!");
    mIsForUpdate = status == RemoteStatus::Failure ? true : false;
}

void OperationModel::remove()
{
    QNetworkReply *reply = sendCRUDRequest("operations/" + std::to_string(mId) + '/', {}, "DELETE");
    RemoteStatus status = replyHandler(reply, "Operation delete successfully!");
    mIsForDelete = status == RemoteStatus::Failure ? true : false;
}

void OperationModel::parseJsonObject(const QJsonObject &object)
{
    mId = object["id"].toInt();
    mDate = object["date"].toString().toStdString();
    mDeposit = object["deposit"].toString().toStdString();
    mAmount = object["amount"].toInt();
    mCategory = object["category"].toString().toStdString();
}

void OperationModel::save(std::ofstream &file)
{
    file << mId << " " << mDate << " " << mDeposit << " " << mAmount << " " << mCategory;
    LocalModel::save(file);
}

void OperationModel::load(std::ifstream &file)
{
    file >> mId >> mDate >> mDeposit >> mAmount >> mCategory;
    LocalModel::load(file);
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

QDateTime OperationModel::rawDate() const
{
    return QDateTime().fromString(mDate.c_str(), "yyyy-MM-dd");
}

DepositModel &OperationModel::rawDeposit(DepositModelHandler &handler)
{
    return *handler.findByName(mDeposit);
}

CategoryModel &OperationModel::rawCategory(CategoryModelHandler &handler)
{
    return *handler.findByName(mCategory);
}

const std::string &OperationModel::category() const
{
    return mCategory;
}
