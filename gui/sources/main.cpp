#include <QCoreApplication>
#include <iostream>
#include "headers/debtmodelhandler.hpp"

void show(DebtModelHandler &depo) {
    for(const auto &depo : depo.debts())
        std::cout << depo.id() << " "
                  << depo.name() << "\t"
                  << depo.amount() << " "
                  << depo.isCreated() << " "
                  << depo.isChanched() << " "
                  << depo.isDeleted() << std::endl;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    DebtModelHandler depo;

    for(const auto &str : log()) {
        std::cout << str << std::endl;
    }

    show(depo);

//    depo.deleteDeposit(5);

//    show(depo);

    return 0;//a.exec();
}
