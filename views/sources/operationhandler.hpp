#ifndef OPERATIONHANDLER_HPP
#define OPERATIONHANDLER_HPP

#include <string>
class AppModel;

class OperationHandler
{
public:
    virtual ~OperationHandler() = default;
    virtual void handle(AppModel *model, std::string &input) = 0;
    virtual const char *operationFieldsInfo() const = 0;
    virtual const char *caption() const = 0;

protected:

    void updateOperationsList(AppModel *model, const std::string &date);
    int getIntFromInput(std::string &input);
    std::string getStrFromInput(std::string &input);
};

class AddNewOperationHandler : public OperationHandler
{
public:
    void handle(AppModel *model, std::string &input) override;
    const char *operationFieldsInfo() const override;
    const char *caption() const override;
};

class DeleteOperationHandler : public OperationHandler
{
public:
    void handle(AppModel *model, std::string &input) override;
    const char *operationFieldsInfo() const override;
    const char *caption() const override;
};

class ChangeOperationHandler : public OperationHandler
{
public:
    void handle(AppModel *model, std::string &input) override;
    const char *operationFieldsInfo() const override;
    const char *caption() const override;
};

class AddLendOperationHandler : public OperationHandler
{
public:
    void handle(AppModel *model, std::string &input) override;
    const char *operationFieldsInfo() const override;
    const char *caption() const override;
};

class AddRepayOperationHandler : public OperationHandler
{
public:
    void handle(AppModel *model, std::string &input) override;
    const char *operationFieldsInfo() const override;
    const char *caption() const override;
};

class SelectListOperationHandler : public OperationHandler
{
public:
    void handle(AppModel *model, std::string &input) override;
    const char *operationFieldsInfo() const override;
};

class AddNewTodayBankPrivatOperationHandler : public OperationHandler
{
public:
    void handle(AppModel *model, std::string &input) override;
    const char *operationFieldsInfo() const override;
};

class AddNewTodayBankPrivatLendOperationHandler : public OperationHandler
{
public:
    void handle(AppModel *model, std::string &input) override;
    const char *operationFieldsInfo() const override;
};

class AddNewTodayBankPrivatRepayOperationHandler : public OperationHandler
{
public:
    void handle(AppModel *model, std::string &input) override;
    const char *operationFieldsInfo() const override;
};

#endif // OPERATIONHANDLER_HPP
