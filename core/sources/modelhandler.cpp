#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QEventLoop>

#include "modelhandler.hpp"
#include "basemodel.hpp"

RemoteStatus DataModelHandler::get(const std::string &additionalPath)
{
    QNetworkReply *reply = sendCRUDRequest(additionalPath, {}, "GET", {{"version", std::to_string(mVersion).c_str()}});
    RemoteStatus status = replyHandler(reply, "Get request successfully!");
    if(status == RemoteStatus::Failure)
        return RemoteStatus::Failure;

    QJsonDocument jsonResponse = QJsonDocument::fromJson(QString(reply->readAll()).toUtf8());
    delete reply;

    QJsonArray array = jsonResponse.array();
    parseJsonArray(array);

    return RemoteStatus::Success;
}

void DataModelHandler::applyChanges(BaseModel *changeModel)
{
    changeModel->setVersion(mVersion);

    if(changeModel->isForCreate() && changeModel->isForDelete())
        return;

    if(changeModel->isForCreate()) {
        changeModel->create();
        changeModel->setIsForUpdate(false);
    }
    else if(changeModel->isForDelete()) {
        changeModel->remove();
        changeModel->setIsForUpdate(false);
    }
    else if(changeModel->isForUpdate())
        changeModel->update();
}

void DataModelHandler::addNewChange(const size_t index)
{
    ++mVersion;
    std::vector<size_t>::iterator curDepIt = std::find_if(mListOfChanges.begin(), mListOfChanges.end(), [&](const size_t &indx) {
        return indx == index;
    });
    if(curDepIt == mListOfChanges.end())
        mListOfChanges.push_back(index);
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
