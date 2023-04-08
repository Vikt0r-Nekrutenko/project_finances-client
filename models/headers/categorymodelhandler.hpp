#ifndef CATEGORYMODELHANDLER_HPP
#define CATEGORYMODELHANDLER_HPP

#include "categorymodel.hpp"
#include "modelhandler.hpp"

class CategoryModelHandler : public DataModelHandler
{
public:

    CategoryModelHandler();

    void addNewCategory(const std::string &name, const std::string &type);
    void deleteCategory(int index);
    void parseJsonArray(const QJsonArray &replyJsonArray) override;

    const std::vector<CategoryModel> &categories() const;
    std::vector<CategoryModel> &categories();

    std::vector<CategoryModel>::iterator findByName(const std::string &name);

private:

    std::vector<CategoryModel> mCategories;
};

#endif // CATEGORYMODELHANDLER_HPP
