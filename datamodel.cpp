#include <QEventLoop>
#include "datamodel.hpp"

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
