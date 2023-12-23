#include <QJsonArray>
#include <QJsonObject>
#include "depositmodelhandler.hpp"

DepositModelHandler::DepositModelHandler()
{
    syncAndLoad<DepositModel>("deposits", mDeposits);
    query.select();
}

DepositModelHandler::~DepositModelHandler()
{
    syncAndSave("deposits.txt", mDeposits);
}

void DepositModelHandler::addNewDeposit(const std::string &name, int balance)
{
    addNewItem<std::vector<DepositModel>::iterator>(
        {name, balance},
        mDeposits,
        [&](const DepositModel &model) {
            return model.mName == name;
        },
        [&](DepositModel &model) {
            model.mBalance = balance;
        });
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
    // ++mVersion;
    // query.at(index)->mIsDeleted = true;
    // query.at(index)->mIsForDelete = true;
    deleteItem(query.at(index));
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

        merge<DepositModel, std::vector<DepositModel>::iterator>("deposits", remoteTmp, mDeposits, [&](const DepositModel &model){
            return remoteTmp.name() == model.name();
        });
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
