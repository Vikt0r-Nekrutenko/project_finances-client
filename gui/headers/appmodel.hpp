#ifndef APPMODEL_HPP
#define APPMODEL_HPP

#include "headers/depositmodelhandler.hpp"
#include "headers/debtmodelhandler.hpp"
#include "headers/categorymodelhandler.hpp"
#include "headers/operationmodelhandler.hpp"

class AppModel
{
public:

    DepositModelHandler Deposits;
    DebtModelHandler Debts;
    CategoryModelHandler Categories;

    DepositModel *selectedDeposit()
    {
        return mSelectedDeposit;
    }

    const OperationModelHandler &operations() const
    {
        return mOperations;
    }

    void addNewOperation(const std::string &date, int amount, const std::string &category)
    {
        mOperations.addNewOperation(date, mSelectedDeposit->name(), amount, category);
    }

    void deleteOperation(int id)
    {
        mOperations.deleteOperation(id);
    }

    void selectDeposit(size_t id)
    {
        mSelectedDeposit = &Deposits.deposits().at(id);
    }

private:

    OperationModelHandler mOperations;
    DepositModel *mSelectedDeposit = nullptr;
};

#endif // APPMODEL_HPP
