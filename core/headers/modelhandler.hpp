#ifndef MODELHANDLER_HPP
#define MODELHANDLER_HPP

#include "datamodel.hpp"

class DataModelHandler : public DataModel
{
public:
    virtual ~DataModelHandler() = default;
    RemoteStatus get(const std::string &additionalPath);
    virtual void parseJsonArray(const QJsonArray &array) = 0;
};

class CORE_EXPORT MonoBankDataHandler
{
public:

    struct Currency
    {
        int code;
        float buy;
        float sell;
    };

    MonoBankDataHandler();
    const std::vector<Currency> &quotes() const;
    std::vector<Currency>::const_iterator usd() const;

private:

    std::vector<Currency> mQuotes;
};

#endif // MODELHANDLER_HPP
