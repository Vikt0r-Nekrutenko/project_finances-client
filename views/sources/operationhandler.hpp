#ifndef OPERATIONHANDLER_HPP
#define OPERATIONHANDLER_HPP

class AppModel;

class OperationHandler
{
public:
    virtual void handle(AppModel *model) = 0;
};

#endif // OPERATIONHANDLER_HPP
