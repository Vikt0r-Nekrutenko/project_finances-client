#include "operationmodelhandler.hpp"


OperationModelHandler::OperationModelHandler()
{
    get("operations/");
}

const QVector<OperationModel> &OperationModelHandler::operations() const
{
    return mOperations;
}
