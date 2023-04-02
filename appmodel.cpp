#include "appmodel.hpp"




const QVector<DepositModel> &AppModel::deposits() const
{
    return mDepositHandler.deposits();
}
