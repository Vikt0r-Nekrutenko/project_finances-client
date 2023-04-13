#include "appmodel.hpp"

const std::vector<DepositModel> &AppModel::deposits() const
{
    return mDepositHandler.deposits();
}

const std::vector<OperationModel> &AppModel::operations() const
{
    return mOperationHandler.operations();
}

const std::vector<CategoryModel> &AppModel::categories() const
{
    return mCategoryHandler.categories();
}

const std::vector<CategoryModel> &AppModel::favCategories() const
{
    return mFavCategories;
}

const std::pair<std::pair<int, std::string>, std::pair<int, std::string>> &AppModel::minMaxLosses() const
{
    return mMinMaxLosses;
}

const std::vector<std::pair<std::string, int> > &AppModel::sumByFavCategories() const
{
    return mSumByFavCategories;
}

const std::vector<DebtModel> &AppModel::debts() const
{
    return mDebtHandler.debts();
}

std::vector<DepositModel> &AppModel::deposits()
{
    return mDepositHandler.deposits();
}

OperationModelHandler *AppModel::operationHandler()
{
    return &mOperationHandler;
}

int AppModel::sumOfAllEarnOperations() const
{
    return mSumOfAllEarnOperations;
}

int AppModel::sumOfAllDeposits() const
{
    return mSumOfAllDeposits;
}

int AppModel::sumOfAllDebts() const
{
    return mSumOfAllDebts;
}

int AppModel::totalPnL() const
{
    return mTotalPnL;
}

int AppModel::todayPnL() const
{
    return mTodayPnL;
}

int AppModel::weekPnL() const
{
    return mWeekPnL;
}

int AppModel::monthPnL() const
{
    return mMonthPnL;
}

int AppModel::yearPnL() const
{
    return mYearPnL;
}

void AppModel::updateStats()
{
    mSumOfAllEarnOperations = getSumOfAllEarnOperations();
    mSumOfAllDeposits = getSumOfAllDeposits();
    mSumOfAllDebts = getSumOfAllDebts();
    mTodayPnL = getTodayPnL();
    mWeekPnL = getWeekPnL();
    mMonthPnL = getMonthPnL();
    mYearPnL = getYearPnl();
    mTotalPnL = mSumOfAllDeposits - mSumOfAllEarnOperations;

    mSumByFavCategories.clear();
    for(const auto &favcat : mFavCategories)
        mSumByFavCategories.push_back({favcat.name(), getSum30DaysOfOperationsByCategory(favcat)});

    getMinMaxLossesBy30Days();
}

void AppModel::updateAllHandlers()
{
    mDepositHandler.get("deposits/");
    mOperationHandler.get("operations/");
    mCategoryHandler.get("categories/");
    mDebtHandler.get("debts/");
}

void AppModel::selectFavCategories(int index1, int index2, int index3)
{
    if(index1 >= (int)mCategoryHandler.categories().size() ||
        index2 >= (int)mCategoryHandler.categories().size() ||
        index3 >= (int)mCategoryHandler.categories().size())
        throw std::out_of_range("category index doesn't exist");

    mFavCategories.clear();
    mFavCategories.insert(mFavCategories.end(), {
                           mCategoryHandler.categories().at(index1),
                           mCategoryHandler.categories().at(index2),
                           mCategoryHandler.categories().at(index3)});
}

void AppModel::deleteDeposit(int index)
{
    if(index >= (int)mDepositHandler.deposits().size() || index < 0)
        throw std::out_of_range("Deposit with that index does not exitst.");
    mDepositHandler.deleteDeposit(index);
}

void AppModel::addNewDeposit(const char *name, int balance)
{
    mDepositHandler.addNewDeposit(name, balance);
}

void AppModel::changeBalance(int index, int balance)
{
    if(index >= (int)mDepositHandler.deposits().size() || index < 0)
        throw std::out_of_range("Deposit with that index does not exitst.");
    mDepositHandler.updateBalance(index, balance);
}

int AppModel::getSumOfAllDeposits() const
{
    int result = 0;

    for(const auto &deposit : deposits()) {
        result += deposit.balance();
    }
    return result;
}

