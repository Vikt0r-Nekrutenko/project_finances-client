#ifndef ICOMMAND_HPP
#define ICOMMAND_HPP

#include <string>
#include <unordered_map>

class ICommand
{
public:

    virtual std::string info() const;
    virtual std::string help() const;
    virtual void execute() { }
};

namespace commands {

class Help : public ICommand
{
public:

    std::string info() const final;
    std::string help() const final;
    void execute() final;
    inline void addCommandsList(std::unordered_map<std::string, ICommand *> *commandsList) { mCommandsList = commandsList; }

private:

    std::unordered_map<std::string, ICommand *> *mCommandsList {nullptr};
};
}

#endif // ICOMMAND_HPP
