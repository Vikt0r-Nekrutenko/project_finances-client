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
        get(collectionName);
    }

    template<class ModelT, class CollectionIteratorT> void merge(const std::string &collectionName, const ModelT &remoteTmp, std::vector<ModelT> &collection, const std::function<bool(const ModelT &)> &comp)
    {
        CollectionIteratorT localTmp = std::find_if(collection.begin(), collection.end(), [&](const ModelT &model) {
            return comp(model);
        });

        if(localTmp == collection.end())
            collection.push_back(remoteTmp);
        else
            *localTmp = remoteTmp;

        if(remoteTmp.version() > mVersion)
            mVersion = remoteTmp.version();
        if(remoteTmp.version() > settings()[(collectionName + "_last_synced_version").c_str()].toInt())
            settings()[(collectionName + "_last_synced_version").c_str()] = remoteTmp.version();
    }

    RemoteStatus get(const std::string &collectionName);

    virtual void parseJsonArray(const QJsonArray &array) = 0;
};

template <class ModelT>
class CORE_EXPORT BaseModelHandler : public DataModelHandler
{
protected:

    void deleteItem(ModelT *model)
    {
        ++mVersion;
        model->mIsDeleted = true;
        model->mIsForDelete = true;
    }
    void syncAndSave(const std::string &fileName, std::vector<ModelT> &collection)
    {
        std::ofstream file(LocalPath + fileName);
        for(ModelT &model : collection) {
            model.syncAndSave(file, mVersion);
        }
        file.close();
    }
    template<class IteratorT> void addNewItem(const ModelT &item, std::vector<ModelT> &collection, const std::function<bool(const ModelT &model)> &compf, const std::function<void(ModelT &model)> &updf)
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
    ///
    /// \brief Thist function parse json array that was received in request reply. If item in array exist in item collections
    /// item will be update else item will be add to collection
    /// \param collectionName - name of items collection
    /// \param replyJsonArray - array
    /// \param collection - collection
    /// \param compf - compare function for comparing received item with local item
    /// \param buildf - return the new ModelT object from QJsonObject
    ///
    template<class IteratorT> void parseAndMerge(
        const std::string &collectionName,
        const QJsonArray &replyJsonArray,
        std::vector<ModelT> &collection,
        const std::function<bool(const ModelT &, const ModelT &)> &compf,
        std::function<ModelT(QJsonValueConstRef)> buildf)
    {
        int count = 0;
        for (const auto &var : replyJsonArray) {
            ModelT remoteTmp = buildf(var);

            merge<ModelT, IteratorT>(collectionName, remoteTmp, collection, [&](const ModelT &model){
                return compf(remoteTmp, model);
            });
            ++count;
        }
        log().push_back({collectionName + " received: " + std::to_string(count)});
    }
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
