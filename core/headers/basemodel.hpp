#ifndef BASEMODEL_HPP
#define BASEMODEL_HPP

#include "crudmodel.hpp"
#include "localmodel.hpp"

class CORE_EXPORT BaseModel : public CRUDModel, public LocalModel
{
protected:

    QJsonObject &completeJsonObject(QJsonObject &object);
    void load(std::ifstream &file) override;
    void save(std::ofstream &file) override;

    inline bool isDeleted() const { return mIsDeleted; }

    bool mIsDeleted { false };
};

#endif // BASEMODEL_HPP
