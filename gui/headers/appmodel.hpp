#ifndef APPMODEL_HPP
#define APPMODEL_HPP

#include "headers/depositmodelhandler.hpp"
#include "headers/debtmodelhandler.hpp"
#include "headers/categorymodelhandler.hpp"
#include "headers/operationmodelhandler.hpp"
#include "headers/queryresult.hpp"

class AppModel
{
public:

    DepositModelHandler Deposits;
    DebtModelHandler Debts;
    CategoryModelHandler Categories;
    OperationModelHandler Operations;

    OperationHandlerQuery mOperationsList = OperationHandlerQuery(&Operations);

    DepositModel *selectedDeposit()
    {
        return mSelectedDeposit;
    }

    void addNewOperation(const std::string &date, int amount, const std::string &category)
    {
        Operations.addNewOperation(date, mSelectedDeposit->name(), amount, category);
        const std::string type = Categories.findByName(category)->type();
        if(type == "positive" || type == "earn")
            mSelectedDeposit->increaseBalance(amount);
        else if(type == "negative")
            mSelectedDeposit->decreaseBalance(amount);
        mSelectedDeposit->update();
        selectOperationsList();
    }

    void deleteOperation(int id)
    {
        id = std::distance(Operations.operations().begin(), Operations.at(id));
        const std::string type = Operations.operations().at(id).rawCategory(Categories).type();
        if(type == "positive" || type == "earn")
            mSelectedDeposit->decreaseBalance(Operations.operations().at(id).amount());
        else if(type == "negative")
            mSelectedDeposit->increaseBalance(Operations.operations().at(id).amount());
        mSelectedDeposit->update();
        Operations.deleteOperation(id);
        selectOperationsList();
    }

    void selectOperationsList()
    {
        if(mSelectedDeposit == nullptr)
            return;

        mOperationsList.select().filterByDeposit(mSelectedDeposit->name());
        if(SelectedYear == 0 || SelectedMonth == 0) {
            mOperationsList.filterByCurrentYear().filterByCurrentMonth();
            return;
        }
        mOperationsList.filterByYear(SelectedYear).filterByMonth(SelectedMonth);
        return;
    }

    void selectOperation(int id)
    {
        mSelectedOperationId = std::distance(Operations.operations().begin(), Operations.at(id));
    }

    OperationModel &selectedOperation()
    {
        return Operations.operations().at(mSelectedOperationId);
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
        const std::string type = selectedOperation.rawCategory(Categories).type();
        if(type == "positive" || type == "earn") {
            mSelectedDeposit->decreaseBalance(selectedOperation.amount());
            mSelectedDeposit->increaseBalance(amount);
        } else if(type == "negative") {
            mSelectedDeposit->increaseBalance(selectedOperation.amount());
            mSelectedDeposit->decreaseBalance(amount);
        }
        Operations.updateOperation(mSelectedOperationId, selectedOperation.date(), selectedOperation.deposit(), amount, selectedOperation.category());
        mSelectedDeposit->update();
    }

    void selectedOperationChangeCategory(const std::string &category)
    {
        OperationModel &selectedOperation = Operations.operations().at(mSelectedOperationId);
        const std::string type = selectedOperation.rawCategory(Categories).type();
        if(type == "positive" || type == "earn") {
            mSelectedDeposit->decreaseBalance(selectedOperation.amount());
        } else if(type == "negative") {
            mSelectedDeposit->increaseBalance(selectedOperation.amount());
        }

        Operations.updateOperation(mSelectedOperationId, selectedOperation.date(), selectedOperation.deposit(), selectedOperation.amount(), category);

        const std::string newType = selectedOperation.rawCategory(Categories).type();
        if(newType == "positive" || newType == "earn") {
            mSelectedDeposit->increaseBalance(selectedOperation.amount());
        } else if(newType == "negative") {
            mSelectedDeposit->decreaseBalance(selectedOperation.amount());
        }
        mSelectedDeposit->update();
    }

    void selectDeposit(size_t id)
    {
        mSelectedDeposit = &Deposits.deposits().at(id);
    }

    void addOrChangeDebt(const std::string &name, int amount, const std::string &lendOrRepay)
    {
        std::vector<DebtModel>::const_iterator debt = Debts.findByName(name);
        if(debt == Debts.debts().end()) {
            Debts.addNewDebt(name, amount);
        } else if(lendOrRepay == "Lend") {
            Debts.updateDebt(int(std::distance(Debts.debts().begin(), debt)), debt->name(), debt->amount() + amount);
        } else if(lendOrRepay == "Repay") {
            Debts.updateDebt(int(std::distance(Debts.debts().begin(), debt)), debt->name(), debt->amount() - amount);
        }
    }

private:

    DepositModel *mSelectedDeposit = nullptr;
    int mSelectedOperationId = 0;

public:

    int SelectedYear = 0, SelectedMonth = 0;
};

#endif // APPMODEL_HPP
