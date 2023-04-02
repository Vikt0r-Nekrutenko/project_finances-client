#ifndef CATEGORYMODEL_HPP
#define CATEGORYMODEL_HPP

#include "crudmodel.hpp"

class CategoryModel : public CRUDModel
{
    friend class CategoryModelHandler;

public:

    CategoryModel(const QString &name, const QString &type);

    const QString &name() const;
    const QString &type() const;

private:

    QString mName;
    QString mType;
};

#endif // CATEGORYMODEL_HPP
