#include <QCoreApplication>
#include <iostream>
#include "headers/depositmodelhandler.hpp"
#include "headers/categorymodelhandler.hpp"
#include "headers/operationmodelhandler.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    DepositModelHandler depo;
    CategoryModelHandler cats;
    OperationModelHandler oper;

    auto &op = oper.operations().back();
    std::cout << op.rawCategory(cats).name() << std::endl;

    return 0;//a.exec();
}
