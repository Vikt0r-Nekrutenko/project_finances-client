#ifndef MODELHANDLER_HPP
#define MODELHANDLER_HPP

#include "datamodel.hpp"
#include "localmodel.hpp"

class BaseModel;

class DataModelHandler : public DataModel
{
public:

    virtual ~DataModelHandler() = default;

protected:

    template<class T> void syncAndLoad(const std::string &collectionName, std::vector<T> &collection)
    {
        std::ifstream file(LocalPath + collectionName + ".txt");

        if(file.is_open()) {
            while(file.eof() == false) {
                collection.push_back({});
                collection.back().load(file);
                if(collection.back().version() > mVersion)
                    mVersion = collection.back().version();
            }
            file.close();
        }
        get(collectionName + "/");
    }
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
