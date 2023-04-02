#include "categorymodel.hpp"

CategoryModel::CategoryModel(const QString &name, const QString &type)
    : mName{name}, mType{type} {}

const QString &CategoryModel::name() const
{
    return mName;
}

const QString &CategoryModel::type() const
{
    return mType;
}
