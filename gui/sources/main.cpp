#include <QCoreApplication>
#include <iostream>
#include "headers/depositmodelhandler.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    DepositModelHandler depo;

    for(const auto &str : log()) {
        std::cout << str << std::endl;
    }

    for(const auto &depo : depo.deposits())
        std::cout << depo.name() << "\t"
              << depo.balance() << " "
              << depo.mIsCreated << " "
              << depo.mIsChanched << " "
              << depo.mIsDeleted << std::endl;

    return 0;//a.exec();
}
