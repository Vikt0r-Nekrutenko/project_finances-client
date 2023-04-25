#include "operationhandler.hpp"
#include "depositmodel.hpp"
#include "appmodel.hpp"

int OperationHandler::getExpressionResultFromInput(std::string &input)
{
    std::string expression = getStrFromInput(input);
    std::vector<char> operators;
    std::vector<int> operands;
    std::string::iterator it = expression.begin(), jt = expression.begin();

    for(; it != expression.end(); ++it) {
        if(*it == '+' || *it == '-') {
            operators.push_back(*it);
            operands.push_back(std::stoi(std::string(jt, it)));
            jt = it + 1;
        }
    }
    operands.push_back(std::stoi(std::string(jt, it)));

    int result = operands.at(0);
    std::vector<int>::iterator operand = operands.begin() + 1;

    for(auto op : operators) {
        switch (op) {
        case '+': result += *operand; break;
        case '-': result -= *operand; break;
        }
        ++operand;
    }
    return result;
}

int OperationHandler::getIntFromInput(std::string &input)
{
    return getExpressionResultFromInput(input);
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

AddNewOperationHandler::AddNewOperationHandler(DepositModel *deposit)
    : OperationHandler(deposit) {}

void AddNewOperationHandler::handle(AppModel *model, std::string &input)
{
    std::string date = getStrFromInput(input);
    int amount = getIntFromInput(input);
    std::string category = getStrFromInput(input);

    model->addNewOperation(date.c_str(), mDeposit->name().c_str(), amount, category.c_str());
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
    model->deleteOperation(id);
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
}

const char *AddNewTodayOperationHandler::operationFieldsInfo() const
{
    return "Type 'amount category' or 'q' to step back:";
}

const char *AddNewTodayOperationHandler::caption() const
{
    return "Today operation.";
}

AddNewTodayLendOperationHandler::AddNewTodayLendOperationHandler(DepositModel *deposit)
    : OperationHandler(deposit) {}

void AddNewTodayLendOperationHandler::handle(AppModel *model, std::string &input)
{
    int amount = getIntFromInput(input);
    std::string name = getStrFromInput(input);
    std::string date = QDateTime().currentDateTime().toString("yyyy-MM-dd").toStdString();

    model->addNewLendOperation(date.c_str(), mDeposit->name().c_str(), amount, name.c_str());
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
}

const char *AddNewTodayRepayOperationHandler::operationFieldsInfo() const
{
    return "Type 'amount name' or 'q' to step back:";
}

const char *AddNewTodayRepayOperationHandler::caption() const
{
    return "Today repay.";
}