int AppModel::getSumOfAllDebts() const
{
    int result = 0;

    for(const auto &debt : mDebtHandler.debts()) {
        result += debt.amount();
    }
    return result;
}

void AppModel::addNewLendOperation(const char *date, const char *deposit, int amount, const char *name)
{
    addNewOperation(date, deposit, amount, "Lend");
    addOrChangeDebtByName(name, amount, "Lend");
}

void AppModel::addNewRepayOperation(const char *date, const char *deposit, int amount, const char *name)
{
    addNewOperation(date, deposit, amount, "Repay");
    addOrChangeDebtByName(name, amount, "Repay");
}

void AppModel::addNewOperation(const char *date, const char *deposit, int amount, const char *category)
{
    auto depo = mDepositHandler.findByName(deposit);
    if(depo == mDepositHandler.deposits().end())
        throw std::out_of_range("Deposit with that name does not exitst.");

    mOperationHandler.addNewOperation(date, deposit, amount, category);

    auto cat = mCategoryHandler.findByName(category);
    updateDepositBalanceByCategoryType(cat, depo, +amount);
    depo->update();
}

void AppModel::changeOperation(int index, const char *date, const char *deposit, int amount, const char *category)
{
    if(index >= (int)mOperationHandler.operations().size() || index < 0)
        throw std::out_of_range("Operation with that index does not exitst.");

    const std::string &oldCategory = mOperationHandler.operations().at(index).category();
    const int oldAmount = mOperationHandler.operations().at(index).amount();
    auto cat = mCategoryHandler.findByName(oldCategory);
    auto depo = mDepositHandler.findByName(deposit);

    if(depo == mDepositHandler.deposits().end())
        throw std::out_of_range("Deposit with that name does not exitst.");

    updateDepositBalanceByCategoryType(cat, depo, -oldAmount);

    mOperationHandler.updateOperation(index, date, deposit, amount, category);
    cat = mCategoryHandler.findByName(category);

    if(cat == mCategoryHandler.categories().end())
        throw std::out_of_range("Category with that name does not exitst.");

    updateDepositBalanceByCategoryType(cat, depo, +amount);
    depo->update();
}

void AppModel::deleteOperation(int index)
{
    if(index >= (int)mOperationHandler.operations().size() || index < 0)
        throw std::out_of_range("Operation with that index does not exitst.");

    const std::string &oldCategoryName = mOperationHandler.operations().at(index).category();
    const int oldAmount = mOperationHandler.operations().at(index).amount();
    auto categoryModel = mCategoryHandler.findByName(oldCategoryName);
    auto depositModel = mDepositHandler.findByName(mOperationHandler.operations().at(index).deposit());

    updateDepositBalanceByCategoryType(categoryModel, depositModel, -oldAmount);
    mOperationHandler.deleteOperation(index);
    depositModel->update();
}

void AppModel::deleteCategory(int index)
{
    if(index >= (int)mCategoryHandler.categories().size() || index < 0)
        throw std::out_of_range("Category with that index does not exitst.");
    mCategoryHandler.deleteCategory(index);
}

void AppModel::addNewCategory(const char *name, const char *type)
{
    mCategoryHandler.addNewCategory(name, type);
}

void AppModel::addNewDebt(const char *name, int amount)
{
    mDebtHandler.addNewDebt(name, amount);
}

void AppModel::changeDebt(int index, const char *name, int amount)
{
    if(index >= (int)mDebtHandler.debts().size() || index < 0)
        throw std::out_of_range("Debt with that index does not exitst.");
    mDebtHandler.updateDebt(index, name, amount);
}

void AppModel::deleteDebt(int index)
{
    if(index >= (int)mDebtHandler.debts().size() || index < 0)
        throw std::out_of_range("Debt with that index does not exitst.");
    mDebtHandler.deleteDebt(index);
}

int AppModel::getSum30DaysOfOperationsByCategory(const CategoryModel &category) const
{
    int result = 0;
    for(const auto &operation : mOperationHandler.operations()) {
        const QDateTime opDate = QDateTime().fromString(operation.date().c_str(), "yyyy-MM-dd");
        const QDateTime time   = QDateTime().currentDateTime().addDays(-30);
        const QDateTime today  = QDateTime().currentDateTime();
        if(opDate >= time && opDate <= today && operation.category() == category.name()) {
            result += operation.amount();
        }
    }
    if(category.type() == "negative")
        return -result;
    return result;
}


