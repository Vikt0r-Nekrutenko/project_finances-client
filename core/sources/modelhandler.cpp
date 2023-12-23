#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QEventLoop>
#include <QFile>

#include "modelhandler.hpp"
#include "localmodel.hpp"

RemoteStatus DataModelHandler::get(const std::string &collectionName)
{
    std::string lastSyncedVersion = std::to_string(settings()[(collectionName + "_last_synced_version").c_str()].toInt());
    QNetworkReply *reply = sendCRUDRequest(collectionName + "/", {}, "GET", {{"version", lastSyncedVersion.c_str()}});
    RemoteStatus status = replyHandler(reply, "Get request successfully!");
    if(status == RemoteStatus::Failure)
        return RemoteStatus::Failure;

    QJsonDocument jsonResponse = QJsonDocument::fromJson(QString(reply->readAll()).toUtf8());
    delete reply;

    QJsonArray array = jsonResponse.array();
    parseJsonArray(array);

    return RemoteStatus::Success;
}

template<class ModelT>
void DataModelHandler::deleteItem(ModelT *model)
{
    ++mVersion;
    model->setIsDeleted(true);
    model->setIsForDelete(true);
}

template<class ModelT>
void DataModelHandler::syncAndLoad(const std::string &collectionName, std::vector<ModelT> &collection)
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

template<class ModelT>
void DataModelHandler::syncAndSave(const std::string &fileName, std::vector<ModelT> &collection)
{
    std::ofstream file(LocalPath + fileName);
    for(ModelT &model : collection) {
        model.syncAndSave(file, mVersion);
    }
    file.close();
}

template<class ModelT, class IteratorT>
void DataModelHandler::addNewItem(const ModelT &item, std::vector<ModelT> &collection, const std::function<bool (const ModelT &)> &compf, const std::function<void (ModelT &)> &updf)
{
    ++mVersion;
    IteratorT searchedDeposit = std::find_if(collection.begin(), collection.end(), [&](const ModelT &model){
        return compf(model);
    });
    if(searchedDeposit == collection.end()) {
        collection.push_back(item);
        collection.back().setIsForCreate(true);
    } else {
        updf(*searchedDeposit);
        searchedDeposit->setIsDeleted(false);
        searchedDeposit->setIsForDelete(false);
        searchedDeposit->setIsForUpdate(true);
    }
}

template<class ModelT, class IteratorT>
void DataModelHandler::parseAndMerge(const std::string &collectionName, const QJsonArray &replyJsonArray, std::vector<ModelT> &collection, const std::function<bool (const ModelT &, const ModelT &)> &compf, std::function<ModelT (QJsonValueConstRef)> buildf)
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

MonoBankDataHandler::MonoBankDataHandler()
{
    QNetworkAccessManager *mManager = new QNetworkAccessManager;
    QNetworkRequest mRequest {QUrl("https://api.monobank.ua/bank/currency")};

    mRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QEventLoop loop;

    QObject::connect(mManager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    QNetworkReply *reply = mManager->get(mRequest);

    loop.exec();

    if(reply->error() == QNetworkReply::NoError) {
        CoreLog.push_back("Quotes has got successfully!");
    } else {
        CoreLog.push_back(reply->errorString().toStdString());
    }
    reply->deleteLater();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(QString(reply->readAll()).toUtf8());
    delete reply;
    QJsonArray array = jsonResponse.array();

    mQuotes.clear();
    for (const auto &var : array) {
        mQuotes.push_back(Currency{
            var.toObject()["currencyCodeA"].toInt(),
            float(var.toObject()["rateBuy"].toDouble()),
            float(var.toObject()["rateSell"].toDouble())
        });
    }
}

const std::vector<MonoBankDataHandler::Currency> &MonoBankDataHandler::quotes() const
{
    return mQuotes;
}

std::vector<MonoBankDataHandler::Currency>::const_iterator MonoBankDataHandler::usd() const
{
    return std::find_if(mQuotes.begin(), mQuotes.end(), [&](const Currency &model){
        return model.code == 840;
    });
}
