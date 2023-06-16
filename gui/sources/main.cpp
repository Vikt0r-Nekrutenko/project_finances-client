#include <QCoreApplication>
#include <iostream>

#include "headers/categorymodelhandler.hpp"
#include "headers/operationmodelhandler.hpp"
#include "headers/debtmodelhandler.hpp"

#include "window.hpp"
#include "viewholder.hpp"
#include "mainview.hpp"
#include "appmodel.hpp"

class App : public stf::Window
{
public:

    AppModel model;
    MainView *mainView = new MainView{&model};
    ViewHolder viewHolder;

    App()
    {
        viewHolder = mainView;
    }

    bool onUpdate(const float) override
    {
        viewHolder.currentView()->show(renderer);
        return viewHolder.currentView()->isContinue();
    }

    void keyEvents(const int key) override
    {
        viewHolder = viewHolder.currentView()->keyHandler(key);
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
