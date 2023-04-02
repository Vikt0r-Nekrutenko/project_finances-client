#include <QJsonArray>
#include <QJsonObject>

#include "operationmodelhandler.hpp"

OperationModelHandler::OperationModelHandler()
{
    get("operations/");
}

void OperationModelHandler::addNewOperation(const QString &date, const QString &deposit, int amount, const QString &category)
{
    mOperations.push_back(OperationModel(
                              mOperations.empty() ? 0 : mOperations.back().mId + 1,
                              date,
                              deposit,
                              amount,
                              category));
    mOperations.back().create();
}

void OperationModelHandler::updateOperation(int index, const QString &date, const QString &deposit, int amount, const QString &category)
{
    mOperations[index].mDate = date;
    mOperations[index].mDeposit = deposit;
    mOperations[index].mAmount = amount;
    mOperations[index].mCategory = category;
    mOperations[index].update();
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
