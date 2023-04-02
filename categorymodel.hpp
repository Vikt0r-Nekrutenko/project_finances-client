#ifndef CATEGORYMODEL_HPP
#define CATEGORYMODEL_HPP

#include "crudmodel.hpp"

class CategoryModel : public CRUDModel
{
    friend class CategoryModelHandler;

public:

    CategoryModel();

private:

    QString mName;
    QString mType;
};

#endif // CATEGORYMODEL_HPP
