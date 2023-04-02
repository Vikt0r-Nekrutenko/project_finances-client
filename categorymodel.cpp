#include <QJsonObject>
#include <QJsonDocument>

#include "categorymodel.hpp"

CategoryModel::CategoryModel(const QString &name, const QString &type)
    : mName{name}, mType{type} {}

void CategoryModel::create()
{
    QJsonObject newCategory {
        {"name", mName },
        {"type", mType }
    };

    QNetworkReply *reply = sendCRUDRequest("categories/", newCategory, "POST");
    replyHandler(reply, "Category added successfully!");
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
        {"name", mName },
        {"type", mType }
    };

    QNetworkReply *reply = sendCRUDRequest("categories/" + mName + '/', selectedCategory, "PUT");
    replyHandler(reply, "Category updated successfully!");
}

void CategoryModel::remove()
{
    QNetworkReply *reply = sendCRUDRequest("categories/" + mName + '/', {}, "DELETE");
    replyHandler(reply, "Category deleted successfully!");
}

void CategoryModel::parseJsonObject(const QJsonObject &object)
{
    mName = object["name"].toString();
    mType = object["type"].toString();
}

const QString &CategoryModel::name() const
{
    return mName;
}

const QString &CategoryModel::type() const
{
    return mType;
}
