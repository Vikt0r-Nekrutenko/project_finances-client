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

std::string OperationHandler::getStrFromInput()
{
    int pos = mInput.find(" ");
    if(pos != int(mInput.npos)) {
        std::string result = mInput.substr(0, pos);
        mInput.erase(0, pos + 1);
        return result;
    } else {
        return mInput.erase(0, pos + 1);
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
    std::string date = getStrFromInput();
    std::string deposit = getStrFromInput();
    int amount = getIntFromInput();
    std::string category = getStrFromInput();

    model->addNewOperation(date.c_str(), deposit.c_str(), amount, category.c_str());
    updateOperationsList(model, date);
}

