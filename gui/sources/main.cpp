#include <QCoreApplication>
#include <iostream>
#include <thread>

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

    AppModel *model;
    MainView *mainView;
    ViewHolder viewHolder;

    App()
    {
        viewHolder = new StartView(nullptr);;
        std::thread([this](){
            model = new AppModel;
            mainView = new MainView{model};
            viewHolder = mainView;
        }).detach();
    }

    ~App()
    {
        delete model;
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
