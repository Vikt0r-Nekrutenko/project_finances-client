#ifndef DEPOSITMODEL_HPP
#define DEPOSITMODEL_HPP

#include "crudmodel.hpp"

class DepositModel : public CRUDModel
{
public:
    DepositModel(const QString &name, int balance);

    void create() override;
    void read() override;
    void update() override;
    void remove() override;
    void parseJsonObject(const QJsonObject &object) override;

private:

    const QString mName;
    int mBalance;
};

#endif // DEPOSITMODEL_HPP
