#ifndef APPMODEL_HPP
#define APPMODEL_HPP

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
    void deleteOperation(int index);
private:

    OperationModelHandler mOperationHandler;
    DepositModelHandler mDepositHandler;
};

#endif // APPMODEL_HPP
