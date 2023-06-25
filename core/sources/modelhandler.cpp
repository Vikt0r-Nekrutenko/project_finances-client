#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QEventLoop>

#include "modelhandler.hpp"

RemoteStatus DataModelHandler::get(const std::string &additionalPath)
{
    QNetworkReply *reply = sendCRUDRequest(additionalPath, {}, "GET");
    RemoteStatus status = replyHandler(reply, "Get request successfully!");
    if(status == RemoteStatus::Failure)
        return RemoteStatus::Failure;

    QJsonDocument jsonResponse = QJsonDocument::fromJson(QString(reply->readAll()).toUtf8());

    QJsonArray array = jsonResponse.array();
    parseJsonArray(array);

    return RemoteStatus::Success;
}

MonoBankDataHandler::MonoBankDataHandler()
{
    static QNetworkAccessManager *mManager = new QNetworkAccessManager;
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

std::vector<MonoBankDataHandler::Currency>::const_iterator MonoBankDataHandler::usd() const
{
    return std::find_if(mQuotes.begin(), mQuotes.end(), [&](const Currency &model){
        return model.code == 840;
    });
}
