#include "appmodel.hpp"
#include "renderer.hpp"

const QVector<DepositModel> &AppModel::deposits() const
{
    return mDepositHandler.deposits();
}

const QVector<OperationModel> &AppModel::operations() const
{
    return mOperationHandler.operations();
}

const QVector<CategoryModel> &AppModel::categories() const
{
    return mCategoryHandler.categories();
}

const QVector<CategoryModel> &AppModel::favCategories() const
{
    return mFavCategories;
}

const QVector<QPair<QString, int> > &AppModel::sumByFavCategories() const
{
    return mSumByFavCategories;
}

const QVector<OperationModel> &AppModel::operationsByMonth() const
{
    return mOperationsByMonth;
}

const QVector<DebtModel> &AppModel::debts() const
{
    return mDebtHandler.debts();
}

int AppModel::sumOfAllEarnOperations() const
{
    return mSumOfAllEarnOperations;
}

int AppModel::sumOfAllDeposits() const
{
    return mSumOfAllDeposits;
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
    mTodayPnL = getTodayPnL();
    mWeekPnL = getWeekPnL();
    mMonthPnL = getMonthPnL();
    mYearPnL = getYearPnl();
    mTotalPnL = mSumOfAllDeposits - mSumOfAllEarnOperations;

    mSumByFavCategories.clear();
    for(const auto &favcat : mFavCategories)
        mSumByFavCategories.push_back({favcat.name(), getSum30DaysOfOperationsByCategory(favcat)});

    getOperationsByCurrentMonth();
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
    if(index1 >= mCategoryHandler.categories().size() ||
        index2 >= mCategoryHandler.categories().size() ||
        index3 >= mCategoryHandler.categories().size())
        throw std::out_of_range("category index doesn't exist");

    mFavCategories.clear();
    mFavCategories.append({mCategoryHandler.categories().at(index1),
                           mCategoryHandler.categories().at(index2),
                           mCategoryHandler.categories().at(index3)});
}

void AppModel::getOperationsByCurrentMonth()
{
    const QDate &currentDate = QDate().currentDate();
    getOperationsByMonth(currentDate.year(), currentDate.month());
}

void AppModel::getOperationsByMonth(int year, int month)
{
    mOperationsByMonth.clear();
    for(const auto &operation : mOperationHandler.operations()) {
        const QDate &date = QDateTime().fromString(operation.date(), "yyyy-MM-dd").date();
        if(year == date.year() && month == date.month())
            mOperationsByMonth.push_back(operation);
    }
}

void AppModel::deleteDeposit(int index)
{
    if(index >= mDepositHandler.deposits().size() || index < 0)
        throw std::out_of_range("Deposit with that index does not exitst.");
    mDepositHandler.deleteDeposit(index);
}

void AppModel::addNewDeposit(const char *name, int balance)
{
    mDepositHandler.addNewDeposit(name, balance);
}

