#include <QJsonArray>
#include <QJsonObject>
#include "depositmodelhandler.hpp"

DepositModelHandler::DepositModelHandler()
{
    get("deposits/");
}

void DepositModelHandler::addNewDeposit(const QString &name, int balance)
{
    mDeposits.push_back(DepositModel{name, balance});
    mDeposits.back().create();
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
    for (const auto &var : replyJsonArray) {
        mDeposits.push_back(DepositModel{
            var.toObject()["name"].toString(),
            var.toObject()["balance"].toInt()
        });
    }
}

const QVector<DepositModel> &DepositModelHandler::deposits() const
{
    return mDeposits;
}

QVector<DepositModel> &DepositModelHandler::deposits()
{
    return mDeposits;
}

QList<DepositModel>::iterator DepositModelHandler::findByName(const QString &name)
{
    return std::find_if(mDeposits.begin(), mDeposits.end(), [&](const DepositModel &model){
        return model.name() == name;
    });
}
