#ifndef APPMODEL_HPP
#define APPMODEL_HPP

#include "categorymodelhandler.hpp"
#include "depositmodelhandler.hpp"
#include "operationmodelhandler.hpp"
#include <smv/imodel.hpp>

class AppModel : public stf::smv::BaseModel
{
public:
    const QVector<DepositModel> &deposits() const;
    const QVector<OperationModel> &operations() const;

    void deleteDeposit(int index);
    void addNewDeposit(const char *name, int balance);
    void changeBalance(int index, int balance);
    int getTotalBalanceOnDeposits() const;

    void addNewOperation(const char *date, const char *deposit, int amount, const char *category);
    void changeOperation(int index, const char *date, const char *deposit, int amount, const char *category);
    void deleteOperation(int index);

    void deleteCategory(int index);
    void addNewCategory(const char *name, const char *type);

private:

    OperationModelHandler mOperationHandler;
    DepositModelHandler mDepositHandler;
    CategoryModelHandler mCategoryHandler;
};

#endif // APPMODEL_HPP
