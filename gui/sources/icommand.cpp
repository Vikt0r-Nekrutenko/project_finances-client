#include "icommand.hpp"
#include "appmodel.hpp"
#include <iostream>

IModelCommand::IModelCommand(AppModel *model)
    : mModel{model} { }

std::string ICommand::info() const { return ""; }

std::string ICommand::help() const { return ""; }

std::string commands::Help::info() const { return "Commands list:"; }

std::string commands::Help::help() const{ return "Get a commands list with descriptions"; }

void commands::Help::execute(int &, char **)
{
    for(const auto &item : *mCommandsList) {
        std::cout << "\t" << item.first << " - " << item.second->help() << std::endl;
    }
}

std::string commands::Log::info() const { return "Current session log:"; }

std::string commands::Log::help() const { return "Get a current session log"; }

void commands::Log::execute(int &, char **)
{
    for(const auto &item : log()) {
        std::cout << "\t" << item << std::endl;
    }
}

commands::AddOperation::AddOperation(AppModel *model)
    : IModelCommand{model} { }

std::string commands::AddOperation::info() const { return ""; }

std::string commands::AddOperation::help() const { return "Add a new operation: yyyy-mm-dd Deposit Amount Category"; }

void commands::AddOperation::execute(int &n, char **argv)
{
    std::string date = parseDate(n, argv);
    std::string depo = argv[++n];
    int amount = 0;
    try{
        amount = std::stoi(argv[++n]);
    } catch(...) {
        return;
    }
    std::string category = argv[++n];

    auto depoIt = mModel->Deposits.query.findByName(depo);

    if(depoIt == mModel->Deposits.query.end()) {
        log().push_back({"Deposit with name [" + depo + "] doesn't exist!"});
        return;
    }

    mModel->Deposits.selectDeposit(std::distance(mModel->Deposits.query.cbegin(), depoIt));

    if(mModel->Categories.query.findByName(category) == mModel->Categories.query.end()) {
        log().push_back({"Category with name [" + category + "] doesn't exist!"});
        return;
    }

    mModel->addNewOperation(date, amount, category);
    std::string result = "Operation successfully added! Deposit [" + mModel->Deposits.selectedDeposit()->name() + "] balance now: " + std::to_string(mModel->Deposits.selectedDeposit()->balance()) + ".00 UAH";
    log().push_back(result);
    std::cout << result << std::endl;
}

std::string commands::AddOperation::parseDate(int &n, char **argv) const
{
    return argv[++n];
}

commands::AddTodayOperation::AddTodayOperation(AppModel *model)
    : AddOperation{model} { }

std::string commands::AddTodayOperation::help() const { return "Add a new today operation: Deposit Amount Category"; }


