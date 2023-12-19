#include <QJsonArray>
#include <QJsonObject>
#include "depositmodelhandler.hpp"

DepositModelHandler::DepositModelHandler()
{
    std::ifstream file(LocalPath + "deposits.txt");
    unsigned index = 0;

    if(file.is_open()) {
        while(true) {
            DepositModel tmp("", 0);
            tmp.load(file);
            if(tmp.version() > mVersion)
                mVersion = tmp.version();

            if(file.eof()) //{
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
            // } else if(status == RemoteStatus::Failure) {
            // } else if(status == RemoteStatus::Success) {
            // if(tmp.mIsCreated)
            //        addNewDeposit(tmp.name(), tmp.balance());
            //     if(tmp.mIsChanched)
            //         updateBalance(index, tmp.balance());
            //     if(tmp.mIsDeleted)
            //         deleteDeposit(index);
            // }
            ++index;
        }
        file.close();
    }
    RemoteStatus status = get("deposits/");
}

DepositModelHandler::~DepositModelHandler()
{
    std::ofstream file(LocalPath + "deposits.txt");
    for(auto &model : mDeposits) {
        model.save(file);
    }
    file.close();
}

void DepositModelHandler::addNewDeposit(const std::string &name, int balance)
{
    mDeposits.push_back(DepositModel{name, balance, ++mVersion});
    mDeposits.back().create();
}

void DepositModelHandler::updateBalance(int depositIndex, int newBalance)
{
    mDeposits[depositIndex].mBalance = newBalance;
    mDeposits[depositIndex].mVersion = ++mVersion;
    mDeposits[depositIndex].update();
}

void DepositModelHandler::deleteDeposit(int depositIndex)
{
    mDeposits[depositIndex].mVersion = ++mVersion;
    mDeposits[depositIndex].remove();
    // if(mDeposits[depositIndex].mIsDeleted == false)
    //     mDeposits.erase(mDeposits.begin() + depositIndex);
}

void DepositModelHandler::parseJsonArray(const QJsonArray &replyJsonArray)
{
    int count = 0;
    // mDeposits.clear();
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
    log().push_back({"Items received: " + std::to_string(count)});
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
