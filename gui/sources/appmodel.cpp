#include "appmodel.hpp"
#include <unordered_map>

AppModel::AppModel()
{
    MonoBankDataHandler mdh;
    if(mdh.usd() != mdh.quotes().end()) {
        float usd = mdh.usd()->sell;
        mQuotes[1].second = usd;
    }
    try {
        // selectFavoriteCategories(0, 1, 10);
    } catch(...) { }
}

void AppModel::addNewOperation(const std::string &date, int amount, const std::string &category)
{
    Operations.addNewOperation(date, Deposits.selectedDeposit()->name(), amount, category);
    const std::string type = (*Categories.query.findByName(category))->type();
    if(type == "positive" || type == "earn")
        Deposits.increaseBalance(amount);
    else if(type == "negative")
        Deposits.decreaseBalance(amount);
    selectOperationsList();
}

void AppModel::deleteOperation(int id)
{
    id = std::distance(Operations.operations().begin(), Operations.at(id));
    const std::string type = Operations.operations().at(id).rawCategory(Categories).type();
    if(type == "positive" || type == "earn")
        Deposits.decreaseBalance(Operations.operations().at(id).amount());
    else if(type == "negative")
        Deposits.increaseBalance(Operations.operations().at(id).amount());
    Operations.deleteOperation(id);
    selectOperationsList();
}

void AppModel::selectOperationsList()
{
    mOperationsList.select().filterByDeposit(Deposits.selectedDeposit()->name());
    if(SelectedYear == 0 || SelectedMonth == 0) {
        mOperationsList.filterByCurrentYear().filterByCurrentMonth();
        return;
    }
    mOperationsList.filterByYear(SelectedYear).filterByMonth(SelectedMonth);
    return;
}

void AppModel::selectOperation(int id)
{
    mSelectedOperationId = std::distance(Operations.operations().begin(), Operations.at(id));
}

OperationModel &AppModel::selectedOperation()
{
    return Operations.operations().at(mSelectedOperationId);
}

void AppModel::selectedOperationChangeDate(const std::string &date)
{
    OperationModel &selectedOperation = Operations.operations().at(mSelectedOperationId);
    Operations.updateOperation(mSelectedOperationId, date, selectedOperation.deposit(), selectedOperation.amount(), selectedOperation.category());
}

void AppModel::selectedOperationChangeDeposit(const std::string &deposit)
{
    OperationModel &selectedOperation = Operations.operations().at(mSelectedOperationId);
    Operations.updateOperation(mSelectedOperationId, selectedOperation.date(), deposit, selectedOperation.amount(), selectedOperation.category());
}

void AppModel::selectedOperationChangeAmount(int amount)
{
    OperationModel &selectedOperation = Operations.operations().at(mSelectedOperationId);
    const std::string type = selectedOperation.rawCategory(Categories).type();
    if(type == "positive" || type == "earn") {
        Deposits.decreaseBalance(selectedOperation.amount());
        Deposits.increaseBalance(amount);
    } else if(type == "negative") {
        Deposits.increaseBalance(selectedOperation.amount());
        Deposits.decreaseBalance(amount);
    }
    Operations.updateOperation(mSelectedOperationId, selectedOperation.date(), selectedOperation.deposit(), amount, selectedOperation.category());
}

void AppModel::selectedOperationChangeCategory(const std::string &category)
{
    OperationModel &selectedOperation = Operations.operations().at(mSelectedOperationId);
    const std::string type = selectedOperation.rawCategory(Categories).type();
    if(type == "positive" || type == "earn") {
        Deposits.decreaseBalance(selectedOperation.amount());
    } else if(type == "negative") {
        Deposits.increaseBalance(selectedOperation.amount());
    }

    Operations.updateOperation(mSelectedOperationId, selectedOperation.date(), selectedOperation.deposit(), selectedOperation.amount(), category);

    const std::string newType = selectedOperation.rawCategory(Categories).type();
    if(newType == "positive" || newType == "earn") {
        Deposits.increaseBalance(selectedOperation.amount());
    } else if(newType == "negative") {
        Deposits.decreaseBalance(selectedOperation.amount());
    }
}

void AppModel::addOrChangeDebt(const std::string &name, int amount, const std::string &lendOrRepay)
{
    std::vector<DebtModel *>::const_iterator debt = Debts.query.findByName(name);
    std::vector<DebtModel *>::const_iterator constBegin = Debts.query.begin();

    if(debt == Debts.query.end()) {
        Debts.addNewDebt(name, amount);
    } else if(lendOrRepay == "Lend") {
        Debts.increaseAmount(int(std::distance(constBegin, debt)), amount);
    } else if(lendOrRepay == "Repay") {
        Debts.decreaseAmount(int(std::distance(constBegin, debt)), amount);
    }
}

