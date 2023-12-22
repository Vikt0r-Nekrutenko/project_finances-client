#include <QJsonArray>
#include <QJsonObject>
#include "depositmodelhandler.hpp"

DepositModelHandler::DepositModelHandler()
{
    std::ifstream file(LocalPath + "deposits.txt");

    if(file.is_open()) {
        while(true) {
            DepositModel tmp("", 0);
            tmp.load(file);
            if(tmp.version() > mVersion)
                mVersion = tmp.version();

            if(file.eof())
                break;

            mDeposits.push_back(tmp);
        }
        file.close();
    }
    get("deposits/");

}

DepositModelHandler::~DepositModelHandler()
{
    std::ofstream file(LocalPath + "deposits.txt");
    for(auto &model : mDeposits) {
        if(model.isForCreate() && model.isForDelete())
            continue;
        else if(model.mIsForCreate) {
            model.mVersion = mVersion;
            model.create();
            model.mIsForUpdate = false;
        } else if (model.mIsForDelete) {
            model.mVersion = mVersion;
            model.remove();
            model.mIsForUpdate = false;
        } else if (model.mIsForUpdate) {
            model.mVersion = mVersion;
            model.update();
        }
        model.save(file);
    }
    file.close();
}

void DepositModelHandler::addNewDeposit(const std::string &name, int balance)
{
    ++mVersion;
    mDeposits.push_back({name, balance});
    mDeposits.back().mIsForCreate = true;
}

void DepositModelHandler::updateBalance(int depositIndex, int newBalance)
{
    ++mVersion;
    mDeposits.at(depositIndex).mBalance = newBalance;
    mDeposits.at(depositIndex).mIsForUpdate = true;
}

void DepositModelHandler::deleteDeposit(int depositIndex)
{
    ++mVersion;
    mDeposits.at(depositIndex).mIsDeleted = true;
    mDeposits.at(depositIndex).mIsForDelete = true;
}

std::vector<DepositModel *> DepositModelHandler::currentDeposits()
{

}

void DepositModelHandler::parseJsonArray(const QJsonArray &replyJsonArray)
{
    int count = 0;
    for (const auto &var : replyJsonArray) {
        DepositModel remoteTmp {
            var.toObject()["name"].toString().toStdString(),
            var.toObject()["balance"].toInt(),
            var.toObject()["version"].toInt(),
            bool(var.toObject()["is_deleted"].toInt())
        };

        std::vector<DepositModel>::iterator localTmp = findByName(remoteTmp.name());
        if(localTmp == mDeposits.end())
            mDeposits.push_back(remoteTmp);
        else
            *localTmp = remoteTmp;

        if(mDeposits.back().version() > mVersion)
            mVersion = mDeposits.back().version();
        ++count;
    }
    log().push_back({"Deposits received: " + std::to_string(count)});
}

std::vector<DepositModel>::iterator DepositModelHandler::findByName(const std::string &name)
{
    return std::find_if(mDeposits.begin(), mDeposits.end(), [&](const DepositModel &model){
        return model.name() == name;
    });
}
