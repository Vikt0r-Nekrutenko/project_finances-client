#ifndef OPERATIONMODELHANDLER_HPP
#define OPERATIONMODELHANDLER_HPP

#include "modelhandler.hpp"
#include "operationmodel.hpp"

class OperationModelHandler : public DataModelHandler
{
    friend class OperationHandlerQuery;

public:

    OperationModelHandler();

    void addNewOperation(const std::string &date, const std::string &deposit, int amount, const std::string &category);
    void updateOperation(int index, const std::string &date, const std::string &deposit, int amount, const std::string &category);
    void deleteOperation(int index);
    void parseJsonArray(const QJsonArray &replyJsonArray) override;

    const std::vector<OperationModel> &operations() const;
    std::vector<OperationModel> &operations();

private:

    std::vector<OperationModel> mOperations;
};

#endif // OPERATIONMODELHANDLER_HPP
