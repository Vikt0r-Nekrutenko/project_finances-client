#ifndef DATAMODEL_HPP
#define DATAMODEL_HPP

#include <QNetworkReply>

enum class RequestType
{
    GET, POST, PUT, DELETE,
};

const QMap<const RequestType, const QString> Requests
{
    { RequestType::GET,     "GET" },
    { RequestType::POST,    "POST" },
    { RequestType::PUT,     "PUT" },
    { RequestType::DELETE,  "DELETE" },
};

class DataModel
{
public:
    virtual QNetworkReply *sendCRUDRequest(const QString &addtionalPath, const QJsonObject &data, const QString &request);
};

#endif // DATAMODEL_HPP
