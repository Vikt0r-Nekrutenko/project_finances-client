#ifndef APPMODEL_HPP
#define APPMODEL_HPP

#include "categorymodelhandler.hpp"
#include "debtmodelhandler.hpp"
#include "depositmodelhandler.hpp"
#include "operationmodelhandler.hpp"
#include <smv/imodel.hpp>

class AppModel : public stf::smv::BaseModel
{
public:
    const QVector<DepositModel> &deposits() const;
    const QVector<OperationModel> &operations() const;
    const QVector<CategoryModel> &categories() const;
    const QVector<CategoryModel> &favCategories() const;
    const QVector<DebtModel> &debts() const;

    void updateAllHandlers();
    void selectFavCategories(int index1, int index2, int index3);

    void deleteDeposit(int index);
    void addNewDeposit(const char *name, int balance);
    void changeBalance(int index, int balance);

    void addNewLendOperation(const char *date, const char *deposit, int amount, const char *name);
    void addNewRepayOperation(const char *date, const char *deposit, int amount, const char *name);

    void addNewOperation(const char *date, const char *deposit, int amount, const char *category);
    void changeOperation(int index, const char *date, const char *deposit, int amount, const char *category);
    void deleteOperation(int index);

    void deleteCategory(int index);
    void addNewCategory(const char *name, const char *type);

    void addNewDebt(const char *name, int amount);
    void changeDebt(int index, const char *name, int amount);
    void deleteDebt(int index);

    int getSum30DeysOfOperationsByCategory(const CategoryModel &category) const;
    int getSumOfAllEarnOperations() const;
    int getSumOfAllDeposits() const;
    int getTodayPnL() const;
    int getWeekPnL() const;
    int getMonthPnL() const;
    int getYearPnl() const;

private:

    int getPnLByDays(int days) const;
    int getSumOfOperationsByCategoryType(const QVector<OperationModel> &operations, const QString &categoryName) const;
    void updateDepositBalanceByCategoryType(QList<CategoryModel>::iterator &category, QList<DepositModel>::iterator &deposit, int amount);

    OperationModelHandler mOperationHandler;
    DebtModelHandler mDebtHandler;
    DepositModelHandler mDepositHandler;
    CategoryModelHandler mCategoryHandler;

    QVector<CategoryModel> mFavCategories;
};

#endif // APPMODEL_HPP
