#include <QCoreApplication>
#include <iostream>
#include "headers/depositmodelhandler.hpp"
#include "headers/categorymodelhandler.hpp"
#include "headers/operationmodelhandler.hpp"
#include "headers/debtmodelhandler.hpp"

#include "window.hpp"
#include "iview.hpp"

class AppModel {};

class ViewHolder {};

class App : public stf::Window
{
public:
    AppModel appModel;
    ViewHolder viewHolder;

    IView view = IView(&appModel, &viewHolder);

    bool onUpdate(const float dt) override
    {
        view.show(renderer);
        return true;
    }

    void keyEvents(const int key) override
    {
        view.keyHandler(key);
    }

    void mouseEvents(const stf::MouseRecord &mr) override
    {

    }
};

int main(int argc, char *argv[])
{
    /*QCoreApplication a(argc, argv);
    DepositModelHandler depo;
    CategoryModelHandler cats;
    OperationModelHandler oper;
    DebtModelHandler debts;

    int option = 0;
    do {
        std::cout << "Choose an option:\n"
                     "1.Deposits.\n"
                     "2.Debts.\n"
                     "3.Categories.\n"
                     "0.Exit.\n"
                     " >> ";

        std::cin >> option;

        switch (option)
        {
        case 1:
            for(const auto &deposit : depo.deposits())
                std::cout << deposit.name() << "\t" << deposit.balance() << std::endl;

            break;
        case 2:
            for(const auto &debt : debts.debts())
                std::cout << debt.name() << "\t" << debt.amount() << std::endl;

            break;
        case 3:
            for(const auto &category : cats.categories())
                std::cout << category.name() << "\t" << category.type() << std::endl;

            break;
        }
    } while(option);*/
    return App().run();//a.exec();
}
