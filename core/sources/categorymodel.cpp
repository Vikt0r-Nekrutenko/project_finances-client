#include <QJsonObject>
#include <QJsonDocument>

#include "categorymodel.hpp"

CategoryModel::CategoryModel(const std::string &name, const std::string &type)
    : mName{name}, mType{type} {}

void CategoryModel::create()
{
    QJsonObject newCategory {
        {"name", mName.c_str() },
        {"type", mType.c_str() }
    };

    QNetworkReply *reply = sendCRUDRequest("categories/", newCategory, "POST");
    RemoteStatus status = replyHandler(reply, "Category added successfully!");
    mIsCreated = status == RemoteStatus::Failure ? true : false;
}

void CategoryModel::read()
{
    QNetworkReply *reply = sendCRUDRequest("categories/" + mName + '/', {}, "GET");
    replyHandler(reply, "Get request successfully!");

    QJsonDocument jsonResponse = QJsonDocument::fromJson(QString(reply->readAll()).toUtf8());
    QJsonObject object = jsonResponse.object();
    parseJsonObject(object);
}

void CategoryModel::update()
{
    QJsonObject selectedCategory {
        {"name", mName.c_str() },
        {"type", mType.c_str() }
    };

    QNetworkReply *reply = sendCRUDRequest("categories/" + mName + '/', selectedCategory, "PUT");
    RemoteStatus status = replyHandler(reply, "Category updated successfully!");
    mIsChanched = status == RemoteStatus::Failure ? true : false;
}

void CategoryModel::remove()
{
    QNetworkReply *reply = sendCRUDRequest("categories/" + mName + '/', {}, "DELETE");
    RemoteStatus status = replyHandler(reply, "Category deleted successfully!");
    mIsDeleted = status == RemoteStatus::Failure ? true : false;
}

void CategoryModel::parseJsonObject(const QJsonObject &object)
{
    mName = object["name"].toString().toStdString();
    mType = object["type"].toString().toStdString();
}

void CategoryModel::load(std::ifstream &file)
{
    file >> mName >> mType;
    LocalModel::load(file);
}

void CategoryModel::save(std::ofstream &file)
{
    file << mName << " " << mType;
    LocalModel::save(file);
}

const std::string &CategoryModel::name() const
{
    return mName;
}

const std::string &CategoryModel::type() const
{
    return mType;
}
