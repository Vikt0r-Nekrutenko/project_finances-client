#include <QJsonArray>
#include <QJsonObject>
#include "depositmodelhandler.hpp"

DepositModelHandler::DepositModelHandler()
{
    std::ifstream file(LocalPath + "deposits.txt");

    if(file.is_open()) {
        while(file.eof() == false) {
            mDeposits.push_back({"", 0});
            mDeposits.back().load(file);
            if(mDeposits.back().version() > mVersion)
                mVersion = mDeposits.back().version();
        }
        file.close();
    }
    get("deposits/");
    query.select();
}

DepositModelHandler::~DepositModelHandler()
{
    std::ofstream file(LocalPath + "deposits.txt");
    size_t i = 0;
    for(auto &model : mDeposits) {
        if(++i != mDeposits.size())
            model.syncAndSave(file, mVersion, "\n");
        else
            model.syncAndSave(file, mVersion, "");
    }
    file.close();
}

void DepositModelHandler::addNewDeposit(const std::string &name, int balance)
{
    ++mVersion;
    std::vector<DepositModel>::iterator searchedDeposit = std::find_if(mDeposits.begin(), mDeposits.end(), [&](const DepositModel &model){
        return model.name() == name;
    });
    if(searchedDeposit == mDeposits.end()) {
        mDeposits.push_back({name, balance});
        mDeposits.back().mIsForCreate = true;
    } else {
        searchedDeposit->mBalance = balance;
        searchedDeposit->mIsDeleted = false;
        searchedDeposit->mIsForDelete = false;
        searchedDeposit->mIsForCreate = false;
        searchedDeposit->mIsForUpdate = true;
    }
    query.select();
}

void DepositModelHandler::selectDeposit(int index)
{
    mSelectedDeposit = query.at(index);
}

void DepositModelHandler::updateBalance(int index, int newBalance)
{
    ++mVersion;
    query.at(index)->mBalance = newBalance;
    query.at(index)->mIsForUpdate = true;
}

void DepositModelHandler::deleteDeposit(int index)
{
    ++mVersion;
    query.at(index)->mIsDeleted = true;
    query.at(index)->mIsForDelete = true;
    query.select();
}

void DepositModelHandler::increaseBalance(int amount)
{
    ++mVersion;
    mSelectedDeposit->mBalance += amount;
    mSelectedDeposit->mIsForUpdate = true;
}

void DepositModelHandler::decreaseBalance(int amount)
{
    ++mVersion;
    mSelectedDeposit->mBalance -= amount;
    mSelectedDeposit->mIsForUpdate = true;
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

        std::vector<DepositModel>::iterator localTmp = std::find_if(mDeposits.begin(), mDeposits.end(), [&](const DepositModel &model){
            return model.name() == remoteTmp.name();
        });

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

std::vector<DepositModel *>::const_iterator DepositModelHandler::Query::findByName(const std::string &name) const
{
    return std::find_if(begin(), end(), [&](const DepositModel *model) {
        return model->name() == name;
    });
}

DepositModelHandler::Query::Query(DepositModelHandler *handler)
    : mHandler{handler} { }

const DepositModelHandler::Query &DepositModelHandler::Query::select()
{
    clear();
    for(size_t i = 0; i < mHandler->mDeposits.size(); ++i)
        if(mHandler->mDeposits.at(i).mIsDeleted == false)
            push_back(&mHandler->mDeposits.at(i));
    return *this;
}

int DepositModelHandler::Query::sum() const
{
    int result = 0;
    for(auto item : *this) {
        result += item->mBalance;
    }
    return result;
}
