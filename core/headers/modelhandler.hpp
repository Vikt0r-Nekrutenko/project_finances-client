#ifndef MODELHANDLER_HPP
#define MODELHANDLER_HPP

#include "datamodel.hpp"
#include "localmodel.hpp"
#include <QJsonObject>
#include <QJsonArray>

class BaseModel;

class DataModelHandler : public DataModel
{
public:

    virtual ~DataModelHandler() = default;

protected:

    template<class ModelT> void deleteItem(ModelT *model)
    {
        ++mVersion;
        model->mIsDeleted = true;
        model->mIsForDelete = true;
    }

    template<class ModelT> void syncAndLoad(const std::string &collectionName, std::vector<ModelT> &collection)
    {
        std::ifstream file(LocalPath + collectionName + ".txt");

        if(file.is_open()) {
            while(true) {
                ModelT model;
                model.load(file);

                if(file.eof())
                    break;

                collection.push_back(model);

                if(collection.back().version() > mVersion)
                    mVersion = collection.back().version();
            }
            file.close();
        }
        get(collectionName);
    }

    template<class ModelT> void syncAndSave(const std::string &fileName, std::vector<ModelT> &collection)
    {
        std::ofstream file(LocalPath + fileName);
        for(ModelT &model : collection) {
            model.syncAndSave(file, mVersion);
        }
        file.close();
    }

    template<class ModelT, class IteratorT> void addNewItem(const ModelT &item, std::vector<ModelT> &collection, const std::function<bool(const ModelT &model)> &compf, const std::function<void(ModelT &model)> &updf)
    {
        ++mVersion;
        IteratorT searchedDeposit = std::find_if(collection.begin(), collection.end(), [&](const ModelT &model){
            return compf(model);
        });
        if(searchedDeposit == collection.end()) {
            collection.push_back(item);
            collection.back().mIsForCreate = true;
        } else {
            updf(*searchedDeposit);
            searchedDeposit->mIsDeleted = searchedDeposit->mIsForDelete = false;
            searchedDeposit->mIsForUpdate = true;
        }
    }

    template<class ModelT, class IteratorT> void parseAndMerge(
        const std::string &collectionName,
        const QJsonArray &replyJsonArray,
        std::vector<ModelT> &collection,
        const std::function<bool(const ModelT &, const ModelT &)> &compf,
        std::function<ModelT(QJsonValueConstRef)> buildf)
    {
        int count = 0;
        for (const auto &var : replyJsonArray) {
            ModelT remoteTmp = buildf(var);

            IteratorT localTmp = std::find_if(collection.begin(), collection.end(), [&](const ModelT &model) {
                return compf(remoteTmp, model);
            });

            if(localTmp == collection.end())
                collection.push_back(remoteTmp);
            else
                *localTmp = remoteTmp;

            if(remoteTmp.version() > mVersion)
                mVersion = remoteTmp.version();
            if(remoteTmp.version() > settings()[(collectionName + "_last_synced_version").c_str()].toInt())
                settings()[(collectionName + "_last_synced_version").c_str()] = remoteTmp.version();

            ++count;
        }
        log().push_back({collectionName + " received: " + std::to_string(count)});
    }

    RemoteStatus get(const std::string &collectionName);

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
