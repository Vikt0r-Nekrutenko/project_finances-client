#ifndef APPMODEL_HPP
#define APPMODEL_HPP

#include "depositmodelhandler.hpp"
#include <smv/imodel.hpp>

class AppModel : public stf::smv::BaseModel
{
public:
    const QVector<DepositModel> &deposits() const;

    void deleteDeposit(int index);

    void addNewDeposit(const char *name, int balance);

    void changeBalance(int index, int balance);

    int getTotalBalanceOnDeposits() const;
private:

    DepositModelHandler mDepositHandler;
};

#endif // APPMODEL_HPP