void AppModel::updateDepositBalanceByCategoryType(std::vector<CategoryModel>::iterator &category, std::vector<DepositModel>::iterator &deposit, int amount)
{
    if(category->type() == "negative") {
        deposit->decreaseBalance(amount);
    } else {
        deposit->increaseBalance(amount);
    }
}

int AppModel::getSumOfOperationsByCategoryType(const std::vector<const OperationModel *> &operations, const std::string &categoryType) const
{
    int result = 0;
    for(const auto &category : mCategoryHandler.categories())
        if(category.type() == categoryType)
            for(const auto &operation : operations)
                if(operation->category() == category.name())
                    result += operation->amount();
    return result;
}

int AppModel::getSumOfAllEarnOperations() const
{
    int result = 0;
    for(const auto &category : mCategoryHandler.categories())
        if(category.type() == "earn")
            for(const auto &operation : mOperationHandler.operations())
                if(operation.category() == category.name())
                    result += operation.amount();
    return result;
}

int AppModel::getTodayPnL() const
{
    return getPnLByDays(-1);
}

int AppModel::getWeekPnL() const
{
    return getPnLByDays(-7);
}

int AppModel::getMonthPnL() const
{
    return getPnLByDays(-30);
}

int AppModel::getYearPnl() const
{
    return getPnLByDays(-365);
}

void AppModel::addOrChangeDebtByName(const char *name, const int amount, const char *lendOrRepay)
{
    auto debt = mDebtHandler.findByName(name);
    if(debt == mDebtHandler.debts().end()) {
        mDebtHandler.addNewDebt(name, amount);
    } else if(std::string(lendOrRepay) == "Lend"){
        debt->increase(amount);
        debt->update();
    } else if(std::string(lendOrRepay) == "Repay"){
        debt->decrease(amount);
        debt->update();
    }
}

int AppModel::getPnLByDays(int days) const
{
    if(mOperationHandler.operations().empty())
        return 0;

    std::vector<const OperationModel *> operations;
    for(const auto &operation : mOperationHandler.operations()) {
        const QDateTime opDate = QDateTime().fromString(operation.date().c_str(), "yyyy-MM-dd");
        const QDateTime time   = QDateTime().currentDateTime().addDays(days);
        const QDateTime today  = QDateTime().currentDateTime();
        if(opDate >= time && opDate <= today)
            operations.push_back(&operation);
    }

    const std::string &today = QDateTime().currentDateTime().toString("yyyy-MM-dd").toStdString();
    int negOpSum = getSumOfOperationsByCategoryType(operations, "negative");
    int posOpSum = getSumOfOperationsByCategoryType(operations, "positive") + getSumOfOperationsByCategoryType(operations, "earn");
    return posOpSum - negOpSum;
}

void AppModel::getMinMaxLossesBy30Days()
{
    if(mOperationHandler.operations().empty())
        return;

    std::vector<const OperationModel *> operations;
    for(const auto &operation : mOperationHandler.operations()) {
        const QDateTime opDate = QDateTime().fromString(operation.date().c_str(), "yyyy-MM-dd");
        const QDateTime time   = QDateTime().currentDateTime().addDays(-30);
        const QDateTime today  = QDateTime().currentDateTime();
        if(opDate >= time && opDate <= today)
            operations.push_back(&operation);
    }

    std::map<std::string, int> operationsSum;
    for(size_t i = 0; i < operations.size(); ++i) {
        auto category = mCategoryHandler.findByName(operations.at(i)->category());
        if(category->type() == "negative") {
            operationsSum[operations.at(i)->category()] += operations.at(i)->amount();
        }
    }

    mMinMaxLosses.first = //Min
    mMinMaxLosses.second = { operationsSum.begin()->second, operationsSum.begin()->first }; //Max

    for(const auto& mm : operationsSum) {
        if(mm.second < mMinMaxLosses.first.first)
            mMinMaxLosses.first = { mm.second, mm.first };
        if(mm.second > mMinMaxLosses.second.first)
            mMinMaxLosses.second = { mm.second, mm.first };
    }
}
