#include "operationmodelhandler.hpp"
#include "categorymodelhandler.hpp"
#include "queryresult.hpp"

CategoryHandlerQuery::CategoryHandlerQuery(CategoryModelHandler *handler)
    : mHandler{handler} {}

CategoryHandlerQuery &CategoryHandlerQuery::select()
{
    clear();
    for(size_t i = 0; i < mHandler->mCategories.size(); ++i)
        push_back(&mHandler->mCategories.at(i));
    return *this;
}

CategoryHandlerQuery &CategoryHandlerQuery::filterByType(const std::string &type)
{
    for(CategoryHandlerQuery::iterator it = begin(); it != end(); )
        it = ((*it)->type() != type) ? erase(it) : ++it;
    return *this;
}

OperationHandlerQuery::OperationHandlerQuery(OperationModelHandler *model)
    : mModel{model} {}

OperationHandlerQuery &OperationHandlerQuery::select()
{
    clear();
    std::vector<OperationModel> &operations = mModel->mOperations;
    for(size_t i = 0; i < operations.size(); ++i)
        push_back(&operations.at(i));
    return *this;
}

OperationHandlerQuery &OperationHandlerQuery::filterByDeposit(const std::string &deposit)
{
    for(OperationHandlerQuery::iterator it = begin(); it != end(); )
        it = ((*it)->deposit() != deposit) ? erase(it) : ++it;
    return *this;
}

OperationHandlerQuery &OperationHandlerQuery::filterByCategoryType(CategoryModelHandler &handler, const std::string &type)
{
    for(OperationHandlerQuery::iterator it = begin(); it != end(); )
        it = ((*it)->rawCategory(handler).type() != type) ? erase(it) : ++it;
    return *this;
}

OperationHandlerQuery &OperationHandlerQuery::filterByCurrentYear()
{
    const QDate &currentDate = QDate().currentDate();
    return filterByYear(currentDate.year());
}

OperationHandlerQuery &OperationHandlerQuery::filterByCurrentMonth()
{
    const QDate &currentDate = QDate().currentDate();
    return filterByMonth(currentDate.month());
}

OperationHandlerQuery &OperationHandlerQuery::filterByCurrentDay()
{
    const QDate &currentDate = QDate().currentDate();
    return filterByDay(currentDate.day());
}

OperationHandlerQuery &OperationHandlerQuery::filterByYear(const int year)
{
    for(OperationHandlerQuery::iterator it = begin(); it != end(); )
        it = (QDateTime().fromString((*it)->date().c_str(), "yyyy-MM-dd").date().year() != year) ? erase(it) : ++it;
    return *this;
}

OperationHandlerQuery &OperationHandlerQuery::filterByMonth(const int month)
{
    for(OperationHandlerQuery::iterator it = begin(); it != end(); )
        it = (QDateTime().fromString((*it)->date().c_str(), "yyyy-MM-dd").date().month() != month) ? erase(it) : ++it;
    return *this;
}

OperationHandlerQuery &OperationHandlerQuery::filterByDay(const int day)
{
    for(OperationHandlerQuery::iterator it = begin(); it != end(); )
        it = (QDateTime().fromString((*it)->date().c_str(), "yyyy-MM-dd").date().day() != day) ? erase(it) : ++it;
    return *this;
}

OperationHandlerQuery &OperationHandlerQuery::join(const CategoryHandlerQuery &query)
{
    for(CategoryHandlerQuery::const_iterator cit = query.begin(); cit != query.end(); ++cit)
        for(OperationHandlerQuery::iterator oit = begin(); oit != end(); )
            oit = ((*oit)->category() != (*cit)->name()) ? erase(oit) : ++oit;
    return *this;
}

int OperationHandlerQuery::sum() const
{
    int result = 0;
    for(OperationHandlerQuery::const_iterator it = begin(); it != end(); ++it)
        result += (*it)->amount();
    return result;
}
