#ifndef BASEMODEL_HPP
#define BASEMODEL_HPP

#include "crudmodel.hpp"
#include "localmodel.hpp"

class CORE_EXPORT BaseModel : public CRUDModel, public LocalModel
{
public:

    BaseModel(int version = 0, bool isDeleted = false);
    inline bool isDeleted() const { return mIsDeleted; }

protected:

    QJsonObject &completeJsonObject(QJsonObject &object);
    void load(std::ifstream &file) override;
    void save(std::ofstream &file) override;

    bool mIsDeleted { false };
};

#endif // BASEMODEL_HPP
