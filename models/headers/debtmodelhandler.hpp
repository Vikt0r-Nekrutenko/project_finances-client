#ifndef DEBTMODELHANDLER_HPP
#define DEBTMODELHANDLER_HPP

#include "modelhandler.hpp"
#include "debtmodel.hpp"

class DebtModelHandler : public DataModelHandler
{
public:
    DebtModelHandler();

    void addNewDebt(const QString &name, int amount);
    void updateDebt(int index, const QString &name, int amount);
    void deleteDebt(int index);
    void parseJsonArray(const QJsonArray &replyJsonArray) override;

    const QVector<DebtModel> &debts() const;

    QList<DebtModel>::iterator findByName(const QString &name);

private:

    QVector<DebtModel> mDebts;
};

#endif // DEBTMODELHANDLER_HPP
