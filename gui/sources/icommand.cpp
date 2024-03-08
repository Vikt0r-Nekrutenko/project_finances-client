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

std::string commands::AddOperation::help() const { return "Add a new operation"; }

void commands::AddOperation::execute(int &n, char **argv)
{
    std::string date = argv[++n];
    std::string depo = argv[++n];
            int amot = std::stoi(argv[++n]);
    std::string catg = argv[++n];

    mModel->Deposits.selectDeposit(std::distance(mModel->Deposits.query.cbegin(), mModel->Deposits.query.findByName(depo)));
    std::cout
        << "Date: " << date << "\n"
        << "Deposit: " << mModel->Deposits.selectedDeposit()->name() << "\n"
        << "Amount: " << amot << "\n"
        << "Category: " << catg << std::endl;
}
