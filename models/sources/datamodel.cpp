#include <QEventLoop>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include "datamodel.hpp"
#include "renderer.hpp"

QNetworkReply *DataModel::sendCRUDRequest(const std::string &additionalPath, const QJsonObject &data, const std::string &request)
{
    static QNetworkAccessManager mManager;
    QNetworkRequest mRequest {QUrl((MainPath + additionalPath).c_str())};

    mRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    mRequest.setRawHeader("accept", "application/json");

    if(!mAuthName.length() || !mAuthValue.length()) {
        QFile authFile("auth_tokens.json");
        authFile.open(QIODevice::ReadOnly | QIODevice::Text);
        if(!authFile.isOpen())
            throw std::invalid_argument("file: " + authFile.fileName().toStdString() + " doesn't opened!");

        QJsonObject obj = QJsonDocument::fromJson(QString(authFile.readAll()).toUtf8()).object();
        mAuthName = obj["name"].toString().toStdString();
        mAuthValue = obj["value"].toString().toStdString();
    }
    mRequest.setRawHeader(mAuthName.c_str(), mAuthValue.c_str());

    QEventLoop loop;

    QObject::connect(&mManager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    QNetworkReply *reply = mManager.sendCustomRequest(mRequest, request.c_str(), QJsonDocument(data).toJson());

    loop.exec();

    return reply;
}

void DataModel::replyHandler(QNetworkReply *reply, const std::string &noErrorMsg) const
{
    if(reply->error() == QNetworkReply::NoError) {
        stf::Renderer::log << stf::endl << noErrorMsg;
    } else {
        stf::Renderer::log << stf::endl << reply->errorString().toStdString();
    }
    reply->deleteLater();
}
