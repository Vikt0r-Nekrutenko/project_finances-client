#ifndef OPERATIONHANDLER_HPP
#define OPERATIONHANDLER_HPP

#include <string>
class AppModel;
class DepositModel;

class OperationHandler
{
public:
    OperationHandler(DepositModel *deposit);
    virtual ~OperationHandler() = default;
    virtual void handle(AppModel *model, std::string &input) = 0;
    virtual const char *operationFieldsInfo() const = 0;
    virtual const char *caption() const = 0;

protected:

    void updateOperationsList(AppModel *model, const std::string &date);
    int getIntFromInput(std::string &input);
    std::string getStrFromInput(std::string &input);

    DepositModel *mDeposit;
};

class AddNewOperationHandler : public OperationHandler
{
public:
    AddNewOperationHandler(DepositModel *deposit);
    void handle(AppModel *model, std::string &input) override;
    const char *operationFieldsInfo() const override;
    const char *caption() const override;
};

class DeleteOperationHandler : public OperationHandler
{
public:
    DeleteOperationHandler(DepositModel *deposit);
    void handle(AppModel *model, std::string &input) override;
    const char *operationFieldsInfo() const override;
    const char *caption() const override;
};

class ChangeOperationHandler : public OperationHandler
{
public:
    ChangeOperationHandler(DepositModel *deposit);
    void handle(AppModel *model, std::string &input) override;
    const char *operationFieldsInfo() const override;
    const char *caption() const override;
};

class AddLendOperationHandler : public OperationHandler
{
public:
    AddLendOperationHandler(DepositModel *deposit);
    void handle(AppModel *model, std::string &input) override;
    const char *operationFieldsInfo() const override;
    const char *caption() const override;
};

class AddRepayOperationHandler : public OperationHandler
{
public:
    AddRepayOperationHandler(DepositModel *deposit);
    void handle(AppModel *model, std::string &input) override;
    const char *operationFieldsInfo() const override;
    const char *caption() const override;
};

class SelectListOperationHandler : public OperationHandler
{
public:
    SelectListOperationHandler(DepositModel *deposit);
    void handle(AppModel *model, std::string &input) override;
    const char *operationFieldsInfo() const override;
    const char *caption() const override;
};

class AddNewTodayOperationHandler : public OperationHandler
{
public:
    void handle(AppModel *model, std::string &input) override;
    const char *operationFieldsInfo() const override;
    const char *caption() const override;
};

class AddNewTodayLendOperationHandler : public OperationHandler
{
public:
    void handle(AppModel *model, std::string &input) override;
    const char *operationFieldsInfo() const override;
    const char *caption() const override;
};

class AddNewTodayRepayOperationHandler : public OperationHandler
{
public:
    void handle(AppModel *model, std::string &input) override;
    const char *operationFieldsInfo() const override;
    const char *caption() const override;
};

#endif // OPERATIONHANDLER_HPP
