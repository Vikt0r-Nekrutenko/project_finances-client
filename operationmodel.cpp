#include "operationmodel.hpp"

OperationModel::OperationModel(int id, const QString &date, const QString &deposit, int amount, const QString &category)
    : mDate{date}, mDeposit{deposit}, mCategory{category}, mId{id}, mAmount{amount} {}
