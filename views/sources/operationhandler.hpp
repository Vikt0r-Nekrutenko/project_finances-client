#ifndef OPERATIONHANDLER_HPP
#define OPERATIONHANDLER_HPP

#include <string>
class AppModel;

class OperationHandler
{
public:
    virtual void handle(AppModel *model, std::string &input) = 0;
};

class AddNewOperationHandler : public OperationHandler
{
public:
    void handle(AppModel *model, std::string &input) override;
};

#endif // OPERATIONHANDLER_HPP
