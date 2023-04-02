#ifndef DEPOSITMODELHANDLER_HPP
#define DEPOSITMODELHANDLER_HPP

#include "depositmodel.hpp"
#include "modelhandler.hpp"

class DepositModelHandler : public DataModelHandler
{
public:
    DepositModelHandler();
    void addNewDeposit(const QString &name, int balance);
    void updateBalance(int depositIndex, int newBalance);
    void deleteDeposit(int depositIndex);
    void parseJsonArray(const QJsonArray &replyJsonArray) override;

    const QVector<DepositModel> &deposits() const;

private:

    QVector<DepositModel> mDeposits;
};

#endif // DEPOSITMODELHANDLER_HPP
