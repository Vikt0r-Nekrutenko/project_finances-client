#include "categorymodelhandler.hpp"

CategoryModelHandler::CategoryModelHandler()
{
    get("categories/");
}

void CategoryModelHandler::addNewCategory(const QString &name, const QString &type)
{
    mCategories.push_back(CategoryModel{name, type});
    mCategories.back().create();
}

void CategoryModelHandler::deleteCategory(int index)
{
    mCategories[index].remove();
    mCategories.removeAt(index);
}

void CategoryModelHandler::parseJsonArray(const QJsonArray &replyJsonArray)
{

}

const QVector<CategoryModel> &CategoryModelHandler::categories() const
{
    return mCategories;
}
