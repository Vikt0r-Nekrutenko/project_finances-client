#include <QJsonArray>
#include <QJsonObject>
#include "categorymodelhandler.hpp"

CategoryModelHandler::CategoryModelHandler()
{
    RemoteStatus status = get("categories/");
    std::ifstream file(LocalPath + "categories.txt");
    unsigned index = 0;

    if(file.is_open()) {
        while(true) {
            CategoryModel tmp("", "");
            tmp.load(file);

            if(file.eof()){
                break;
            } else if(status == RemoteStatus::Failure) {
                mCategories.push_back(tmp);
            } else if(status == RemoteStatus::Success) {
                if(tmp.mIsForCreate)
                    addNewCategory(tmp.mName, tmp.mType);
                if(tmp.mIsForDelete)
                    deleteCategory(index);
            }
            ++index;
        }
        file.close();
    }
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
