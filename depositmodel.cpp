#include <QJsonObject>
#include "depositmodel.hpp"

DepositModel::DepositModel(const QString &name, int balance)
    : mName{name}, mBalance{balance} {}

void DepositModel::create()
{
    QJsonObject newDepo {
        {"name", mName },
        {"balance", mBalance }
    };

    QNetworkReply *reply = sendCRUDRequest("deposits/", newDepo, Requests[RequestType::POST]);
    replyHandler(reply, "Deposit added successfully!");
}
