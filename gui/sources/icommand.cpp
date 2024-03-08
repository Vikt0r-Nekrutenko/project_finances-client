#include "icommand.hpp"
#include <iostream>

std::string ICommand::info() const { return ""; }

std::string ICommand::help() const { return ""; }

std::string commands::Help::info() const
{
    return "Commands list:";
}

std::string commands::Help::help() const
{
    return "Get a commands list with descriptions";
}

void commands::Help::execute()
{
    for(const auto &item : *mCommandsList) {
        std::cout << "\t" << item.first << " - " << item.second->help() << std::endl;
    }
}
