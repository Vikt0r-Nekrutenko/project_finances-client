#include <QJsonArray>
#include <QJsonObject>
#include "categorymodelhandler.hpp"

CategoryModelHandler::CategoryModelHandler()
{
    get("categories/");
}

void CategoryModelHandler::addNewCategory(const std::string &name, const std::string &type)
{
    mCategories.push_back(CategoryModel{name, type});
    mCategories.back().create();
}

void CategoryModelHandler::deleteCategory(int index)
{
    mCategories[index].remove();
    mCategories.erase(mCategories.begin() + index);
}

void CategoryModelHandler::parseJsonArray(const QJsonArray &replyJsonArray)
{
    mCategories.clear();
    for (const auto &var : replyJsonArray) {
        mCategories.push_back(CategoryModel{
            var.toObject()["name"].toString().toStdString(),
            var.toObject()["type"].toString().toStdString()
        });
    }
}

const std::vector<CategoryModel> &CategoryModelHandler::categories() const
{
    return mCategories;
}

std::vector<CategoryModel> &CategoryModelHandler::categories()
{
    return mCategories;
}

std::vector<CategoryModel>::iterator CategoryModelHandler::findByName(const std::string &name)
{
    return std::find_if(mCategories.begin(), mCategories.end(), [&](const CategoryModel &model){
        return model.name() == name;
    });
}
