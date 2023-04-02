#include "operationmodelhandler.hpp"


OperationModelHandler::OperationModelHandler()
{
    get("operations/");
}

void OperationModelHandler::addNewOperation(const QString &date, const QString &deposit, int amount, const QString &category)
{

}

void OperationModelHandler::updateOperation(int index, const QString &date, const QString &deposit, int amount, const QString &category)
{

}

void OperationModelHandler::deleteOperation(int index)
{

}

void OperationModelHandler::parseJsonArray(const QJsonArray &replyJsonArray)
{

}

const QVector<OperationModel> &OperationModelHandler::operations() const
{
    return mOperations;
}
