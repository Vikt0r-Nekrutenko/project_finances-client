#ifndef MODELHANDLER_HPP
#define MODELHANDLER_HPP

#include "datamodel.hpp"
#include <QJsonObject>
#include <QJsonArray>

class BaseModel;

class DataModelHandler : public DataModel
{
protected:

    template<class ModelT> void deleteItem(ModelT *model);

    template<class ModelT> void syncAndLoad(const std::string &collectionName, std::vector<ModelT> &collection);

    template<class ModelT> void syncAndSave(const std::string &fileName, std::vector<ModelT> &collection);

    template<class ModelT, class IteratorT> void addNewItem(
        const ModelT &item,
        std::vector<ModelT> &collection,
        const std::function<bool(const ModelT &model)> &compf,
        const std::function<void(ModelT &model)> &updf);

    template<class ModelT, class IteratorT> void parseAndMerge(
        const std::string &collectionName,
        const QJsonArray &replyJsonArray,
        std::vector<ModelT> &collection,
        const std::function<bool(const ModelT &, const ModelT &)> &compf,
        std::function<ModelT(QJsonValueConstRef)> buildf);

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
