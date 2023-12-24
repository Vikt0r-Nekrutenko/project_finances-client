#ifndef OPERATIONMODELHANDLER_HPP
#define OPERATIONMODELHANDLER_HPP

#include "modelhandler.hpp"
#include "operationmodel.hpp"

class CORE_EXPORT OperationModelHandler : public DataModelHandler
{
    friend class OperationHandlerQuery;

public:

    class CORE_EXPORT Query : public std::list<OperationModel *>
    {
    public:

        Query(OperationModelHandler *handler);
        Query &select();
        Query &filterByDeposit(const std::string &deposit);
        Query &filterByCategoryName(const std::string &name);
        Query &filterByCategoryType(CategoryModelHandler &handler, const std::string &type);
        Query &filterByCurrentMonth();
        Query &filterByCurrentYear();
        Query &filterByCurrentDay();
        Query &filterByYear(const int year);
        Query &filterByMonth(const int month);
        Query &filterByDay(const int day);
        OperationModel *at(size_t index);

        int sum() const;

    private:

        OperationModelHandler *mHandler { nullptr };
    } query {this};

    OperationModelHandler();
    ~OperationModelHandler() override;

    void addNewOperation(const std::string &date, const std::string &deposit, int amount, const std::string &category);
    void updateOperation(int index, const std::string &date, const std::string &deposit, int amount, const std::string &category);
    void deleteOperation(int index);
    void selectOperation(int index);
    void changeDate(const std::string &date);

    inline const OperationModel *selectedOperation() const { return mSelectedOperation; }

protected:

    void parseJsonArray(const QJsonArray &replyJsonArray) override;

private:

    std::vector<OperationModel> mOperations;
    OperationModel *mSelectedOperation { nullptr };
};

#endif // OPERATIONMODELHANDLER_HPP
