#ifndef ICOMMAND_HPP
#define ICOMMAND_HPP

#include <string>

class ICommand
{
public:

    virtual std::string info() const { return ""; }
    virtual void execute() { }
};

#endif // ICOMMAND_HPP
