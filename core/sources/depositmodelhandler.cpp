#include <QJsonArray>
#include <QJsonObject>
#include "depositmodelhandler.hpp"

DepositModelHandler::DepositModelHandler()
{
    RemoteStatus status = get("deposits/");
    std::ifstream file("deposits.txt");
    if(file.is_open()) {
        while(true) {
            DepositModel tmp("", 0);
            tmp.load(file);

            if(file.eof()) {
                break;
            } else if(status == RemoteStatus::Failure) {
                mDeposits.push_back(tmp);
            } else if(status == RemoteStatus::Success) {
                if(tmp.mIsCreated)
                    addNewDeposit(tmp.mName, tmp.mBalance);
                else if(tmp.mIsChanched || tmp.mIsDeleted)
                    mDeposits.push_back(tmp);
            }
        }
        file.close();
    }
}

DepositModelHandler::~DepositModelHandler()
{
    std::ofstream file("deposits.txt");
    for(auto &model : mDeposits) {
        model.save(file);
    }
    file.close();
}

void DepositModelHandler::addNewDeposit(const std::string &name, int balance)
{
    mDeposits.push_back(DepositModel{name, balance});
    try {
        mDeposits.back().create();
    } catch(...) {
        mDeposits.back().mIsCreated = true;
    }
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
