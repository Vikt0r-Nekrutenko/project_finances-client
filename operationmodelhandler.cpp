#include <QJsonArray>
#include <QJsonObject>

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
    mOperations.removeAt(index);
    mOperations[index].remove();
}

void OperationModelHandler::parseJsonArray(const QJsonArray &replyJsonArray)
{
    mOperations.clear();
    for (const auto &var : replyJsonArray) {
        mOperations.push_back(OperationModel{
            var.toObject()["id"].toInt(),
            var.toObject()["date"].toString(),
            var.toObject()["deposit"].toString(),
            var.toObject()["amount"].toInt(),
            var.toObject()["category"].toString()
        });
    }
}

const QVector<OperationModel> &OperationModelHandler::operations() const
{
    return mOperations;
}
