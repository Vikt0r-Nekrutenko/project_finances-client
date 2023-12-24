#ifndef CATEGORYMODEL_HPP
#define CATEGORYMODEL_HPP

#include "basemodel.hpp"

class CORE_EXPORT CategoryModel : public BaseModel
{
    friend class CategoryModelHandler;

public:

    CategoryModel() = default;
    CategoryModel(const std::string &name, const std::string &type);
    CategoryModel(const std::string &name, const std::string &type, int version, bool isDeleted = false);

    void create() override;
    void read() override;
    void update() override;
    void remove() override;

    void load(std::ifstream &file) override;
    void save(std::ofstream &file) override;

    inline const std::string &name() const { return mName; }
    inline const std::string &type() const { return mType; }

private:

    void parseJsonObject(const QJsonObject &object) override;

    std::string mName;
    std::string mType;
};

#endif // CATEGORYMODEL_HPP