void AppModel::changeBalance(int index, int balance)
{
    if(index >= mDepositHandler.deposits().size() || index < 0)
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

void AppModel::addNewLendOperation(const char *date, const char *deposit, int amount, const char *name)
{
    mOperationHandler.addNewOperation(date, deposit, amount, "Lend");

    auto depo = mDepositHandler.findByName(deposit);
    depo->decreaseBalance(amount);
    depo->update();

    auto debt = mDebtHandler.findByName(name);
    if(debt == mDebtHandler.debts().end()) {
        mDebtHandler.addNewDebt(name, amount);
    } else {
        debt->increase(amount);
    }
    debt->update();
}

void AppModel::addNewRepayOperation(const char *date, const char *deposit, int amount, const char *name)
{
    mOperationHandler.addNewOperation(date, deposit, amount, "Repay");

    auto depo = mDepositHandler.findByName(deposit);
    depo->increaseBalance(amount);
    depo->update();

    auto debt = mDebtHandler.findByName(name);
    if(debt == mDebtHandler.debts().end()) {
        mDebtHandler.addNewDebt(name, amount);
    } else {
        debt->decrease(amount);
    }
    debt->update();
}

void AppModel::addNewOperation(const char *date, const char *deposit, int amount, const char *category)
{
    mOperationHandler.addNewOperation(date, deposit, amount, category);

    auto cat = mCategoryHandler.findByName(category);
    auto depo = mDepositHandler.findByName(deposit);

    updateDepositBalanceByCategoryType(cat, depo, +amount);
    depo->update();
}

void AppModel::changeOperation(int index, const char *date, const char *deposit, int amount, const char *category)
{
    if(index >= mOperationHandler.operations().size() || index < 0)
        throw std::out_of_range("Operation with that index does not exitst.");

    const QString &oldCategory = mOperationHandler.operations().at(index).category();
    const int oldAmount = mOperationHandler.operations().at(index).amount();
    auto cat = mCategoryHandler.findByName(oldCategory);
    auto depo = mDepositHandler.findByName(deposit);

    updateDepositBalanceByCategoryType(cat, depo, -oldAmount);

    mOperationHandler.updateOperation(index, date, deposit, amount, category);
    cat = mCategoryHandler.findByName(category);

    updateDepositBalanceByCategoryType(cat, depo, +amount);
    depo->update();
}

void AppModel::deleteOperation(int index)
{
    if(index >= mOperationHandler.operations().size() || index < 0)
        throw std::out_of_range("Operation with that index does not exitst.");

    const QString &oldCategoryName = mOperationHandler.operations().at(index).category();
    const int oldAmount = mOperationHandler.operations().at(index).amount();
    auto categoryModel = mCategoryHandler.findByName(oldCategoryName);
    auto depositModel = mDepositHandler.findByName(mOperationHandler.operations().at(index).deposit());

    updateDepositBalanceByCategoryType(categoryModel, depositModel, -oldAmount);
    mOperationHandler.deleteOperation(index);
    depositModel->update();
}

void AppModel::deleteCategory(int index)
{
    if(index >= mCategoryHandler.categories().size() || index < 0)
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
    if(index >= mDebtHandler.debts().size() || index < 0)
        throw std::out_of_range("Debt with that index does not exitst.");
    mDebtHandler.updateDebt(index, name, amount);
}

void AppModel::deleteDebt(int index)
{
    if(index >= mDebtHandler.debts().size() || index < 0)
        throw std::out_of_range("Debt with that index does not exitst.");
    mDebtHandler.deleteDebt(index);
}

int AppModel::getSum30DaysOfOperationsByCategory(const CategoryModel &category) const
{
//    OperationModelHandler newHandler;
//    newHandler.get("operations/?category=" + category.name());
    QVector<const OperationModel *> operations;
    for(const auto &cat : mOperationHandler.operations())
        if(cat.category() == category.name())
            operations.push_back(&cat);

    int result = 0;
    for(const auto &operation : operations) {
        const QDateTime opDate = QDateTime().fromString(operation->date(), "yyyy-MM-dd");
        const QDateTime time   = QDateTime().currentDateTime().addDays(-30);
        const QDateTime today  = QDateTime().currentDateTime();
        if(opDate >= time && opDate <= today) {
            result += operation->amount();
        }
    }
    if(category.type() == "negative")
        return -result;
    return result;
}


void AppModel::updateDepositBalanceByCategoryType(QList<CategoryModel>::iterator &category, QList<DepositModel>::iterator &deposit, int amount)
{
    if(category->type() == "negative") {
        deposit->decreaseBalance(amount);
    } else {
        deposit->increaseBalance(amount);
    }
}

int AppModel::getSumOfOperationsByCategoryType(const QVector<const OperationModel *> &operations, const QString &categoryName) const
{
//    CategoryModelHandler newHandler;
//    newHandler.get("categories/?type=" + categoryName);
    QVector<const CategoryModel *> categories;
    for(const auto &category : mCategoryHandler.categories())
        if(category.type() == categoryName)
            categories.push_back(&category);

    int result = 0;
    for(const auto &category : categories)
        for(const auto &operation : operations)
            if(operation->category() == category->name())
                result += operation->amount();
    return result;
}

int AppModel::getSumOfAllEarnOperations() const
{
    return 1;//getSumOfOperationsByCategoryType(mOperationHandler.operations(), "earn");
}

int AppModel::getTodayPnL() const
{
    if(mOperationHandler.operations().empty())
        return 0;

//    OperationModelHandler newHandler;
    QString strToday = QDateTime().currentDateTime().toString("yyyy-MM-dd");
//    newHandler.get("operations/?date=" + strToday);
    QVector<const OperationModel *> operations;
    for(const auto &op : mOperationHandler.operations())
        if(op.date() == strToday)
            operations.push_back(&op);

    const QString &today = QDateTime().currentDateTime().toString("yyyy-MM-dd");
    int negOpSum = getSumOfOperationsByCategoryType(operations, "negative");
    int posOpSum = getSumOfOperationsByCategoryType(operations, "positive") + getSumOfOperationsByCategoryType(operations, "earn");
    return posOpSum - negOpSum;
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

int AppModel::getPnLByDays(int days) const
{
    if(mOperationHandler.operations().empty())
        return 0;

    QVector<const OperationModel *> operations;
    for(const auto &operation : mOperationHandler.operations()) {
        const QDateTime opDate = QDateTime().fromString(operation.date(), "yyyy-MM-dd");
        const QDateTime time   = QDateTime().currentDateTime().addDays(days);
        const QDateTime today  = QDateTime().currentDateTime();
        if(opDate >= time && opDate <= today)
            operations.push_back(&operation);
    }

    const QString &today = QDateTime().currentDateTime().toString("yyyy-MM-dd");
    int negOpSum = getSumOfOperationsByCategoryType(operations, "negative");
    int posOpSum = getSumOfOperationsByCategoryType(operations, "positive") + getSumOfOperationsByCategoryType(operations, "earn");
    return posOpSum - negOpSum;
}
