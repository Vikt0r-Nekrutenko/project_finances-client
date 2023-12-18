#include <QEventLoop>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include "datamodel.hpp"

const std::vector<std::string> &log()
{
    return CoreLog;
}

std::string
    DataModel::AuthValue,
    DataModel::MainPath;

QNetworkReply *DataModel::sendCRUDRequest(const std::string &additionalPath, const QJsonObject &data, const std::string &request)
{
    if(!MainPath.length() || !AuthValue.length()) {
        QFile settingsFile("settings.json");
        settingsFile.open(QIODevice::ReadOnly | QIODevice::Text);
        if(!settingsFile.isOpen())
            throw std::invalid_argument("file: " + settingsFile.fileName().toStdString() + " doesn't opened!");

        QJsonObject obj = QJsonDocument::fromJson(QString(settingsFile.readAll()).toUtf8()).object();
        AuthValue = obj["value"].toString().toStdString();
        MainPath = obj["url"].toString().toStdString();
    }

    QNetworkAccessManager *mManager = new QNetworkAccessManager();
    QNetworkRequest mRequest {QUrl((MainPath + additionalPath).c_str())};

    mRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    mRequest.setRawHeader("accept", "application/json");
    mRequest.setRawHeader("authorization", AuthValue.c_str());

    QEventLoop loop;

    QObject::connect(mManager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    QNetworkReply *reply = mManager->sendCustomRequest(mRequest, request.c_str(), QJsonDocument(data).toJson());

    loop.exec();

    return reply;
}

RemoteStatus DataModel::replyHandler(QNetworkReply *reply, const std::string &noErrorMsg) const
{
    if(reply->error() == QNetworkReply::NoError) {
        CoreLog.push_back(noErrorMsg);
        reply->deleteLater();
        return RemoteStatus::Success;
    } else {
        CoreLog.push_back(reply->errorString().toStdString());
        reply->deleteLater();
        return RemoteStatus::Failure;
    }
}
