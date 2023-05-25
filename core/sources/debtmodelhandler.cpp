#include <QJsonArray>
#include <QJsonObject>

#include "debtmodelhandler.hpp"

DebtModelHandler::DebtModelHandler()
{
    get("debts/");
}

void DebtModelHandler::addNewDebt(const std::string &name, int amount)
{
    mDebts.push_back(DebtModel(
                              mDebts.empty() ? 0 : mDebts.back().mId + 1,
                              name,
                              amount));
    mDebts.back().create();
}

void DebtModelHandler::updateDebt(int index, const std::string &name, int amount)
{
    mDebts[index].mName = name;
    mDebts[index].mAmount = amount;
    mDebts[index].update();
}

void DebtModelHandler::deleteDebt(int index)
{
    mDebts[index].remove();
    mDebts.erase(mDebts.begin() + index);
}

void DebtModelHandler::parseJsonArray(const QJsonArray &replyJsonArray)
{
    mDebts.clear();
    for(const auto &var : replyJsonArray) {
        mDebts.push_back(DebtModel{
            var.toObject()["id"].toInt(),
            var.toObject()["name"].toString().toStdString(),
            var.toObject()["amount"].toInt()
        });
    }
}

const std::vector<DebtModel> &DebtModelHandler::debts() const
{
    return mDebts;
}

std::vector<DebtModel>::iterator DebtModelHandler::findByName(const std::string &name)
{
    return std::find_if(mDebts.begin(), mDebts.end(), [&](const DebtModel &model){
        return model.name() == name;
    });
}
