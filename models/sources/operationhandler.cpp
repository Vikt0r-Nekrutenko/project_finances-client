#include "operationhandler.hpp"
#include "depositmodel.hpp"
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

OperationHandler::OperationHandler(DepositModel *deposit)
    : mDeposit{deposit} {}

void OperationHandler::updateOperationsList(AppModel *model, const std::string &date)
{
    const int year = QDateTime().fromString(date.c_str(), "yyyy-MM-dd").date().year();
    const int month = QDateTime().fromString(date.c_str(), "yyyy-MM-dd").date().month();
    model->getOperationsByMonth(year, month);
}

AddNewOperationHandler::AddNewOperationHandler(DepositModel *deposit)
    : OperationHandler(deposit) {}

void AddNewOperationHandler::handle(AppModel *model, std::string &input)
{
    std::string date = getStrFromInput(input);
    int amount = getIntFromInput(input);
    std::string category = getStrFromInput(input);

    model->addNewOperation(date.c_str(), mDeposit->name().c_str(), amount, category.c_str());
    updateOperationsList(model, date);
}

const char *AddNewOperationHandler::operationFieldsInfo() const
{
    return "Type 'date amount category' or 'q' to step back:";
}

const char *AddNewOperationHandler::caption() const
{
    return "Add new operation.";
}

DeleteOperationHandler::DeleteOperationHandler(DepositModel *deposit)
    : OperationHandler(deposit) {}

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

ChangeOperationHandler::ChangeOperationHandler(DepositModel *deposit)
    : OperationHandler(deposit) {}

void ChangeOperationHandler::handle(AppModel *model, std::string &input)
{
    int id = getIntFromInput(input) - 1;
    std::string date = getStrFromInput(input);
    int amount = getIntFromInput(input);
    std::string category = getStrFromInput(input);

    model->changeOperation(id, date.c_str(), mDeposit->name().c_str(), amount, category.c_str());
    updateOperationsList(model, date);
}

const char *ChangeOperationHandler::operationFieldsInfo() const
{
    return "Type 'id date amount category' or 'q' to step back:";
}

const char *ChangeOperationHandler::caption() const
{
    return "Change operation.";
}

AddLendOperationHandler::AddLendOperationHandler(DepositModel *deposit)
    : OperationHandler(deposit) {}

void AddLendOperationHandler::handle(AppModel *model, std::string &input)
{
    std::string date = getStrFromInput(input);
    int amount = getIntFromInput(input);
    std::string name = getStrFromInput(input);

    model->addNewLendOperation(date.c_str(), mDeposit->name().c_str(), amount, name.c_str());
    updateOperationsList(model, date);
}

const char *AddLendOperationHandler::operationFieldsInfo() const
{
    return "Type 'date amount name' or 'q' to step back:";
}

const char *AddLendOperationHandler::caption() const
{
    return "Add new lend operation.";
}

AddRepayOperationHandler::AddRepayOperationHandler(DepositModel *deposit)
    : OperationHandler(deposit) {}

void AddRepayOperationHandler::handle(AppModel *model, std::string &input)
{
    std::string date = getStrFromInput(input);
    int amount = getIntFromInput(input);
    std::string name = getStrFromInput(input);

    model->addNewRepayOperation(date.c_str(), mDeposit->name().c_str(), amount, name.c_str());
    updateOperationsList(model, date);
}

const char *AddRepayOperationHandler::operationFieldsInfo() const
{
    return "Type 'date amount name' or 'q' to step back:";
}

const char *AddRepayOperationHandler::caption() const
{
    return "Add new repay operation.";
}

AddNewTodayOperationHandler::AddNewTodayOperationHandler(DepositModel *deposit)
    : OperationHandler(deposit) {}

void AddNewTodayOperationHandler::handle(AppModel *model, std::string &input)
{
    int amount = getIntFromInput(input);
    std::string category = getStrFromInput(input);
    std::string date = QDateTime().currentDateTime().toString("yyyy-MM-dd").toStdString();

    model->addNewOperation(date.c_str(), mDeposit->name().c_str(), amount, category.c_str());
    updateOperationsList(model, date);
}

const char *AddNewTodayOperationHandler::operationFieldsInfo() const
{
    return "Type 'amount category' or 'q' to step back:";
}

const char *AddNewTodayOperationHandler::caption() const
{
    return "Today operation.";
}

SelectListOperationHandler::SelectListOperationHandler(DepositModel *deposit)
    : OperationHandler(deposit) {}

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

AddNewTodayLendOperationHandler::AddNewTodayLendOperationHandler(DepositModel *deposit)
    : OperationHandler(deposit) {}

void AddNewTodayLendOperationHandler::handle(AppModel *model, std::string &input)
{
    int amount = getIntFromInput(input);
    std::string name = getStrFromInput(input);
    std::string date = QDateTime().currentDateTime().toString("yyyy-MM-dd").toStdString();

    model->addNewLendOperation(date.c_str(), mDeposit->name().c_str(), amount, name.c_str());
    updateOperationsList(model, date);
}

const char *AddNewTodayLendOperationHandler::operationFieldsInfo() const
{
    return "Type 'amount name' or 'q' to step back:";
}

const char *AddNewTodayLendOperationHandler::caption() const
{
    return "Today lend.";
}

AddNewTodayRepayOperationHandler::AddNewTodayRepayOperationHandler(DepositModel *deposit)
    : OperationHandler(deposit) {}

void AddNewTodayRepayOperationHandler::handle(AppModel *model, std::string &input)
{
    int amount = getIntFromInput(input);
    std::string name = getStrFromInput(input);
    std::string date = QDateTime().currentDateTime().toString("yyyy-MM-dd").toStdString();

    model->addNewRepayOperation(date.c_str(), mDeposit->name().c_str(), amount, name.c_str());
    updateOperationsList(model, date);
}

const char *AddNewTodayRepayOperationHandler::operationFieldsInfo() const
{
    return "Type 'amount name' or 'q' to step back:";
}

const char *AddNewTodayRepayOperationHandler::caption() const
{
    return "Today repay.";
}
