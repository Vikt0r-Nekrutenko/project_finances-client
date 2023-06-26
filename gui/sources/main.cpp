#include <QCoreApplication>
#include <iostream>

#include "window.hpp"
#include "viewholder.hpp"
#include "mainview.hpp"
#include "appmodel.hpp"

class StartView : public IView
{
public:

    StartView(AppModel *model)
        : IView(model) { }

    void show(stf::Renderer &renderer) override
    {
        renderer.drawText({renderer.Size.x / 2, renderer.Size.y / 2}, "Start view");
    }

    IView *keyHandler(int) override
    {
        return this;
    }
};

class App : public stf::Window
{
public:

    AppModel model;
    MainView *mainView = new MainView{&model};
    StartView *startView = new StartView(&model);
    ViewHolder viewHolder;

    App()
    {
        viewHolder = startView;
    }

    bool onUpdate(const float) override
    {
        viewHolder.currentView()->show(renderer);
        renderer.draw({renderer.Size.x - 20, 0}, "Views [Count] : [%d]", viewHolder.viewsCount());
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
