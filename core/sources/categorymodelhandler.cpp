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
            if(tmp.mIsForDelete) {
                mCategories.back().remove();
            }
        }
    }
    file.close();
    get("categories/");
}

CategoryModelHandler::~CategoryModelHandler()
{
    std::ofstream file(LocalPath + "categories.txt");
    for(auto &model : mCategories) {
        model.save(file);
    }
    file.close();
}

void CategoryModelHandler::addNewCategory(const std::string &name, const std::string &type)
{
    mCategories.push_back(CategoryModel{name, type});
    mCategories.back().create();
}

void CategoryModelHandler::deleteCategory(int index)
{
    mCategories[index].remove();
    if(mCategories[index].mIsForDelete == false)
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

std::vector<CategoryModel>::iterator CategoryModelHandler::findByName(const std::string &name)
{
    return std::find_if(mCategories.begin(), mCategories.end(), [&](const CategoryModel &model){
        return model.name() == name;
    });
}
