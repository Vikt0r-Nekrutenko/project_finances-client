#include <QJsonArray>
#include <QJsonObject>
#include "depositmodelhandler.hpp"

std::thread *DepositModelHandler::asyncConstruct()
{
    return new std::thread{[this](){
        syncAndLoad<DepositModel>("deposits", mDeposits);
        query.select();
    }};
}

std::thread *DepositModelHandler::asyncDestruct()
{
    return new std::thread{[this](){
        syncAndSave("deposits.txt", mDeposits);
    }};
}

void DepositModelHandler::addNewDeposit(const std::string &name, int balance)
{
    addNewItem<DepositModel, std::vector<DepositModel>::iterator>(
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

void DepositModelHandler::makeTransfer(int fromId, int toId, int amount)
{
    ++mVersion;
    query.at(fromId)->mBalance -= amount;
    query.at(toId)->mBalance += amount;
    query.at(fromId)->mIsForUpdate = true;
    query.at(toId)->mIsForUpdate = true;
}

void DepositModelHandler::parseJsonArray(const QJsonArray &replyJsonArray)
{
    parseAndMerge<DepositModel, std::vector<DepositModel>::iterator>(
        "deposits",
        replyJsonArray,
        mDeposits,
        [&](const DepositModel &remoteModel, const DepositModel &localModel) {
            return remoteModel.mName == localModel.mName;
        },
        [&](const QJsonValue &var) {
            return DepositModel {
                var.toObject()["name"].toString().toStdString(),
                var.toObject()["balance"].toInt(),
                var.toObject()["version"].toInt(),
                bool(var.toObject()["is_deleted"].toInt())
            };
        });
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
    return std::accumulate(begin(), end(), 0, [](int accumulator, const DepositModel *model) { return accumulator + model->mBalance; });
}
