#include <QJsonArray>
#include <QJsonObject>
#include "categorymodelhandler.hpp"

CategoryModelHandler::CategoryModelHandler()
{
    syncAndLoad("categories", mCategories);
    query.select();
}

CategoryModelHandler::~CategoryModelHandler()
{
    syncAndSave("categories.txt", mCategories);
}

void CategoryModelHandler::addNewCategory(const std::string &name, const std::string &type)
{
    addNewItem<CategoryModel, std::vector<CategoryModel>::iterator>(
        {name, type},
        mCategories,
        [&](const CategoryModel &model) {
            return model.mName == name;
        },
        [&](CategoryModel &model) {
            model.mType = type;
        });
    query.select();
}

void CategoryModelHandler::updateCategoryType(int index, const std::string &type)
{
    ++mVersion;
    query.at(index)->mType = type;
    query.at(index)->mIsForUpdate = true;
}

void CategoryModelHandler::deleteCategory(int index)
{
    deleteItem<CategoryModel>(query.at(index));
}

void CategoryModelHandler::parseJsonArray(const QJsonArray &replyJsonArray)
{
    int count = 0;
    for (const auto &var : replyJsonArray) {
        mCategories.push_back({
            var.toObject()["name"].toString().toStdString(),
            var.toObject()["type"].toString().toStdString(),
            var.toObject()["version"].toInt(),
            bool(var.toObject()["is_deleted"].toInt())
        });
        if(mCategories.back().version() > mVersion)
            mVersion = mCategories.back().version();
        ++count;
    }
    log().push_back({"Categories received: " + std::to_string(count)});

    parseAndMerge<CategoryModel, std::vector<CategoryModel>::iterator>(
        "categories",
        replyJsonArray,
        mCategories,
        [](const CategoryModel &remote, const CategoryModel &local) {
            return remote.mName == local.mName;
        },
        [](QJsonValueConstRef var) {
            return CategoryModel {
                var.toObject()["name"].toString().toStdString(),
                var.toObject()["type"].toString().toStdString(),
                var.toObject()["version"].toInt(),
                bool(var.toObject()["is_deleted"].toInt())
            };
        });
}

CategoryModelHandler::Query::Query(CategoryModelHandler *handler)
    : mHandler{handler} { }

const CategoryModelHandler::Query &CategoryModelHandler::Query::select()
{
    clear();
    for(size_t i = 0; i < mHandler->mCategories.size(); ++i)
        if(mHandler->mCategories.at(i).mIsDeleted == false)
            push_back(&mHandler->mCategories.at(i));
    return *this;
}

std::vector<CategoryModel *>::const_iterator CategoryModelHandler::Query::findByName(const std::string &name) const
{
    return std::find_if(begin(), end(), [&](const CategoryModel *model) {
        return model->name() == name;
    });
}
