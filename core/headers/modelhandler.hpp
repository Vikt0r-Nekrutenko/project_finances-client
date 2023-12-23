#ifndef MODELHANDLER_HPP
#define MODELHANDLER_HPP

#include "datamodel.hpp"
#include "localmodel.hpp"

class BaseModel;

class DataModelHandler : public DataModel
{
public:

    virtual ~DataModelHandler() = default;
    inline int lastSyncedVersion() const { return mLastSyncedVersion; }

protected:

    template<class T> void syncAndLoad(const std::string &collectionName, std::vector<T> &collection)
    {
        std::ifstream file(LocalPath + collectionName + ".txt");

        if(file.is_open()) {
            while(true) {
                T model;
                model.load(file);

                if(file.eof())
                    break;

                collection.push_back(model);

                if(collection.back().version() > mVersion)
                    mVersion = collection.back().version();
            }
            file.close();
        }
        get(collectionName + "/");
    }

    template<class ModelT, class CollectionIteratorT> void merge(const ModelT &remoteTmp, std::vector<ModelT> &collection, const std::function<bool(const ModelT &)> &comp)
    {
        CollectionIteratorT localTmp = std::find_if(collection.begin(), collection.end(), [&](const ModelT &model) {
            return comp(model);
        });

        if(localTmp == collection.end())
            collection.push_back(remoteTmp);
        else
            *localTmp = remoteTmp;

        if(remoteTmp.version() > mVersion)
            mLastSyncedVersion = mVersion = remoteTmp.version();
    }

    RemoteStatus get(const std::string &collectionName);

    virtual void parseJsonArray(const QJsonArray &array) = 0;

    int mLastSyncedVersion { -1 };
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
