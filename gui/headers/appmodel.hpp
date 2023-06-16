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
    OperationModelHandler Operations;

    DepositModel *selectedDeposit()
    {
        return mSelectedDeposit;
    }

    void addNewOperation(const std::string &date, int amount, const std::string &category)
    {
        Operations.addNewOperation(date, mSelectedDeposit->name(), amount, category);
    }

    void deleteOperation(int id)
    {
        Operations.deleteOperation(id);
    }

    void selectOperation(int id)
    {
        mSelectedOperationId = id;
    }

    void selectedOperationChangeDate(const std::string &date)
    {
        OperationModel &selectedOperation = Operations.operations().at(mSelectedOperationId);
        Operations.updateOperation(mSelectedOperationId, date, selectedOperation.deposit(), selectedOperation.amount(), selectedOperation.category());
    }

    void selectedOperationChangeDeposit(const std::string &deposit)
    {
        OperationModel &selectedOperation = Operations.operations().at(mSelectedOperationId);
        Operations.updateOperation(mSelectedOperationId, selectedOperation.date(), deposit, selectedOperation.amount(), selectedOperation.category());
    }

    void selectedOperationChangeAmount(int amount)
    {
        OperationModel &selectedOperation = Operations.operations().at(mSelectedOperationId);
        Operations.updateOperation(mSelectedOperationId, selectedOperation.date(), selectedOperation.deposit(), amount, selectedOperation.category());
    }

    void selectedOperationChangeCategory(const std::string &category)
    {
        OperationModel &selectedOperation = Operations.operations().at(mSelectedOperationId);
        Operations.updateOperation(mSelectedOperationId, selectedOperation.date(), selectedOperation.deposit(), selectedOperation.amount(), category);
    }

    void selectDeposit(size_t id)
    {
        mSelectedDeposit = &Deposits.deposits().at(id);
    }

private:

    DepositModel *mSelectedDeposit = nullptr;
    int mSelectedOperationId = 0;

public:

    int SelectedYear = 0, SelectedMonth = 0;
};

#endif // APPMODEL_HPP
