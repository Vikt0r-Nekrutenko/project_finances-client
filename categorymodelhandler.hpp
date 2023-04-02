#ifndef CATEGORYMODELHANDLER_HPP
#define CATEGORYMODELHANDLER_HPP

#include "categorymodel.hpp"
#include "modelhandler.hpp"

class CategoryModelHandler : public DataModelHandler
{
public:

    CategoryModelHandler();

    const QVector<CategoryModel> &categories() const;

private:

    QVector<CategoryModel> mCategories;
};

#endif // CATEGORYMODELHANDLER_HPP
