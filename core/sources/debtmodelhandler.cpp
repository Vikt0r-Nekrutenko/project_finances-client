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
    std::ofstream file(LocalPath + "debts.txt");
    for(auto &model : mDebts) {
        model.syncAndSave(file, mVersion);
    }
    file.close();
}

void DebtModelHandler::addNewDebt(const std::string &name, int amount)
{
    ++mVersion;
    std::vector<DebtModel>::iterator searchedDebt = std::find_if(mDebts.begin(), mDebts.end(), [&](const DebtModel &model){
        return model.name() == name;
    });
    if(searchedDebt == mDebts.end()) {
        mDebts.push_back({0, name, amount});
        mDebts.back().mIsForCreate = true;
    } else if(searchedDebt->mIsDeleted) {
        searchedDebt->mAmount = amount;
        searchedDebt->mIsDeleted = searchedDebt->mIsForDelete = false;
        searchedDebt->mIsForUpdate = true;
    }
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
    ++mVersion;
    query.at(index)->mIsDeleted = true;
    query.at(index)->mIsForDelete = true;
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
