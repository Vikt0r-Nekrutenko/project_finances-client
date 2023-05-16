#ifndef MODELHANDLER_HPP
#define MODELHANDLER_HPP

#include "datamodel.hpp"

class DataModelHandler : public DataModel
{
public:
    virtual ~DataModelHandler() = default;
    void get(const std::string &additionalPath);
    virtual void parseJsonArray(const QJsonArray &array) = 0;
};

#endif // MODELHANDLER_HPP
