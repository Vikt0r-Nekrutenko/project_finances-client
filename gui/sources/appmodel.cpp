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
        selectFavoriteCategories(0, 1, 10);
    } catch(...) { }
}

const OperationHandlerQuery &AppModel::operationsList() const
{
    return mOperationsList;
}

const AppModel::FavoriteCategoryList &AppModel::favoriteCategories() const
{
    return mFavoriteCategories;
}

const AppModel::MinMaxLoss &AppModel::minMaxLoss() const
{
    return mMinMaxLoss;
}

const std::pair<std::string, float> &AppModel::currentCurrency() const
{
    return mQuotes[mCurrentCurrencyId];
}

const std::vector<std::pair<CategoryModel *, int> > &AppModel::monthlyPnlsByCategories() const
{
    return mMonthlyGroupPnls;
}

DepositModel *AppModel::selectedDeposit()
{
    return mSelectedDeposit;
}

int AppModel::totalEarn() const
{
    return mTotalEarn;
}

int AppModel::totalDeposits() const
{
    return mTotalDeposits;
}

int AppModel::totalDebts() const
{
    return mTotalDebts;
}

int AppModel::totalPnL() const
{
    return mTotalDeposits - mTotalEarn;
}

int AppModel::todayPnL() const
{
    return float(mTodayPnL) / mQuotes[mCurrentCurrencyId].second;
}

int AppModel::todayProfit() const
{
    return float(mTodayProfit) / mQuotes[mCurrentCurrencyId].second;
}

int AppModel::todayLoss() const
{
    return float(mTodayLoss) / mQuotes[mCurrentCurrencyId].second;
}

int AppModel::monthlyPnL() const
{
    return float(mMonthlyPnL) / mQuotes[mCurrentCurrencyId].second;
}

int AppModel::monthlyProfit() const
{
    return float(mMonthlyProfit) / mQuotes[mCurrentCurrencyId].second;
}

int AppModel::monthlyLoss() const
{
    return float(mMonthlyLoss) / mQuotes[mCurrentCurrencyId].second;
}

int AppModel::yearPnL() const
{
    return float(mYearPnL) / mQuotes[mCurrentCurrencyId].second;
}

int AppModel::yearProfit() const
{
    return float(mYearProfit) / mQuotes[mCurrentCurrencyId].second;
}

int AppModel::yearLoss() const
{
    return float(mYearLoss) / mQuotes[mCurrentCurrencyId].second;
}

void AppModel::addNewOperation(const std::string &date, int amount, const std::string &category)
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

void AppModel::deleteOperation(int id)
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

void AppModel::selectOperationsList()
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
        mSelectedDeposit->decreaseBalance(selectedOperation.amount());
        mSelectedDeposit->increaseBalance(amount);
    } else if(type == "negative") {
        mSelectedDeposit->increaseBalance(selectedOperation.amount());
        mSelectedDeposit->decreaseBalance(amount);
    }
    Operations.updateOperation(mSelectedOperationId, selectedOperation.date(), selectedOperation.deposit(), amount, selectedOperation.category());
    mSelectedDeposit->update();
}

void AppModel::selectedOperationChangeCategory(const std::string &category)
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

void AppModel::selectDeposit(size_t id)
{
    mSelectedDeposit = &Deposits.deposits().at(id);
}

void AppModel::addOrChangeDebt(const std::string &name, int amount, const std::string &lendOrRepay)
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

void AppModel::selectFavoriteCategories(int id1, int id2, int id3)
{
    const CategoryModel &cat1 = Categories.categories().at(id1);
    const CategoryModel &cat2 = Categories.categories().at(id2);
    const CategoryModel &cat3 = Categories.categories().at(id3);

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
    mTotalDeposits = 0;
    for(const auto &deposit : Deposits.deposits())
        mTotalDeposits += deposit.balance();
    return mTotalDeposits;
}

int AppModel::calcTotalDebts()
{
    mTotalDebts = 0;
    for(const auto &debt : Debts.debts())
        mTotalDebts += debt.amount();
    return mTotalDebts;
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

    auto min = Categories.findByName(mMinMaxLoss.first.first);
    auto max = Categories.findByName(mMinMaxLoss.second.first);

    if(min == Categories.categories().end())
        mMinMaxLoss.first = {"None", 0};
    else if(min->type() == "negative")
        mMinMaxLoss.first.second = -mMinMaxLoss.first.second;

    if(max == Categories.categories().end())
        mMinMaxLoss.second = {"None", 0};
    else if(max->type() == "negative")
        mMinMaxLoss.second.second = -mMinMaxLoss.second.second;
}

void AppModel::calcMonthlyGroupPnL()
{
    OperationHandlerQuery monthlyOperations = OperationHandlerQuery(&Operations).select().filterByCurrentYear().filterByCurrentMonth();
    for(auto &category : Categories.categories()) {
        OperationHandlerQuery tmp = monthlyOperations;
        int value = tmp.filterByCategoryName(category.name()).sum();
        mMonthlyGroupPnls.push_back({&category, category.type() == "negative" ? -value : value});
    }
}

void AppModel::updateStats()
{
    calcTotalEarn();
    calcTotalDeposits();
    calcTotalDebts();
    calcPnLs();
    calcMinMaxLoss();
}

void AppModel::switchCurrency()
{
    mCurrentCurrencyId ^= 1;
}
