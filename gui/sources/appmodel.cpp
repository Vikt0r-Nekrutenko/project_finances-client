#include "appmodel.hpp"

AppModel::AppModel()
{
    std::unique_ptr<std::thread> dmhTh { Deposits.asyncConstruct() };
    std::unique_ptr<std::thread> cmhTh { Categories.asyncConstruct() };
    std::unique_ptr<std::thread> bmhTh { Debts.asyncConstruct() };
    std::unique_ptr<std::thread> omhTh { Operations.asyncConstruct() };

    dmhTh->join();
    cmhTh->join();
    bmhTh->join();
    omhTh->join();

    MonoBankDataHandler mdh;
    if(mdh.usd() != mdh.quotes().end()) {
        float usd = mdh.usd()->sell;
        mQuotes[1].second = usd;
    }
}

AppModel::~AppModel()
{
    std::unique_ptr<std::thread> dmhTh { Deposits.asyncDestruct() };
    std::unique_ptr<std::thread> cmhTh { Categories.asyncDestruct() };
    std::unique_ptr<std::thread> bmhTh { Debts.asyncDestruct() };
    std::unique_ptr<std::thread> omhTh { Operations.asyncDestruct() };

    dmhTh->join();
    cmhTh->join();
    bmhTh->join();
    omhTh->join();
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
    OperationModel *model = Operations.query.at(id);
    const std::string type = model->rawCategory(Categories).type();
    if(type == "positive" || type == "earn")
        Deposits.decreaseBalance(model->amount());
    else if(type == "negative")
        Deposits.increaseBalance(model->amount());
    Operations.deleteOperation(id);
    selectOperationsList();
}

void AppModel::selectOperationsList()
{
    Operations.query.select().filterByDeposit(Deposits.selectedDeposit()->name());
    if(SelectedYear == 0 || SelectedMonth == 0) {
        Operations.query.filterByCurrentYear().filterByCurrentMonth();
        return;
    }
    Operations.query.filterByYear(SelectedYear).filterByMonth(SelectedMonth);
    return;
}

void AppModel::selectedOperationChangeAmount(int amount)
{
    const std::string type = Operations.selectedOperation()->rawCategory(Categories).type();
    if(type == "positive" || type == "earn") {
        Deposits.decreaseBalance(Operations.selectedOperation()->amount());
        Deposits.increaseBalance(amount);
    } else if(type == "negative") {
        Deposits.increaseBalance(Operations.selectedOperation()->amount());
        Deposits.decreaseBalance(amount);
    }
    Operations.changeAmount(amount);
}

void AppModel::selectedOperationChangeCategory(const std::string &category)
{
    const std::string type = Operations.selectedOperation()->rawCategory(Categories).type();
    if(type == "positive" || type == "earn") {
        Deposits.decreaseBalance(Operations.selectedOperation()->amount());
    } else if(type == "negative") {
        Deposits.increaseBalance(Operations.selectedOperation()->amount());
    }

    Operations.changeCategory(category);

    const std::string newType = Operations.selectedOperation()->rawCategory(Categories).type();
    if(newType == "positive" || newType == "earn") {
        Deposits.increaseBalance(Operations.selectedOperation()->amount());
    } else if(newType == "negative") {
        Deposits.decreaseBalance(Operations.selectedOperation()->amount());
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

int AppModel::calcTotalEarn()
{
    return mTotalEarn = OperationModelHandler::Query(&Operations).select().filterByCategoryType(Categories, "earn").sum();
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
    OperationModelHandler::Query operationsByYear =   OperationModelHandler::Query(&Operations).select().filterByCurrentYear();
    OperationModelHandler::Query earnOperations =     OperationModelHandler::Query(operationsByYear).filterByCategoryType(Categories, "earn");
    OperationModelHandler::Query positiveOperations = OperationModelHandler::Query(operationsByYear).filterByCategoryType(Categories, "positive");
    OperationModelHandler::Query negativeOperations = OperationModelHandler::Query(operationsByYear).filterByCategoryType(Categories, "negative");

    mYearProfit = earnOperations.sum() + positiveOperations.sum();
    mYearLoss = negativeOperations.sum();

    mYearPnL = mYearProfit - mYearLoss;

    mMonthlyProfit = earnOperations.filterByCurrentMonth().sum() + positiveOperations.filterByCurrentMonth().sum();
    mMonthlyLoss = negativeOperations.filterByCurrentMonth().sum();

    mMonthlyPnL = mMonthlyProfit - mMonthlyLoss;

    mTodayProfit = earnOperations.filterByCurrentDay().sum() + positiveOperations.filterByCurrentDay().sum();
    mTodayLoss = negativeOperations.filterByCurrentDay().sum();

    mTodayPnL = mTodayProfit - mTodayLoss;
}

void AppModel::calcPnLsByCategories()
{
    mPnLsByCategories.clear();
    Categories.query.select();
    OperationModelHandler::Query currentYearOperations = OperationModelHandler::Query(&Operations).select().filterByCurrentYear();
    OperationModelHandler::Query currentMonthOperations = OperationModelHandler::Query(currentYearOperations).filterByCurrentMonth();
    OperationModelHandler::Query currentDayOperations = OperationModelHandler::Query(currentMonthOperations).filterByCurrentDay();

    for(auto &category : Categories.query) {
        int pnlByYear = OperationModelHandler::Query(currentYearOperations).filterByCategoryName(category->name()).sum();
        int pnlByMonth = OperationModelHandler::Query(currentMonthOperations).filterByCategoryName(category->name()).sum();
        int pnlByDay = OperationModelHandler::Query(currentDayOperations).filterByCategoryName(category->name()).sum();
        if(category->type() == "negative")
            mPnLsByCategories.push_back({category, -pnlByDay, -pnlByMonth, -pnlByYear});
        else
            mPnLsByCategories.push_back({category, +pnlByDay, +pnlByMonth, +pnlByYear});
    }
}

void AppModel::updateStats()
{
    calcTotalEarn();
    calcTotalDeposits();
    calcTotalDebts();
    calcPnLs();
}

void AppModel::switchCurrency()
{
    mCurrentCurrencyId ^= 1;
}
