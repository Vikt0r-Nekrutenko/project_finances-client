#include <QEventLoop>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include "datamodel.hpp"
#include <mutex>

std::vector<std::string> &log()
{
    return CoreLog;
}

std::string
    DataModel::AuthValue,
    DataModel::MainPath;
    
std::mutex netAMMtx;

QNetworkReply *DataModel::sendCRUDRequest(const std::string &additionalPath, const QJsonObject &data, const std::string &request, const QUrlQuery &params)
{
    if(!MainPath.length() || !AuthValue.length()) {
        AuthValue = Settings["value"].toString().toStdString();
        MainPath = Settings["url"].toString().toStdString();
    }

    netAMMtx.lock();
        QNetworkAccessManager *mManager = new QNetworkAccessManager();
    netAMMtx.unlock();
    
    QUrl url{(MainPath + additionalPath).c_str()};
    if(!params.isEmpty())
        url.setQuery(params);
    QNetworkRequest mRequest {url};

    mRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    mRequest.setRawHeader("accept", "application/json");
    mRequest.setRawHeader("authorization", AuthValue.c_str());

    QEventLoop loop;

    QObject::connect(mManager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    QNetworkReply *reply = mManager->sendCustomRequest(mRequest, request.c_str(), QJsonDocument(data).toJson());

    loop.exec();

    return reply;
}

RemoteStatus DataModel::replyHandler(QNetworkReply *reply, const std::string &noErrorMsg) const
{
    auto status = RemoteStatus::Failure;
    if(reply->error() == QNetworkReply::NoError) {
        CoreLog.push_back(noErrorMsg);
        status = RemoteStatus::Success;
    } else {
        CoreLog.push_back(reply->errorString().toStdString());
    }
    reply->deleteLater();
    return status;
}

void loadSettings()
{
    QFile settingsFile("settings.json");
    settingsFile.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!settingsFile.isOpen())
        throw std::invalid_argument("file: " + settingsFile.fileName().toStdString() + " doesn't opened!");

    Settings = QJsonDocument::fromJson(QString(settingsFile.readAll()).toUtf8()).object();
    settingsFile.close();
}

void saveSettings()
{
    QFile settingsFile("settings.json");
    settingsFile.open(QIODevice::WriteOnly | QIODevice::Text);
    if(!settingsFile.isOpen())
        throw std::invalid_argument("file: " + settingsFile.fileName().toStdString() + " doesn't opened!");

    settingsFile.write(QJsonDocument(Settings).toJson());
    settingsFile.close();
}

QJsonObject &settings()
{
    return Settings;
}
