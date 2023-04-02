#include "depositmodelhandler.hpp"

DepositModelHandler::DepositModelHandler()
{
    get("deposits/");
}

void DepositModelHandler::addNewDeposit(const QString &name, int balance)
{
    mDeposits.push_back(DepositModel{name, balance});
}

void DepositModelHandler::updateBalance(int depositIndex, int newBalance)
{
    mDeposits[depositIndex].mBalance = newBalance;
    mDeposits[depositIndex].update();
}
