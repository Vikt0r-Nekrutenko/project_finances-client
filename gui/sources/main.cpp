#include <QCoreApplication>
#include <iostream>
#include "headers/depositmodel.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    DepositModel privat("PrivatBank", 0);
    privat.read();

    for(const auto &str : log()) {
        std::cout << str << std::endl;
    }

    std::cout << privat.balance() << std::endl;

    return a.exec();
}
