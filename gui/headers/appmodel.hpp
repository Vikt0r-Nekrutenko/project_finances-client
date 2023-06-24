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

    using FavoriteCategoryList = std::vector<std::pair<std::string, int>>;
    using MinMaxLoss = std::pair<std::pair<std::string, int>, std::pair<std::string, int>>;

    const OperationHandlerQuery &operationsList() const
    {
        return mOperationsList;
    }

    const FavoriteCategoryList &favoriteCategories() const
    {
        return mFavoriteCategories;
    }

    const MinMaxLoss &minMaxLoss() const
    {
        return mMinMaxLoss;
    }

    DepositModel *selectedDeposit()
    {
        return mSelectedDeposit;
    }

    int totalEarn() const
    {
        return mTotalEarn;
    }

    int totalDeposits() const
    {
        return mTotalDeposits;
    }

    int totalDebts() const
    {
        return mTotalDebts;
    }

    int totalPnL() const
    {
        return mTotalDeposits - mTotalEarn;
    }

    int todayPnL() const
    {
        return mTodayPnL;
    }

    int monthlyPnL() const
    {
        return mMonthlyPnL;
    }

    int yearPnL() const
    {
        return mYearPnL;
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

    void selectFavoriteCategories(int id1, int id2, int id3)
    {
        const CategoryModel &cat1 = Categories.categories().at(id1);
        const CategoryModel &cat2 = Categories.categories().at(id2);
        const CategoryModel &cat3 = Categories.categories().at(id3);

        int sum1 = OperationHandlerQuery(&Operations).select().filterByCurrentYear().filterByCurrentMonth().filterByCategoryName(cat1.name()).sum();
        int sum2 = OperationHandlerQuery(&Operations).select().filterByCurrentYear().filterByCurrentMonth().filterByCategoryName(cat2.name()).sum();
        int sum3 = OperationHandlerQuery(&Operations).select().filterByCurrentYear().filterByCurrentMonth().filterByCategoryName(cat3.name()).sum();

        mFavoriteCategories[0] = {cat1.name(), cat1.type() == "negative" ? -sum1 : sum1};
        mFavoriteCategories[1] = {cat2.name(), cat2.type() == "negative" ? -sum2 : sum2};
        mFavoriteCategories[2] = {cat3.name(), cat3.type() == "negative" ? -sum3 : sum3};
    }

    int calcTotalEarn()
    {
        return mTotalEarn = OperationHandlerQuery(&Operations).select().filterByCategoryType(Categories, "earn").sum();
    }

    int calcTotalDeposits()
    {
        for(const auto &deposit : Deposits.deposits())
            mTotalDeposits += deposit.balance();
        return mTotalDeposits;
    }

    int calcTotalDebts()
    {
        for(const auto &debt : Debts.debts())
            mTotalDebts += debt.amount();
        return mTotalDebts;
    }

    void calcPnLs()
    {
        OperationHandlerQuery yearEarnOperations = OperationHandlerQuery(&Operations).select().filterByCurrentYear().filterByCategoryType(Categories, "earn");
        OperationHandlerQuery yearNegativeOperations = OperationHandlerQuery(&Operations).select().filterByCurrentYear().filterByCategoryType(Categories, "negative");

        mYearPnL = yearEarnOperations.sum() - yearNegativeOperations.sum();
        mMonthlyPnL = yearEarnOperations.filterByCurrentMonth().sum() - yearNegativeOperations.filterByCurrentMonth().sum();
        mTodayPnL = yearEarnOperations.filterByCurrentDay().sum() - yearNegativeOperations.filterByCurrentDay().sum();
    }

    void calcMinMaxLoss()
    {
        OperationHandlerQuery monthlyOperations = OperationHandlerQuery(&Operations).select().filterByCurrentYear().filterByCurrentMonth();
        std::unordered_map<std::string, int> sumByCategories;
        for(const auto &operation : monthlyOperations) {
            sumByCategories[operation->category()] += operation->amount();
        }

        mMinMaxLoss.first.second = INT_MAX;
        mMinMaxLoss.second.second = 0;

        for(const auto &pair : sumByCategories) {
            if(pair.second < mMinMaxLoss.first.second)
                mMinMaxLoss.first = pair;
            if(pair.second > mMinMaxLoss.second.second)
                mMinMaxLoss.second = pair;
        }

        if(Categories.findByName(mMinMaxLoss.first.first)->type() == "negative")
            mMinMaxLoss.first.second = -mMinMaxLoss.first.second;
        if(Categories.findByName(mMinMaxLoss.second.first)->type() == "negative")
            mMinMaxLoss.second.second = -mMinMaxLoss.second.second;
    }

private:

    OperationHandlerQuery mOperationsList = OperationHandlerQuery(&Operations);
    FavoriteCategoryList mFavoriteCategories = FavoriteCategoryList(3);
    MinMaxLoss mMinMaxLoss;
    DepositModel *mSelectedDeposit = nullptr;
    int mTotalEarn = 0;
    int mTotalDeposits = 0;
    int mTotalDebts = 0;
    int mTodayPnL = 0,
        mMonthlyPnL = 0,
        mYearPnL = 0;
    int mSelectedOperationId = 0;

public:

    int SelectedYear = 0, SelectedMonth = 0;
};

#endif // APPMODEL_HPP
