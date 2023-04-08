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

const std::string MainPath = "https://grhin0.pythonanywhere.com/api/";

class DataModel
{
public:
    virtual QNetworkReply *sendCRUDRequest(const std::string &additionalPath, const QJsonObject &data, const std::string &request);
    void replyHandler(QNetworkReply *reply, const std::string &noErrorMsg) const;

private:

    std::string mAuthName, mAuthValue;
};

#endif // DATAMODEL_HPP
