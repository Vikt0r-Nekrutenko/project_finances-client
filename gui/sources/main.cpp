#include <QCoreApplication>
#include <iostream>

#include "headers/categorymodelhandler.hpp"
#include "headers/operationmodelhandler.hpp"
#include "headers/debtmodelhandler.hpp"

#include "window.hpp"
#include "viewholder.hpp"
#include "appmodel.hpp"

class App : public stf::Window
{
public:

    AppModel model;
    ViewHolder viewHolder = ViewHolder(&model);
    IView *currentView;

    App()
    {
        currentView = viewHolder.getStartView();
    }

    bool onUpdate(const float) override
    {
        currentView->show(renderer);
        return currentView->isContinue();
    }

    void keyEvents(const int key) override
    {
        currentView = currentView->keyHandler(key);
    }

    void mouseEvents(const stf::MouseRecord &) override
    {

    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    return App().run();//a.exec();
}
