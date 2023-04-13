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