void AppModel::selectFavoriteCategories(int id1, int id2, int id3)
{
    const CategoryModel &cat1 = *Categories.query.at(id1);
    const CategoryModel &cat2 = *Categories.query.at(id2);
    const CategoryModel &cat3 = *Categories.query.at(id3);

    int sum1 = OperationHandlerQuery(&Operations).select().filterByCurrentYear().filterByCurrentMonth().filterByCategoryName(cat1.name()).sum();
    int sum2 = OperationHandlerQuery(&Operations).select().filterByCurrentYear().filterByCurrentMonth().filterByCategoryName(cat2.name()).sum();
    int sum3 = OperationHandlerQuery(&Operations).select().filterByCurrentYear().filterByCurrentMonth().filterByCategoryName(cat3.name()).sum();

    mFavoriteCategories.at(0) = {cat1.name(), cat1.type() == "negative" ? -sum1 : sum1};
    mFavoriteCategories.at(1) = {cat2.name(), cat2.type() == "negative" ? -sum2 : sum2};
    mFavoriteCategories.at(2) = {cat3.name(), cat3.type() == "negative" ? -sum3 : sum3};
}

int AppModel::calcTotalEarn()
{
    return mTotalEarn = OperationHandlerQuery(&Operations).select().filterByCategoryType(Categories, "earn").sum();
}

int AppModel::calcTotalDeposits()
{
    return mTotalDeposits = Deposits.query.sum();
}

int AppModel::calcTotalDebts()
{
    return mTotalDebts = Debts.query.sum();
}

void AppModel::calcPnLs()
{
    OperationHandlerQuery yearEarnOperations = OperationHandlerQuery(&Operations).select().filterByCurrentYear().filterByCategoryType(Categories, "earn");
    OperationHandlerQuery yearPositiveOperations = OperationHandlerQuery(&Operations).select().filterByCurrentYear().filterByCategoryType(Categories, "positive");
    OperationHandlerQuery yearNegativeOperations = OperationHandlerQuery(&Operations).select().filterByCurrentYear().filterByCategoryType(Categories, "negative");

    mYearProfit = yearEarnOperations.sum() + yearPositiveOperations.sum();
    mYearLoss = yearNegativeOperations.sum();

    mYearPnL = mYearProfit - mYearLoss;

    mMonthlyProfit = yearEarnOperations.filterByCurrentMonth().sum() + yearPositiveOperations.filterByCurrentMonth().sum();
    mMonthlyLoss = yearNegativeOperations.filterByCurrentMonth().sum();

    mMonthlyPnL = mMonthlyProfit - mMonthlyLoss;

    mTodayProfit = yearEarnOperations.filterByCurrentDay().sum() + yearPositiveOperations.filterByCurrentDay().sum();
    mTodayLoss = yearNegativeOperations.filterByCurrentDay().sum();

    mTodayPnL = mTodayProfit - mTodayLoss;
}

void AppModel::calcMinMaxLoss()
{
    OperationHandlerQuery monthlyOperations = OperationHandlerQuery(&Operations)
                                                  .select()
                                                  .filterByCurrentYear()
                                                  .filterByCurrentMonth()
                                                  .filterByCategoryType(Categories, "negative");
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

    auto min = Categories.query.findByName(mMinMaxLoss.first.first);
    auto max = Categories.query.findByName(mMinMaxLoss.second.first);

    if(min == Categories.query.end())
        mMinMaxLoss.first = {"None", 0};
    else
        mMinMaxLoss.first.second = -mMinMaxLoss.first.second;

    if(max == Categories.query.end())
        mMinMaxLoss.second = {"None", 0};
    else
        mMinMaxLoss.second.second = -mMinMaxLoss.second.second;
}

void AppModel::calcMonthlyGroupPnL()
{
    OperationHandlerQuery monthlyOperations = OperationHandlerQuery(&Operations).select().filterByCurrentYear().filterByCurrentMonth();
    for(auto &category : Categories.query) {
        OperationHandlerQuery tmp = monthlyOperations;
        int value = tmp.filterByCategoryName(category->name()).sum();
        mMonthlyGroupPnls.push_back({category, category->type() == "negative" ? -value : value});
    }
}

void AppModel::updateStats()
{
    // calcTotalEarn();
    // calcTotalDeposits();
    // calcTotalDebts();
    // calcPnLs();
    // calcMinMaxLoss();
}

void AppModel::switchCurrency()
{
    mCurrentCurrencyId ^= 1;
}
