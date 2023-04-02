#ifndef APPMODEL_HPP
#define APPMODEL_HPP

#include "depositmodelhandler.hpp"
#include <smv/imodel.hpp>

class AppModel : public stf::smv::BaseModel
{
public:
    const QVector<DepositModel> &deposits() const;

    int getTotalBalanceOnDeposits() const;
private:

    DepositModelHandler mDepositHandler;
};

#endif // APPMODEL_HPP
