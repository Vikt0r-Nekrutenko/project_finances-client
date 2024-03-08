#ifndef ICOMMAND_HPP
#define ICOMMAND_HPP

#include <string>
#include <unordered_map>

class ICommand
{
public:

    virtual std::string info() const;
    virtual std::string help() const;
    virtual void execute(int &, char **) { }
};

namespace commands {

class Help : public ICommand
{
public:

    std::string info() const final;
    std::string help() const final;
    void execute(int &, char **) final;
    inline void addCommandsList(std::unordered_map<std::string, ICommand *> *commandsList) { mCommandsList = commandsList; }

private:

    std::unordered_map<std::string, ICommand *> *mCommandsList {nullptr};
};

class Log : public ICommand
{
public:

    std::string info() const final;
    std::string help() const final;
    void execute(int &, char **) final;
};

class AddOperation : public ICommand
{
public:

    std::string info() const final;
    std::string help() const final;
    void execute(int &n, char **argv) final;
};
}

#endif // ICOMMAND_HPP
