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

            if(tmp.mIsForCreate) {
                mDeposits.back().create();
            }
            if(tmp.isForUpdate()) {
                mDeposits.back().update();
            }
            if(tmp.isForDelete()) {
                mDeposits.back().remove();
            }
        }
        file.close();
    }
    get("deposits/");
}

DepositModelHandler::~DepositModelHandler()
{
    // std::ofstream file(LocalPath + "deposits.txt");
    // for(auto &model : mDeposits) {
    //     model.save(file);
    // }
    // file.close();
}

void DepositModelHandler::addNewDeposit(const std::string &name, int balance)
{
    mDeposits.push_back({name, balance});
    mDeposits.back().mIsForCreate = true;
    addNewChange(mDeposits.size() - 1);
}

void DepositModelHandler::updateBalance(int depositIndex, int newBalance)
{
    mDeposits.at(depositIndex).mBalance = newBalance;
    mDeposits.at(depositIndex).mIsForUpdate = true;
    addNewChange(depositIndex);
}

void DepositModelHandler::deleteDeposit(int depositIndex)
{
    mDeposits.at(depositIndex).mIsDeleted = true;
    mDeposits.at(depositIndex).mIsForDelete = true;
    addNewChange(depositIndex);
}

void DepositModelHandler::applyChanges()
{

}

void DepositModelHandler::parseJsonArray(const QJsonArray &replyJsonArray)
{
    int count = 0;
    for (const auto &var : replyJsonArray) {
        mDeposits.push_back({
            var.toObject()["name"].toString().toStdString(),
            var.toObject()["balance"].toInt(),
            var.toObject()["version"].toInt(),
            bool(var.toObject()["is_deleted"].toInt())
        });
        if(mDeposits.back().version() > mVersion)
            mVersion = mDeposits.back().version();
        ++count;
    }
    log().push_back({"Deposits received: " + std::to_string(count)});
}

void DepositModelHandler::addNewChange(const size_t index)
{
    ++mVersion;
    std::vector<size_t>::iterator curDepIt = std::find_if(mListOfChanges.begin(), mListOfChanges.end(), [&](const size_t &indx) {
        return indx == index;
    });
    if(curDepIt == mListOfChanges.end())
        mListOfChanges.push_back(index);
}

std::vector<DepositModel>::iterator DepositModelHandler::findByName(const std::string &name)
{
    return std::find_if(mDeposits.begin(), mDeposits.end(), [&](const DepositModel &model){
        return model.name() == name;
    });
}
