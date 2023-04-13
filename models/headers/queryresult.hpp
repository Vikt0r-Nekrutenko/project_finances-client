#ifndef QUERYRESULT_HPP
#define QUERYRESULT_HPP

#include <list>
#include <string>

class OperationModel;
class OperationModelHandler;

class OperationHandlerQuery : public std::list<OperationModel *>
{
public:
    OperationHandlerQuery(OperationModelHandler *model);
    OperationHandlerQuery &select();
    OperationHandlerQuery &filterByDeposit(const std::string &deposit);
    OperationHandlerQuery &filterByCurrentMonth();
    OperationHandlerQuery &filterByCurrentYear();
    OperationHandlerQuery &filterByCurrentDay();

    OperationHandlerQuery &filterByYear(const int year);
    OperationHandlerQuery &filterByMonth(const int month);
    OperationHandlerQuery &filterByDay(const int day);

protected:

    OperationModelHandler *mModel;
};

#endif // QUERYRESULT_HPP
