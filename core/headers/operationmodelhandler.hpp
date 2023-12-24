#ifndef OPERATIONMODELHANDLER_HPP
#define OPERATIONMODELHANDLER_HPP

#include "modelhandler.hpp"
#include "operationmodel.hpp"

class CORE_EXPORT OperationModelHandler : public DataModelHandler
{
    friend class OperationHandlerQuery;

public:

    class CORE_EXPORT Query : public std::vector<OperationModel *>
    {
    public:

        Query(OperationModelHandler *model);
        const Query &select();
        const Query &filterByDeposit(const std::string &deposit);
        const Query &filterByCategoryName(const std::string &name);
        const Query &filterByCategoryType(CategoryModelHandler &handler, const std::string &type);
        const Query &filterByCurrentMonth();
        const Query &filterByCurrentYear();
        const Query &filterByCurrentDay();
        const Query &filterByYear(const int year);
        const Query &filterByMonth(const int month);
        const Query &filterByDay(const int day);

        int sum() const;

    private:

        OperationModelHandler *mHandler { nullptr };
    };

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
