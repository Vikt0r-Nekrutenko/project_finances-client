#include <QJsonArray>
#include <QJsonObject>

#include "debtmodelhandler.hpp"

DebtModelHandler::DebtModelHandler()
{
    std::ifstream file(LocalPath + "debts.txt");

    if(file.is_open()) {
        while(true) {
            DebtModel tmp(0, "", 0);
            tmp.load(file);
            if(tmp.version() > mVersion)
                mVersion = tmp.version();

            if(file.eof())
                break;

            mDebts.push_back(tmp);

            if(tmp.mIsForCreate) {
                mDebts.back().create();
            }
            if(tmp.mIsForUpdate) {
                mDebts.back().update();
            }
            if(tmp.mIsForDelete) {
                mDebts.back().remove();
            }
        }
        file.close();
    }
    get("debts/");
}

DebtModelHandler::~DebtModelHandler()
{
    std::ofstream file(LocalPath + "debts.txt");
    for(auto &model : mDebts) {
        model.save(file);
    }
    file.close();
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
    if(mDebts[index].mIsForDelete == false)
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

std::vector<DebtModel>::iterator DebtModelHandler::findByName(const std::string &name)
{
    return std::find_if(mDebts.begin(), mDebts.end(), [&](const DebtModel &model){
        return model.name() == name;
    });
}
