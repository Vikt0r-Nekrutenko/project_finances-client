#ifndef DEPOSITMODEL_HPP
#define DEPOSITMODEL_HPP

#include "crudmodel.hpp"

class DepositModel : public CRUDModel
{
public:
    DepositModel(const QString &name, const QString &balance);

private:
    const QString mName;
    int mBalance;
};

#endif // DEPOSITMODEL_HPP
