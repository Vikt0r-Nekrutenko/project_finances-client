#ifndef CATEGORYMODEL_HPP
#define CATEGORYMODEL_HPP

#include "crudmodel.hpp"

class CategoryModel : public CRUDModel
{
    friend class CategoryModelHandler;

public:

    CategoryModel(const QString &name, const QString &type);

    void create() override;
    void read() override;
    void update() override;
    void remove() override;
    void parseJsonObject(const QJsonObject &object) override;

    const QString &name() const;
    const QString &type() const;

private:

    QString mName;
    QString mType;
};

#endif // CATEGORYMODEL_HPP
