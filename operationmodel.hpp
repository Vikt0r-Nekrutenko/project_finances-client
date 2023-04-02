#ifndef OPERATIONMODEL_HPP
#define OPERATIONMODEL_HPP

#include "crudmodel.hpp"

class OperationModel : public CRUDModel
{
public:
    OperationModel();

private:

    QString mDate;
    QString mDeposit;
    QString mCategory;
    int mId, mAmount;
};

#endif // OPERATIONMODEL_HPP
