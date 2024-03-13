#include <QJsonArray>
#include <QJsonObject>

#include "debtmodelhandler.hpp"

std::thread *DebtModelHandler::asyncConstruct()
{
    return new std::thread{[this](){
        syncAndLoad<DebtModel>("debts", mDebts);
        query.select();
    }};
}

std::thread *DebtModelHandler::asyncDestruct()
{
    return new std::thread{[this](){
        syncAndSave("debts.txt", mDebts);
    }};
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
    parseAndMerge<DebtModel, std::vector<DebtModel>::iterator>(
        "debts",
        replyJsonArray,
        mDebts,
        [](const DebtModel &remoteModel, const DebtModel &localModel) {
            return remoteModel.mId == localModel.mId;
        },
        [](const QJsonValue& var) {
            return DebtModel {
                var.toObject()["id"].toInt(),
                var.toObject()["name"].toString().toStdString(),
                var.toObject()["amount"].toInt(),
                var.toObject()["version"].toInt(),
                bool(var.toObject()["is_deleted"].toInt())
            };
        });
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
    return std::accumulate(begin(), end(), 0, [](int accumulator, const DebtModel *model) { return accumulator + model->mAmount; });
}

std::vector<DebtModel *>::const_iterator DebtModelHandler::Query::findByName(const std::string &name) const
{
    return std::find_if(begin(), end(), [&](const DebtModel *model){
        return model->name() == name;
    });
}
