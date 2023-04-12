#include "operationhandler.hpp"
#include "appmodel.hpp"

int OperationHandler::getIntFromInput(std::string &input)
{
    int pos = input.find(" ");
    if(pos != int(input.npos)) {
        int result = std::stoi(input.substr(0, pos));
        input.erase(0, pos + 1);
        return result;
    } else {
        return std::stoi(input.erase(0, pos + 1));
    }
}

std::string OperationHandler::getStrFromInput(std::string &input)
{
    int pos = input.find(" ");
    if(pos != int(input.npos)) {
        std::string result = input.substr(0, pos);
        input.erase(0, pos + 1);
        return result;
    } else {
        return input.erase(0, pos + 1);
    }
}

void OperationHandler::updateOperationsList(AppModel *model, const std::string &date)
{
    const int year = QDateTime().fromString(date.c_str(), "yyyy-MM-dd").date().year();
    const int month = QDateTime().fromString(date.c_str(), "yyyy-MM-dd").date().month();
    static_cast<AppModel*>(model)->getOperationsByMonth(year, month);
}

void AddNewOperationHandler::handle(AppModel *model, std::string &input)
{
    std::string date = getStrFromInput(input);
    std::string deposit = getStrFromInput(input);
    int amount = getIntFromInput(input);
    std::string category = getStrFromInput(input);

    model->addNewOperation(date.c_str(), deposit.c_str(), amount, category.c_str());
    updateOperationsList(model, date);
}

