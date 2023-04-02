#include "categorymodelhandler.hpp"

CategoryModelHandler::CategoryModelHandler()
{
    get("categories/");
}

void CategoryModelHandler::addNewCategory(const QString &name, const QString &type)
{

}

void CategoryModelHandler::deleteCategory(int index)
{

}

void CategoryModelHandler::parseJsonArray(const QJsonArray &replyJsonArray)
{

}

const QVector<CategoryModel> &CategoryModelHandler::categories() const
{
    return mCategories;
}
