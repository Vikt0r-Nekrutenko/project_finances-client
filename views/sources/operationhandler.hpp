#ifndef OPERATIONHANDLER_HPP
#define OPERATIONHANDLER_HPP

#include <string>
class AppModel;

class OperationHandler
{
public:
    virtual ~OperationHandler() = default;
    int getIntFromInput(std::string &input);
    std::string getStrFromInput(std::string &input);
    void updateOperationsList(AppModel *model, const std::string &date);
    virtual void handle(AppModel *model, std::string &input) = 0;
    virtual const char *operationFieldsInfo() const = 0;
};

class AddNewOperationHandler : public OperationHandler
{
public:
    void handle(AppModel *model, std::string &input) override;
    const char *operationFieldsInfo() const override;
};

class DeleteOperationHandler : public OperationHandler
{
public:
    void handle(AppModel *model, std::string &input) override;
    const char *operationFieldsInfo() const override;
};

class ChangeOperationHandler : public OperationHandler
{
public:
    void handle(AppModel *model, std::string &input) override;
    const char *operationFieldsInfo() const override;
};

#endif // OPERATIONHANDLER_HPP
