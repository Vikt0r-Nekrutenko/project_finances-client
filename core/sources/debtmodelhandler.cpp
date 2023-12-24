#include <QJsonArray>
#include <QJsonObject>

#include "debtmodelhandler.hpp"

DebtModelHandler::DebtModelHandler()
{
    syncAndLoad<DebtModel>("debts", mDebts);
    query.select();
}

DebtModelHandler::~DebtModelHandler()
{
    syncAndSave("debts.txt", mDebts);
}

void DebtModelHandler::addNewDebt(const std::string &name, int amount)
{
    addNewItem<DebtModel, std::vector<DebtModel>::iterator>(
        {0, name, amount},
        mDebts,
        [&](const DebtModel &model) {
            return model.mName == name;
        },
        [&](DebtModel &model) {
            model.mAmount = amount;
        });
    query.select();
}

void DebtModelHandler::updateDebt(int index, const std::string &name, int amount)
{
    ++mVersion;
    query.at(index)->mName = name;
    query.at(index)->mAmount = amount;
    query.at(index)->mIsForUpdate = true;
}

void DebtModelHandler::deleteDebt(int index)
{
    deleteItem(query.at(index));
    query.select();
}

void DebtModelHandler::increaseAmount(int index, int amount)
{
    ++mVersion;
    query.at(index)->mAmount += amount;
    query.at(index)->mIsForUpdate = true;
}

void DebtModelHandler::decreaseAmount(int index, int amount)
{
    ++mVersion;
    query.at(index)->mAmount -= amount;
    query.at(index)->mIsForUpdate = true;
}

void DebtModelHandler::parseJsonArray(const QJsonArray &replyJsonArray)
{
    int count = 0;
    for(const auto &var : replyJsonArray) {
        DebtModel remoteTmp{
            var.toObject()["id"].toInt(),
            var.toObject()["name"].toString().toStdString(),
            var.toObject()["amount"].toInt(),
            var.toObject()["version"].toInt(),
            bool(var.toObject()["is_deleted"].toInt())
        };
        merge<DebtModel, std::vector<DebtModel>::iterator>("debts", remoteTmp, mDebts, [&](const DebtModel &model){
            return remoteTmp.id() == model.id();
        });
        ++count;
    }
    log().push_back({"Debts received: " + std::to_string(count)});
}

DebtModelHandler::Query::Query(DebtModelHandler *handler)
    : mHandler{handler} { }

const DebtModelHandler::Query &DebtModelHandler::Query::select()
{
    clear();
    for(size_t i = 0; i < mHandler->mDebts.size(); ++i)
        if(mHandler->mDebts.at(i).mIsDeleted == false)
            push_back(&mHandler->mDebts.at(i));
    return *this;
}

int DebtModelHandler::Query::sum() const
{
    int result = 0;
    for(auto item : *this) {
        result += item->mAmount;
    }
    return result;
}

std::vector<DebtModel *>::const_iterator DebtModelHandler::Query::findByName(const std::string &name) const
{
    return std::find_if(begin(), end(), [&](const DebtModel *model){
        return model->name() == name;
    });
}
