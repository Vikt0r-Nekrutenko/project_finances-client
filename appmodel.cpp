#include "appmodel.hpp"




const QVector<DepositModel> &AppModel::deposits() const
{
    return mDepositHandler.deposits();
}

int AppModel::getTotalBalanceOnDeposits() const
{
    int result = 0;

    for(const auto &deposit : deposits()) {
        result += deposit.balance();
    }
    return result;
}
