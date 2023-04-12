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
    model->getOperationsByMonth(year, month);
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

const char *AddNewOperationHandler::operationFieldsInfo() const
{
    return "Type 'date deposit amount category' or 'q' to step back:";
}

const char *AddNewOperationHandler::caption() const
{
    return "Add new operation.";
}

void DeleteOperationHandler::handle(AppModel *model, std::string &input)
{
    int id = getIntFromInput(input) - 1;
    const std::string &date = model->operations().at(id).date();
    model->deleteOperation(id);
    updateOperationsList(model, date);
}

const char *DeleteOperationHandler::operationFieldsInfo() const
{
    return "Type 'id' or 'q' to step back:";
}

const char *DeleteOperationHandler::caption() const
{
    return "Delete operation.";
}

void ChangeOperationHandler::handle(AppModel *model, std::string &input)
{
    int id = getIntFromInput(input) - 1;
    std::string date = getStrFromInput(input);
    std::string deposit = getStrFromInput(input);
    int amount = getIntFromInput(input);
    std::string category = getStrFromInput(input);

    model->changeOperation(id, date.c_str(), deposit.c_str(), amount, category.c_str());
    updateOperationsList(model, date);
}

const char *ChangeOperationHandler::operationFieldsInfo() const
{
    return "Type 'id date deposit amount category' or 'q' to step back:";
}

const char *ChangeOperationHandler::caption() const
{
    return "Change operation.";
}

void AddLendOperationHandler::handle(AppModel *model, std::string &input)
{
    std::string date = getStrFromInput(input);
    std::string deposit = getStrFromInput(input);
    int amount = getIntFromInput(input);
    std::string name = getStrFromInput(input);

    model->addNewLendOperation(date.c_str(), deposit.c_str(), amount, name.c_str());
    updateOperationsList(model, date);
}

const char *AddLendOperationHandler::operationFieldsInfo() const
{
    return "Type 'date deposit amount name' or 'q' to step back:";
}

const char *AddLendOperationHandler::caption() const
{
    return "Add new lend operation.";
}

void AddRepayOperationHandler::handle(AppModel *model, std::string &input)
{
    std::string date = getStrFromInput(input);
    std::string deposit = getStrFromInput(input);
    int amount = getIntFromInput(input);
    std::string name = getStrFromInput(input);

    model->addNewRepayOperation(date.c_str(), deposit.c_str(), amount, name.c_str());
    updateOperationsList(model, date);
}

const char *AddRepayOperationHandler::operationFieldsInfo() const
{
    return "Type 'date deposit amount name' or 'q' to step back:";
}

const char *AddRepayOperationHandler::caption() const
{
    return "Add new repay operation.";
}

void AddNewTodayBankPrivatOperationHandler::handle(AppModel *model, std::string &input)
{
    int amount = getIntFromInput(input);
    std::string category = getStrFromInput(input);
    std::string date = QDateTime().currentDateTime().toString("yyyy-MM-dd").toStdString();

    model->addNewOperation(date.c_str(), "PrivatBank", amount, category.c_str());
    updateOperationsList(model, date);
}

const char *AddNewTodayBankPrivatOperationHandler::operationFieldsInfo() const
{
    return "Type 'amount category' or 'q' to step back:";
}

const char *AddNewTodayBankPrivatOperationHandler::caption() const
{
    return "Today PrivatBank.";
}

void SelectListOperationHandler::handle(AppModel *model, std::string &input)
{
    int year = getIntFromInput(input);
    int month = getIntFromInput(input);

    model->getOperationsByMonth(year, month);
}

const char *SelectListOperationHandler::operationFieldsInfo() const
{
    return "Type 'year month' or 'q' to step back:";
}

const char *SelectListOperationHandler::caption() const
{
    return "Select list by month.";
}

void AddNewTodayBankPrivatLendOperationHandler::handle(AppModel *model, std::string &input)
{
    int amount = getIntFromInput(input);
    std::string name = getStrFromInput(input);
    std::string date = QDateTime().currentDateTime().toString("yyyy-MM-dd").toStdString();

    model->addNewLendOperation(date.c_str(), "PrivatBank", amount, name.c_str());
    updateOperationsList(model, date);
}

const char *AddNewTodayBankPrivatLendOperationHandler::operationFieldsInfo() const
{
    return "Type 'amount name' or 'q' to step back:";
}

const char *AddNewTodayBankPrivatLendOperationHandler::caption() const
{
    return "Today PrivatBank Lend.";
}

void AddNewTodayBankPrivatRepayOperationHandler::handle(AppModel *model, std::string &input)
{
    int amount = getIntFromInput(input);
    std::string name = getStrFromInput(input);
    std::string date = QDateTime().currentDateTime().toString("yyyy-MM-dd").toStdString();

    model->addNewRepayOperation(date.c_str(), "PrivatBank", amount, name.c_str());
    updateOperationsList(model, date);
}

const char *AddNewTodayBankPrivatRepayOperationHandler::operationFieldsInfo() const
{
    return "Type 'amount name' or 'q' to step back:";
}

const char *AddNewTodayBankPrivatRepayOperationHandler::caption() const
{
    return "Today PrivatBank Repay.";
}