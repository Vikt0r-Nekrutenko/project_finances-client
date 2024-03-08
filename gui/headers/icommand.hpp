#ifndef ICOMMAND_HPP
#define ICOMMAND_HPP

#include <string>

class ICommand
{
public:

    virtual std::string info() const;
    virtual std::string help() const;
    virtual void execute() { }
};

#endif // ICOMMAND_HPP
