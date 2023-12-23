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
    // get("debts/");
}

DebtModelHandler::~DebtModelHandler()
{
    // std::ofstream file(LocalPath + "debts.txt");
    // for(auto &model : mDebts) {
    //     model.save(file);
    // }
    // file.close();
}

void DebtModelHandler::addNewDebt(const std::string &name, int amount)
{
    mDebts.push_back(DebtModel{0, name, amount, ++mVersion});
    mDebts.back().create();
}

void DebtModelHandler::updateDebt(int index, const std::string &name, int amount)
{
    mDebts[index].mName = name;
    mDebts[index].mAmount = amount;
    mDebts[index].mVersion = ++mVersion;
    mDebts[index].update();
}

void DebtModelHandler::deleteDebt(int index)
{
    mDebts[index].mVersion = ++mVersion;
    mDebts[index].mIsDeleted = true;
    mDebts[index].remove();
}

void DebtModelHandler::increaseAmount(int index, int amount)
{

}

void DebtModelHandler::decreaseAmount(int index, int amount)
{

}

void DebtModelHandler::parseJsonArray(const QJsonArray &replyJsonArray)
{
    int count = 0;
    for(const auto &var : replyJsonArray) {
        mDebts.push_back(DebtModel{
            var.toObject()["id"].toInt(),
            var.toObject()["name"].toString().toStdString(),
            var.toObject()["amount"].toInt(),
            var.toObject()["version"].toInt(),
            bool(var.toObject()["is_deleted"].toInt())
        });
        if(mDebts.back().version() > mVersion)
            mVersion = mDebts.back().version();
        ++count;
    }
    log().push_back({"Debts received: " + std::to_string(count)});
}

std::vector<DebtModel>::iterator DebtModelHandler::findByName(const std::string &name)
{
    return std::find_if(mDebts.begin(), mDebts.end(), [&](const DebtModel &model){
        return model.name() == name;
    });
}

DebtModelHandler::Query::Query(DebtModelHandler *handler)
{

}

const DebtModelHandler::Query &DebtModelHandler::Query::select()
{

}

int DebtModelHandler::Query::sum() const
{

}

std::vector<DebtModel *>::const_iterator DebtModelHandler::Query::findByName(const std::string &name) const
{

}
