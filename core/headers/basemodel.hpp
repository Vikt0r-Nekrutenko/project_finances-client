#ifndef BASEMODEL_HPP
#define BASEMODEL_HPP

#include "crudmodel.hpp"
#include "localmodel.hpp"

class CORE_EXPORT BaseModel : public CRUDModel, public LocalModel
{
public:

    BaseModel(int version = 0, bool isDeleted = false);
    inline bool isDeleted() const { return mIsDeleted; }
    void setIsDeleted(bool value) { mIsDeleted = value; }

protected:

    QJsonObject &completeJsonObject(QJsonObject &object);
    void parseJsonObject(const QJsonObject &object) override;
    void load(std::ifstream &file) override;
    void save(std::ofstream &file) override;
    void syncAndSave(std::ofstream &file, int version);

    bool mIsDeleted { false };    
};

#endif // BASEMODEL_HPP
