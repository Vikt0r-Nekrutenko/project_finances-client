#include "operationhandler.hpp"
#include "appmodel.hpp"

void OperationHandler::updateOperationsList(AppModel *model, const std::string &date)
{
    const int year = QDateTime().fromString(date.c_str(), "yyyy-MM-dd").date().year();
    const int month = QDateTime().fromString(date.c_str(), "yyyy-MM-dd").date().month();
    static_cast<AppModel*>(model)->getOperationsByMonth(year, month);
}

void AddNewOperationHandler::handle(AppModel *model, std::string &input)
{
    std::string date = getStrFromInput();
    std::string deposit = getStrFromInput();
    int amount = getIntFromInput();
    std::string category = getStrFromInput();

    static_cast<AppModel*>(m_model)->addNewOperation(date.c_str(), deposit.c_str(), amount, category.c_str());
    updateOperationsList(date);
}

