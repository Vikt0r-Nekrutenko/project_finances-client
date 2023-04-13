#include "appmodel.hpp"

AppModel::QueryResult::QueryResult(AppModel *model)
    : mModel{model} {}

AppModel::QueryResult &AppModel::QueryResult::select()
{
    auto operations = mModel->mOperationHandler.operations();
    for(size_t i = 0; i < operations.size(); ++i)
        push_back(&operations.at(i));
    return *this;
}

AppModel::QueryResult &AppModel::QueryResult::filterByDeposit(const std::string &deposit)
{
    for(QueryResult::iterator it = begin(); it != end(); )
        it = ((*it)->deposit() == deposit) ? erase(it) : ++it;
    return *this;
}

AppModel::QueryResult &AppModel::QueryResult::filterByYear(const int year)
{
    for(QueryResult::iterator it = begin(); it != end(); )
        it = (QDateTime().fromString((*it)->date().c_str(), "yyyy-MM-dd").date().year() == year) ? erase(it) : ++it;
    return *this;
}

AppModel::QueryResult &AppModel::QueryResult::filterByMonth(const int month)
{
    for(QueryResult::iterator it = begin(); it != end(); )
        it = (QDateTime().fromString((*it)->date().c_str(), "yyyy-MM-dd").date().month() == month) ? erase(it) : ++it;
    return *this;
}

AppModel::QueryResult &AppModel::QueryResult::filterByDay(const int day)
{
    for(QueryResult::iterator it = begin(); it != end(); )
        it = (QDateTime().fromString((*it)->date().c_str(), "yyyy-MM-dd").date().day() == day) ? erase(it) : ++it;
    return *this;
}
