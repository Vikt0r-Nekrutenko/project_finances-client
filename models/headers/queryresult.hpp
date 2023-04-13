#ifndef QUERYRESULT_HPP
#define QUERYRESULT_HPP

#include <list>
#include <string>

class OperationModel;
class AppModel;

class QueryResult : public std::list<OperationModel *>
{
public:
    QueryResult(AppModel *model);
    QueryResult &select();
    QueryResult &filterByDeposit(const std::string &deposit);
    QueryResult &filterByCurrentMonth();
    QueryResult &filterByCurrentYear();
    QueryResult &filterByCurrentDay();

    QueryResult &filterByYear(const int year);
    QueryResult &filterByMonth(const int month);
    QueryResult &filterByDay(const int day);

protected:

    AppModel *mModel;
};

#endif // QUERYRESULT_HPP
