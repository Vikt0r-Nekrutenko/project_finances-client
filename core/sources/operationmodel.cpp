#include <QJsonObject>
#include <QJsonDocument>

#include "operationmodel.hpp"
#include "categorymodelhandler.hpp"

OperationModel::OperationModel(int id, const std::string &date, const std::string &deposit, int amount, const std::string &category)
    : mDate{date}, mDeposit{deposit}, mCategory{category}, mId{id}, mAmount{amount} {}

OperationModel::OperationModel(int id, const std::string &date, const std::string &deposit, int amount, const std::string &category, int version, bool isDeleted)
    : BaseModel{version, isDeleted}, mDate{date}, mDeposit{deposit}, mCategory{category}, mId{id}, mAmount{amount} {}

void OperationModel::create()
{
    QJsonObject newOperation {
        {"date", mDate.c_str() },
        {"deposit", mDeposit.c_str() },
        {"amount", mAmount },
        {"category", mCategory.c_str() },
    };

    QNetworkReply *reply = sendCRUDRequest("operations/", completeJsonObject(newOperation), "POST");
    RemoteStatus status = replyHandler(reply, "Operation added successfully!");
    mIsForCreate = status == RemoteStatus::Failure ? true : false;

    if(status == RemoteStatus::Success) {
        QJsonDocument jsonResponse = QJsonDocument::fromJson(QString(reply->readAll()).toUtf8());
        QJsonObject object = jsonResponse.object();
        mId = object["id"].toInt();
    }
    delete reply;
}

void OperationModel::read()
{
    QNetworkReply *reply = sendCRUDRequest("operations/" + std::to_string(mId) + '/', {}, "GET");
    replyHandler(reply, "Operation read successfully!");

    QJsonDocument jsonResponse = QJsonDocument::fromJson(QString(reply->readAll()).toUtf8());
    delete reply;
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

    QNetworkReply *reply = sendCRUDRequest("operations/" + std::to_string(mId) + '/', completeJsonObject(selectedOperation), "PUT");
    RemoteStatus status = replyHandler(reply, "Operation updated successfully!");
    mIsForUpdate = status == RemoteStatus::Failure ? true : false;
    delete reply;
}

void OperationModel::remove()
{
    QJsonObject selectedOperation {
                                  {"id", mId },
                                  {"date", mDate.c_str() },
                                  {"deposit", mDeposit.c_str() },
                                  {"amount", mAmount },
                                  {"category", mCategory.c_str() },
                                  };

    QNetworkReply *reply = sendCRUDRequest("operations/" + std::to_string(mId) + '/', completeJsonObject(selectedOperation), "PUT");
    RemoteStatus status = replyHandler(reply, "Operation delete successfully!");
    mIsForDelete = status == RemoteStatus::Failure ? true : false;
    delete reply;
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
    BaseModel::save(file);
}

void OperationModel::load(std::ifstream &file)
{
    file >> mId >> mDate >> mDeposit >> mAmount >> mCategory;
    BaseModel::load(file);
}

const CategoryModel &OperationModel::rawCategory(CategoryModelHandler &handler) const
{
    if(handler.query.findByName(mCategory) == handler.query.end())
        throw std::invalid_argument("handler has empty query!");
    return *(*handler.query.findByName(mCategory));
}
