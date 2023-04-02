#ifndef OPERATIONMODELHANDLER_HPP
#define OPERATIONMODELHANDLER_HPP

#include "modelhandler.hpp"
#include "operationmodel.hpp"

class OperationModelHandler : public DataModelHandler
{
public:
    OperationModelHandler();

    const QVector<OperationModel> &operations() const;

private:

    QVector<OperationModel> mOperations;
};

#endif // OPERATIONMODELHANDLER_HPP
