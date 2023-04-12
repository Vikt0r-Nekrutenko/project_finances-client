#include "operationhandler.hpp"
#include "appmodel.hpp"

void AddNewOperationHandler::handle(AppModel *model, std::string &input)
{
    std::string date = getStrFromInput();
    std::string deposit = getStrFromInput();
    int amount = getIntFromInput();
    std::string category = getStrFromInput();

    static_cast<AppModel*>(m_model)->addNewOperation(date.c_str(), deposit.c_str(), amount, category.c_str());
    updateOperationsList(date);
}
