#ifndef OPERATIONMODELHANDLER_HPP
#define OPERATIONMODELHANDLER_HPP

#include "modelhandler.hpp"
#include "operationmodel.hpp"

class OperationModelHandler : public DataModelHandler
{
public:
    OperationModelHandler();

    void addNewOperation(const QString &date, const QString &deposit, int amount, const QString &category);
    void updateOperation(int index, const QString &date, const QString &deposit, int amount, const QString &category);
    void deleteOperation(int index);
    void parseJsonArray(const QJsonArray &replyJsonArray) override;

    const QVector<OperationModel> &operations() const;

private:

    QVector<OperationModel> mOperations;
};

#endif // OPERATIONMODELHANDLER_HPP
