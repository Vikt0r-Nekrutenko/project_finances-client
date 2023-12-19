#ifndef CATEGORYMODEL_HPP
#define CATEGORYMODEL_HPP

#include "crudmodel.hpp"
#include "localmodel.hpp"

class CORE_EXPORT CategoryModel : public CRUDModel, public LocalModel
{
    friend class CategoryModelHandler;

public:

    CategoryModel(const std::string &name, const std::string &type);

    void create() override;
    void read() override;
    void update() override;
    void remove() override;
    void parseJsonObject(const QJsonObject &object) override;

    void load(std::ifstream &file) override;
    void save(std::ofstream &file) override;

    inline const std::string &name() const { return mName; }
    inline const std::string &type() const { return mType; }

private:

    std::string mName;
    std::string mType;
};

#endif // CATEGORYMODEL_HPP
