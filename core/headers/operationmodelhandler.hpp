#ifndef OPERATIONMODELHANDLER_HPP
#define OPERATIONMODELHANDLER_HPP

#include "modelhandler.hpp"
#include "operationmodel.hpp"

class CORE_EXPORT OperationModelHandler : public DataModelHandler
{
    friend class OperationHandlerQuery;

public:

    OperationModelHandler();
    ~OperationModelHandler() override;

    void addNewOperation(const std::string &date, const std::string &deposit, int amount, const std::string &category);
    void updateOperation(int index, const std::string &date, const std::string &deposit, int amount, const std::string &category);
    void deleteOperation(int index);

    inline const std::vector<OperationModel> &operations() const { return mOperations; }
    inline std::vector<OperationModel> &operations() { return mOperations; }

    std::vector<OperationModel>::iterator at(int id);

protected:

    void parseJsonArray(const QJsonArray &replyJsonArray) override;

private:

    std::vector<OperationModel> mOperations;
};

#endif // OPERATIONMODELHANDLER_HPP
