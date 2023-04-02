#include <QJsonArray>
#include "depositmodelhandler.hpp"

DepositModelHandler::DepositModelHandler()
{
    get("deposits/");
}

void DepositModelHandler::addNewDeposit(const QString &name, int balance)
{
    mDeposits.push_back(DepositModel{name, balance});
}

void DepositModelHandler::updateBalance(int depositIndex, int newBalance)
{
    mDeposits[depositIndex].mBalance = newBalance;
    mDeposits[depositIndex].update();
}

void DepositModelHandler::deleteDeposit(int depositIndex)
{
    mDeposits[depositIndex].remove();
    mDeposits.removeAt(depositIndex);
}

void DepositModelHandler::parseJsonArray(const QJsonArray &replyJsonArray)
{
    mDeposits.clear();
    foreach (const auto &var, replyJsonArray) {
        mDeposits.push_back(DepositModel{
            var.toObject()["name"].toString(),
            var.toObject()["balance"].toInt()
        });
    }
}
