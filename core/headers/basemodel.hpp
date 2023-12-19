#ifndef BASEMODEL_HPP
#define BASEMODEL_HPP

#include "crudmodel.hpp"
#include "localmodel.hpp"

class CORE_EXPORT BaseModel : public CRUDModel, public LocalModel
{
protected:

    QJsonObject &completeJsonObject(QJsonObject &object);
};

#endif // BASEMODEL_HPP
