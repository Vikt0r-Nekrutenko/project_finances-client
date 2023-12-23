#ifndef DATAMODEL_HPP
#define DATAMODEL_HPP

#include <QNetworkReply>
#include <QUrlQuery>
#include <vector>

#include "core_global.h"

static std::vector<std::string> CoreLog;

std::vector<std::string> CORE_EXPORT &log();

enum class RemoteStatus
{
    Success, Failure,
};

class CORE_EXPORT DataModel
{
public:

    inline int version() const { return mVersion; }
    inline void setVersion(int value) { mVersion = value; }

protected:

    virtual QNetworkReply *sendCRUDRequest(const std::string &additionalPath, const QJsonObject &data, const std::string &request, const QUrlQuery &params = {});
    RemoteStatus replyHandler(QNetworkReply *reply, const std::string &noErrorMsg) const;

private:

    static std::string
        AuthValue,
        MainPath;

protected:

    static QJsonObject mSettings;
    int mVersion {0};
};

#endif // DATAMODEL_HPP
