#include "appmodel.hpp"




const QVector<DepositModel> &AppModel::deposits() const
{
    return mDepositHandler.deposits();
}

void AppModel::deleteDeposit(int index)
{
    mDepositHandler.deleteDeposit(index);
}

void AppModel::addNewDeposit(const char *name, int balance)
{
    mDepositHandler.addNewDeposit(name, balance);
}

void AppModel::changeBalance(int index, int balance)
{
    mDepositHandler.updateBalance(index, balance);
}

int AppModel::getTotalBalanceOnDeposits() const
{
    int result = 0;

    for(const auto &deposit : deposits()) {
        result += deposit.balance();
    }
    return result;
}
