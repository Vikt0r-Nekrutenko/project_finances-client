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
    const QVector<DebtModel> &debts() const;

    void deleteDeposit(int index);
    void addNewDeposit(const char *name, int balance);
    void changeBalance(int index, int balance);
    int getTotalBalanceOnDeposits() const;

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

    int calculateAllEarnOperations();

private:

    void updateDepositBalanceByCategoryType(QList<CategoryModel>::iterator &category, QList<DepositModel>::iterator &deposit, int amount);

    OperationModelHandler mOperationHandler;
    DebtModelHandler mDebtHandler;
    DepositModelHandler mDepositHandler;
    CategoryModelHandler mCategoryHandler;
};

#endif // APPMODEL_HPP
