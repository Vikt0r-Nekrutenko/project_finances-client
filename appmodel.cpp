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

int AppModel::getTotalBalanceOnDeposits() const
{
    int result = 0;

    for(const auto &deposit : deposits()) {
        result += deposit.balance();
    }
    return result;
}

void AppModel::addNewOperation(const char *date, const char *deposit, int amount, const char *category)
{
    mOperationHandler.addNewOperation(date, deposit, amount, category);

    auto cat = std::find_if(mCategoryHandler.categories().begin(), mCategoryHandler.categories().end(), [&](const CategoryModel &model){
        return model.name() == category;
    });

    auto depo = std::find_if(mDepositHandler.deposits().begin(), mDepositHandler.deposits().end(), [&](const DepositModel &model){
        return model.name() == deposit;
    });

    updateDepositBalanceByCategoryType(cat, depo, +amount);
    depo->update();
}

void AppModel::changeOperation(int index, const char *date, const char *deposit, int amount, const char *category)
{
    if(index >= mOperationHandler.operations().size() || index < 0)
        throw std::out_of_range("Operation with that index does not exitst.");

    const QString &oldCategory = mOperationHandler.operations().at(index).category();

    auto cat = std::find_if(mCategoryHandler.categories().begin(), mCategoryHandler.categories().end(), [&](const CategoryModel &model){
        return model.name() == oldCategory;
    });

    auto depo = std::find_if(mDepositHandler.deposits().begin(), mDepositHandler.deposits().end(), [&](const DepositModel &model){
        return model.name() == deposit;
    });

    const int oldAmount = mOperationHandler.operations().at(index).amount();

    updateDepositBalanceByCategoryType(cat, depo, -oldAmount);

    mOperationHandler.updateOperation(index, date, deposit, amount, category);

    cat = std::find_if(mCategoryHandler.categories().begin(), mCategoryHandler.categories().end(), [&](const CategoryModel &model){
        return model.name() == category;
    });

    updateDepositBalanceByCategoryType(cat, depo, +amount);

    depo->update();
}

void AppModel::deleteOperation(int index)
{
    if(index >= mOperationHandler.operations().size() || index < 0)
        throw std::out_of_range("Operation with that index does not exitst.");
    mOperationHandler.deleteOperation(index);
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
