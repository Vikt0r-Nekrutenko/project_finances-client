#include <QJsonObject>
#include <QJsonDocument>

#include "categorymodel.hpp"

CategoryModel::CategoryModel(const QString &name, const QString &type)
    : mName{name}, mType{type} {}

void CategoryModel::create()
{

}

void CategoryModel::read()
{

}

void CategoryModel::update()
{

}

void CategoryModel::remove()
{

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
