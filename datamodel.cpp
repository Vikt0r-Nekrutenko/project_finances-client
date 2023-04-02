#include <QEventLoop>
#include <QJsonDocument>
#include "datamodel.hpp"
#include "renderer.hpp"

QNetworkReply *DataModel::sendCRUDRequest(const QString &additionalPath, const QJsonObject &data, const QString &request)
{
    static QNetworkAccessManager mManager;
    QNetworkRequest mRequest {QUrl(MainPath + additionalPath)};

    mRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    mRequest.setRawHeader("accept", "application/json");

    QEventLoop loop;

    QObject::connect(&mManager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    QNetworkReply *reply = mManager.sendCustomRequest(mRequest, request.toUtf8(), QJsonDocument(data).toJson());

    loop.exec();

    return reply;
}

void DataModel::replyHandler(QNetworkReply *reply, const QString &noErrorMsg) const
{
    if(reply->error() == QNetworkReply::NoError) {
        stf::Renderer::log << reply->errorString().toStdString() << stf::endl;
    } else {
        stf::Renderer::log << noErrorMsg.toStdString() << stf::endl;
    }
    reply->deleteLater();
}
