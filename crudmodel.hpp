#ifndef CRUDMODEL_HPP
#define CRUDMODEL_HPP

#include "datamodel.hpp"

class CRUDModel : public DataModel
{
public:
    virtual void create() = 0;
    virtual void read() = 0;
    virtual void update() = 0;
    virtual void remove() = 0;
    virtual void parseJsonObject(const QJsonObject &) = 0;
};

#endif // CRUDMODEL_HPP
