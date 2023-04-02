#include "appmodel.hpp"

const char *BadDateFormat::what() const noexcept
{
    return "Date format is YYYY-MM-DD";
}

const QVector<DepositModel> &AppModel::deposits() const
{
    return mDepositHandler.deposits();
}

const QVector<OperationModel> &AppModel::operations() const
{
    return mOperationHandler.operations();
}

void AppModel::deleteDeposit(int index)
{
    if(index >= mDepositHandler.deposits().size())
        throw std::out_of_range("Deposit with that index does not exitst.");
    mDepositHandler.deleteDeposit(index);
}

void AppModel::addNewDeposit(const char *name, int balance)
{
    mDepositHandler.addNewDeposit(name, balance);
}

void AppModel::changeBalance(int index, int balance)
{
    if(index >= mDepositHandler.deposits().size())
        throw std::out_of_range("Deposit with that index does not exitst.");
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

void AppModel::addNewOperation(const char *date, const char *deposit, int amount, const char *category)
{
    mOperationHandler.addNewOperation(date, deposit, amount, category);
}
