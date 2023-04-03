#include "appmodel.hpp"

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

const QVector<DebtModel> &AppModel::debts() const
{
    return mDebtHandler.debts();
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


void AppModel::updateDepositBalanceByCategoryType(QList<CategoryModel>::iterator &category, QList<DepositModel>::iterator &deposit, int amount)
{
    if(category->type() == "negative") {
        deposit->decreaseBalance(amount);
    } else {
        deposit->increaseBalance(amount);
    }
}

int AppModel::getSumOfOperationsByCategoryType(const QVector<OperationModel> &operations, const QString &categoryName) const
{
    QVector<QString> earnOperationNames;
    for(const auto &category : mCategoryHandler.categories())
        if(category.type() == categoryName)
            earnOperationNames.push_back(category.name());

    int result = 0;
    for(const auto &name : earnOperationNames)
        for(const auto &operation : operations)
            if(operation.category() == name)
                result += operation.amount();
    return result;
}

int AppModel::getSumOfAllEarnOperations() const
{
    return getSumOfOperationsByCategoryType(mOperationHandler.operations(), "earn");
}

int AppModel::getTodayPnL() const
{
    if(mOperationHandler.operations().empty())
        return 0;

    const QString &today = QDateTime().currentDateTime().toString("yyyy-MM-dd");

    QVector<OperationModel> todayOperations;
    for(const auto &operation : mOperationHandler.operations())
        if(operation.date() == today)
            todayOperations.push_back(operation);

    int negOpSum = getSumOfOperationsByCategoryType(todayOperations, "negative");
    int posOpSum = getSumOfOperationsByCategoryType(todayOperations, "positive") + getSumOfOperationsByCategoryType(todayOperations, "earn");

    return posOpSum - negOpSum;
}
