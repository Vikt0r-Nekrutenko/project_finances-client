#include <QJsonArray>
#include <QJsonObject>
#include "depositmodelhandler.hpp"

DepositModelHandler::DepositModelHandler()
{
    RemoteStatus status = get("deposits/");
    std::ifstream file(LocalPath + "deposits.txt");
    unsigned index = 0;

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
                    addNewDeposit(tmp.name(), tmp.balance());
                if(tmp.mIsChanched)
                    updateBalance(index, tmp.balance());
                if(tmp.mIsDeleted)
                    deleteDeposit(index);
            }
            ++index;
        }
        file.close();
    }
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
    if(mDeposits[depositIndex].mIsDeleted == false)
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
