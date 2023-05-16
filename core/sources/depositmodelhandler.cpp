#include <QJsonArray>
#include <QJsonObject>
#include "depositmodelhandler.hpp"

DepositModelHandler::DepositModelHandler()
{
    try {
        get("deposits/");
    } catch(...) {
        std::ifstream file("deposits.txt");
        if(file.is_open()) {
            while(!file.eof()) {
                DepositModel tmp("", 0);
                tmp.load(file);
            }
        }
    }
}

void DepositModelHandler::addNewDeposit(const std::string &name, int balance)
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
    mDeposits.erase(mDeposits.begin() + depositIndex);
}

void DepositModelHandler::parseJsonArray(const QJsonArray &replyJsonArray)
{
    mDeposits.clear();
    for (const auto &var : replyJsonArray) {
        mDeposits.push_back(DepositModel{
            var.toObject()["name"].toString().toStdString(),
            var.toObject()["balance"].toInt()
        });
    }
}

const std::vector<DepositModel> &DepositModelHandler::deposits() const
{
    return mDeposits;
}

std::vector<DepositModel> &DepositModelHandler::deposits()
{
    return mDeposits;
}

std::vector<DepositModel>::iterator DepositModelHandler::findByName(const std::string &name)
{
    return std::find_if(mDeposits.begin(), mDeposits.end(), [&](const DepositModel &model){
        return model.name() == name;
    });
}
