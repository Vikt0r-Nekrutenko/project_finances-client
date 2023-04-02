#ifndef DEBTMODEL_HPP
#define DEBTMODEL_HPP

#include "crudmodel.hpp"

class DebtModel : public CRUDModel
{
    friend class DebtModelHandler;
public:
    DebtModel(int id, const QString &name, int amount);

    void create() override;
    void read() override;
    void update() override;
    void remove() override;
    void parseJsonObject(const QJsonObject &) override;

    const QString &name() const;
    int amount() const;
    int id() const;

private:

    QString mName;
    int mId, mAmount;
};

#endif // DEBTMODEL_HPP
