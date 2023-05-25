#ifndef QUERYRESULT_HPP
#define QUERYRESULT_HPP

#include <list>
#include <string>
#include "core_global.h"

class CategoryModel;
class OperationModel;
class OperationModelHandler;
class CategoryModelHandler;

class CategoryHandlerQuery : public std::list<CategoryModel *>
{
public:

    CategoryHandlerQuery(CategoryModelHandler *handler);
    CategoryHandlerQuery &select();
    CategoryHandlerQuery &filterByType(const std::string &type);

protected:

    CategoryModelHandler *mHandler;
};

class CORE_EXPORT OperationHandlerQuery : public std::list<OperationModel *>
{
public:
    OperationHandlerQuery(OperationModelHandler *model);
    OperationHandlerQuery &select();
    OperationHandlerQuery &filterByDeposit(const std::string &deposit);
    OperationHandlerQuery &filterByCategoryType(CategoryModelHandler &handler, const std::string &type);
    OperationHandlerQuery &filterByCurrentMonth();
    OperationHandlerQuery &filterByCurrentYear();
    OperationHandlerQuery &filterByCurrentDay();

    OperationHandlerQuery &filterByYear(const int year);
    OperationHandlerQuery &filterByMonth(const int month);
    OperationHandlerQuery &filterByDay(const int day);

    OperationHandlerQuery &join(const CategoryHandlerQuery &query);

    int sum() const;

protected:

    OperationModelHandler *mModel;
};

#endif // QUERYRESULT_HPP
