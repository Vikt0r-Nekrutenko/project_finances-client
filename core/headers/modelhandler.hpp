#ifndef MODELHANDLER_HPP
#define MODELHANDLER_HPP

#include "datamodel.hpp"

enum class RemoteStatus
{
    Success, Failure,
};

class DataModelHandler : public DataModel
{
public:
    virtual ~DataModelHandler() = default;
    RemoteStatus get(const std::string &additionalPath);
    virtual void parseJsonArray(const QJsonArray &array) = 0;
};

#endif // MODELHANDLER_HPP
