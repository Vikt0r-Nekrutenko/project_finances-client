#ifndef DATAMODEL_HPP
#define DATAMODEL_HPP

#include <QNetworkReply>
#include <vector>

#include "core_global.h"

static std::vector<std::string> CoreLog;

const std::vector<std::string> CORE_EXPORT &log();

enum class RemoteStatus
{
    Success, Failure,
};

class CORE_EXPORT DataModel
{
public:
    virtual QNetworkReply *sendCRUDRequest(const std::string &additionalPath, const QJsonObject &data, const std::string &request);
    RemoteStatus replyHandler(QNetworkReply *reply, const std::string &noErrorMsg) const;

private:

    static std::string
        AuthName,
        AuthValue,
        MainPath;
};

#endif // DATAMODEL_HPP
