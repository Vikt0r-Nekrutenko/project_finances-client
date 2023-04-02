#ifndef DEPOSITMODELHANDLER_HPP
#define DEPOSITMODELHANDLER_HPP

#include "modelhandler.hpp"

class DepositModelHandler : public DataModelHandler
{
public:
    DepositModelHandler();
    void addNewDeposit(const QString &name, int balance);
};

#endif // DEPOSITMODELHANDLER_HPP
