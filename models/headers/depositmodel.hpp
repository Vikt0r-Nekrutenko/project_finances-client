#ifndef DEPOSITMODEL_HPP
#define DEPOSITMODEL_HPP

#include "crudmodel.hpp"

class DepositModel : public CRUDModel
{
    friend class DepositModelHandler;
public:
    DepositModel(const QString &name, int balance);

    void create() override;
    void read() override;
    void update() override;
    void remove() override;
    void parseJsonObject(const QJsonObject &object) override;

    const QString &name() const;
    int balance() const;

    void increaseBalance(int amount);
    void decreaseBalance(int amount);

private:

    QString mName;
    int mBalance;
};

#endif // DEPOSITMODEL_HPP
