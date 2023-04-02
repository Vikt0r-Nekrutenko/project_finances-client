#include "categorymodelhandler.hpp"

CategoryModelHandler::CategoryModelHandler()
{
    get("categories/");
}

const QVector<CategoryModel> &CategoryModelHandler::categories() const
{
    return mCategories;
}
