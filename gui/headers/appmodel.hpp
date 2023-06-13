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

    void selectDeposit(size_t id)
    {
        mSelectedDeposit = &Deposits.deposits().at(id);
    }

private:

    DepositModel *mSelectedDeposit = nullptr;
};

#endif // APPMODEL_HPP
