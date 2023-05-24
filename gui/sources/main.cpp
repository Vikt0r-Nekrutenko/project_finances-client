#include <QCoreApplication>
#include <iostream>
#include "headers/depositmodelhandler.hpp"

void show(DepositModelHandler &depo) {
    for(const auto &depo : depo.deposits())
        std::cout << depo.name() << "\t"
                  << depo.balance() << " "
                  << depo.mIsCreated << " "
                  << depo.mIsChanched << " "
                  << depo.mIsDeleted << std::endl;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    DepositModelHandler depo;

    for(const auto &str : log()) {
        std::cout << str << std::endl;
    }

    show(depo);

//    depo.addNewDeposit("Test", 100);
//    show(depo);

    return 0;//a.exec();
}
