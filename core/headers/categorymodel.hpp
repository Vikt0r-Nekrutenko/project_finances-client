#ifndef CATEGORYMODEL_HPP
#define CATEGORYMODEL_HPP

#include "crudmodel.hpp"

class CategoryModel : public CRUDModel
{
    friend class CategoryModelHandler;

public:

    CategoryModel(const std::string &name, const std::string &type);

    void create() override;
    void read() override;
    void update() override;
    void remove() override;
    void parseJsonObject(const QJsonObject &object) override;

    const std::string &name() const;
    const std::string &type() const;

private:

    std::string mName;
    std::string mType;
};

#endif // CATEGORYMODEL_HPP
