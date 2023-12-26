#ifndef DATAMODEL_HPP
#define DATAMODEL_HPP

#include <QJsonObject>
#include <QNetworkReply>
#include <QUrlQuery>
#include <vector>

#include "core_global.hpp"

static std::vector<std::string> CoreLog;
static QJsonObject Settings;

void CORE_EXPORT loadSettings();
void CORE_EXPORT saveSettings();

std::vector<std::string> CORE_EXPORT &log();
QJsonObject CORE_EXPORT &settings();

enum class RemoteStatus
{
    Success, Failure,
};

class CORE_EXPORT DataModel
{
public:

    virtual ~DataModel() = default;

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

    int mVersion {0};
};

#endif // DATAMODEL_HPP
