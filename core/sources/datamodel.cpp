#include <QEventLoop>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include "datamodel.hpp"

const std::vector<std::string> &log()
{
    return CoreLog;
}

std::string DataModel::AuthName, DataModel::AuthValue;

QNetworkReply *DataModel::sendCRUDRequest(const std::string &additionalPath, const QJsonObject &data, const std::string &request)
{
    QNetworkRequest mRequest {QUrl((MainPath + additionalPath).c_str())};

    mRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    mRequest.setRawHeader("accept", "application/json");

    if(!AuthName.length() || !AuthValue.length()) {
        QFile authFile("auth_tokens.json");
        authFile.open(QIODevice::ReadOnly | QIODevice::Text);
        if(!authFile.isOpen())
            throw std::invalid_argument("file: " + authFile.fileName().toStdString() + " doesn't opened!");

        QJsonObject obj = QJsonDocument::fromJson(QString(authFile.readAll()).toUtf8()).object();
        AuthName = obj["name"].toString().toStdString();
        AuthValue = obj["value"].toString().toStdString();
    }
    mRequest.setRawHeader(AuthName.c_str(), AuthValue.c_str());

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
