#ifndef OPERATIONMODEL_HPP
#define OPERATIONMODEL_HPP

#include "crudmodel.hpp"

class OperationModel : public CRUDModel
{
public:
    OperationModel(int id, const QString &date, const QString &deposit, int amount, const QString &category);

    void create() override;
    void read() override;
    void update() override;
    void remove() override;
    void parseJsonObject(const QJsonObject &) override;

private:

    QString mDate;
    QString mDeposit;
    QString mCategory;
    int mId, mAmount;
};

#endif // OPERATIONMODEL_HPP
