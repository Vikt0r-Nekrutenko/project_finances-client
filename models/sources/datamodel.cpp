#include <QEventLoop>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include "datamodel.hpp"
#include "renderer.hpp"

QNetworkReply *DataModel::sendCRUDRequest(const QString &additionalPath, const QJsonObject &data, const QString &request)
{
    static QNetworkAccessManager mManager;
    QNetworkRequest mRequest {QUrl(MainPath + additionalPath)};

    mRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    mRequest.setRawHeader("accept", "application/json");

    if(!mAuthName.length() || !mAuthValue.length()) {
        QFile authFile("auth_tokens.json");
        authFile.open(QIODevice::ReadOnly | QIODevice::Text);
        if(!authFile.isOpen())
            throw std::invalid_argument("file: " + authFile.fileName().toStdString() + " doesn't opened!");

        QJsonObject obj = QJsonDocument::fromJson(QString(authFile.readAll()).toUtf8()).object();
        mAuthName = obj["name"].toString();
        mAuthValue = obj["value"].toString();
    }
    mRequest.setRawHeader(mAuthName.toUtf8(), mAuthValue.toUtf8());

    QEventLoop loop;

    QObject::connect(&mManager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    QNetworkReply *reply = mManager.sendCustomRequest(mRequest, request.toUtf8(), QJsonDocument(data).toJson());

    loop.exec();

    return reply;
}

void DataModel::replyHandler(QNetworkReply *reply, const QString &noErrorMsg) const
{
    if(reply->error() == QNetworkReply::NoError) {
        stf::Renderer::log << stf::endl << noErrorMsg.toStdString();
    } else {
        stf::Renderer::log << stf::endl << reply->errorString().toStdString();
    }
    reply->deleteLater();
}
