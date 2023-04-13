#include "appmodel.hpp"

AppModel::QueryResult::QueryResult(AppModel *model)
    : mModel{model} {}

AppModel::QueryResult &AppModel::QueryResult::filterByDeposit(const std::string &deposit)
{
    auto operations = mModel->mOperationHandler.operations();
    for(size_t i = 0; i < operations.size(); ++i)
        if(operations.at(i).deposit() == deposit)
            push_back(&operations.at(i));
    return *this;
}

AppModel::QueryResult &AppModel::QueryResult::filterByYear(const int year)
{
    auto operations = mModel->mOperationHandler.operations();
    for(size_t i = 0; i < operations.size(); ++i)
        if(QDateTime().fromString(operations.at(i).date().c_str(), "yyyy-MM-dd").date().year() == year)
            push_back(&operations.at(i));
    return *this;
}

AppModel::QueryResult &AppModel::QueryResult::filterByMonth(const int month)
{
    auto operations = mModel->mOperationHandler.operations();
    for(size_t i = 0; i < operations.size(); ++i)
        if(QDateTime().fromString(operations.at(i).date().c_str(), "yyyy-MM-dd").date().month() == month)
            push_back(&operations.at(i));
    return *this;
}

AppModel::QueryResult &AppModel::QueryResult::filterByDay(const int day)
{
    auto operations = mModel->mOperationHandler.operations();
    for(size_t i = 0; i < operations.size(); ++i)
        if(QDateTime().fromString(operations.at(i).date().c_str(), "yyyy-MM-dd").date().day() == day)
            push_back(&operations.at(i));
    return *this;
}
