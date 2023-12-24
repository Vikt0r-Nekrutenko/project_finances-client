#include <QJsonArray>
#include <QJsonObject>
#include "categorymodelhandler.hpp"

CategoryModelHandler::CategoryModelHandler()
{
    std::ifstream file(LocalPath + "categories.txt");

    if(file.is_open()) {
        while(true) {
            CategoryModel tmp("", "");
            tmp.load(file);
            if(tmp.version() > mVersion)
                mVersion = tmp.version();

            if(file.eof())
                break;

            mCategories.push_back(tmp);

            if(tmp.mIsForCreate) {
                mCategories.back().create();
            }
            if(tmp.mIsForUpdate) {
                mCategories.back().update();
            }
            if(tmp.mIsForDelete) {
                mCategories.back().remove();
            }
        }
        file.close();
    }
    // get("categories/");
}

CategoryModelHandler::~CategoryModelHandler()
{
    // std::ofstream file(LocalPath + "categories.txt");
    // for(auto &model : mCategories) {
    //     model.save(file);
    // }
    // file.close();
}

void CategoryModelHandler::addNewCategory(const std::string &name, const std::string &type)
{
    mCategories.push_back(CategoryModel{name, type, ++mVersion});
    mCategories.back().create();
}

void CategoryModelHandler::updateCategoryType(int index, const std::string &type)
{
    mCategories[index].mVersion = ++mVersion;
    mCategories[index].mType = type;
    mCategories[index].update();
}

void CategoryModelHandler::deleteCategory(int index)
{
    mCategories[index].mVersion = ++mVersion;
    mCategories[index].mIsDeleted = true;
    mCategories[index].remove();
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
}

std::vector<CategoryModel>::iterator CategoryModelHandler::findByName(const std::string &name)
{
    return std::find_if(mCategories.begin(), mCategories.end(), [&](const CategoryModel &model){
        return model.name() == name;
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
