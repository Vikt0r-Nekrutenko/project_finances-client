#include <QJsonArray>
#include <QJsonObject>
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
    mCategories.clear();
    for (const auto &var : replyJsonArray) {
        mCategories.push_back(CategoryModel{
            var.toObject()["name"].toString(),
            var.toObject()["type"].toString()
        });
    }
}

const QVector<CategoryModel> &CategoryModelHandler::categories() const
{
    return mCategories;
}

QVector<CategoryModel> &CategoryModelHandler::categories()
{
    return mCategories;
}

QList<CategoryModel>::iterator CategoryModelHandler::findByName(const QString &name)
{
    return std::find_if(mCategories.begin(), mCategories.end(), [&](const CategoryModel &model){
        return model.name() == name;
    });
}
