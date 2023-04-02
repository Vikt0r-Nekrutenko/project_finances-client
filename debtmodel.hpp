#ifndef DEBTMODEL_HPP
#define DEBTMODEL_HPP

#include "crudmodel.hpp"

class DebtModel : public CRUDModel
{
    friend class DebtModelHandler;
public:
    DebtModel(const QString &name, const QString &deposit, int amount);

    void create() override;
    void read() override;
    void update() override;
    void remove() override;
    void parseJsonObject(const QJsonObject &) override;

    const QString &deposit() const;
    const QString &name() const;
    int amount() const;

private:
    QString mDeposit;
    QString mName;
    int mAmount;
};

#endif // DEBTMODEL_HPP
