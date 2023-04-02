#ifndef OPERATIONMODEL_HPP
#define OPERATIONMODEL_HPP

#include "crudmodel.hpp"

class OperationModel : public CRUDModel
{
public:
    OperationModel(int id, const QString &date, const QString &deposit, int amount, const QString &category);

private:

    QString mDate;
    QString mDeposit;
    QString mCategory;
    int mId, mAmount;
};

#endif // OPERATIONMODEL_HPP
