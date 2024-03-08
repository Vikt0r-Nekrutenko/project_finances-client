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

class AppModel;

class IModelCommand
{
public:

    IModelCommand(AppModel *model);
    virtual ~IModelCommand() = default;

protected:

    AppModel *mModel {nullptr};
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

class AddOperation : public ICommand, public IModelCommand
{
public:

    AddOperation(AppModel *model);
    std::string info() const override;
    std::string help() const override;
    void execute(int &n, char **argv) override;

protected:

    virtual std::string parseDate(int &n, char **argv) const;
};

class AddTodayOperation : public AddOperation
{
public:

    AddTodayOperation(AppModel *model);
    std::string help() const override;

protected:

    std::string parseDate(int &n, char **argv) const override;
};
}

#endif // ICOMMAND_HPP
