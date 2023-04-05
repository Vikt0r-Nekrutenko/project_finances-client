#ifndef DATAMODEL_HPP
#define DATAMODEL_HPP

#include <QNetworkReply>

enum class RequestType
{
    GET_RQ,
    POST_RQ,
    PUT_RQ,
    DELETE_RQ
};

const QString MainPath = "http://127.0.0.1:8000/api/";

class DataModel
{
public:
    virtual QNetworkReply *sendCRUDRequest(const QString &additionalPath, const QJsonObject &data, const QString &request);
    void replyHandler(QNetworkReply *reply, const QString &noErrorMsg) const;
};

#endif // DATAMODEL_HPP
