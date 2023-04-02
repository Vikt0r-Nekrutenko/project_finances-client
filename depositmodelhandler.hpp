#ifndef DEPOSITMODELHANDLER_HPP
#define DEPOSITMODELHANDLER_HPP

#include "depositmodel.hpp"
#include "modelhandler.hpp"

class DepositModelHandler : public DataModelHandler
{
public:
    DepositModelHandler();
    void addNewDeposit(const QString &name, int balance);

private:

    QVector<DepositModel> mDeposits;
};

#endif // DEPOSITMODELHANDLER_HPP
