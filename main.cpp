#include <QCoreApplication>
#include <time.hpp>
#include <window.hpp>

#include "closeview.hpp"
#include "menuview.hpp"
#include "appmodel.hpp"

#include <thread>
#include <chrono>

using namespace std::chrono;

auto tbegin = high_resolution_clock::now();

class MainWindow : public stf::Window
{
    AppModel model = AppModel();
    MenuView menuView = MenuView(&model);
    CloseView closeView = CloseView(&model);
    stf::smv::IView *currentView = &menuView;

public:
    MainWindow()
        : stf::Window()
    {
        stf::Renderer::log.setX(0);
        stf::Renderer::log.setHeight(4);
        stf::Renderer::log.setY(renderer.Size.y - stf::Renderer::log.height());
        enableLog();

        try {
            model.selectFavCategories(9, 5, 1);
            model.updateStats();
        }catch(const std::exception& ex) {
            stf::Renderer::log << stf::endl << ex.what();
        }
    }

    bool onUpdate(const float) override
    {
        static auto tend = duration_cast<milliseconds>(high_resolution_clock::now() - tbegin).count();
        renderer.draw({30, 0}, "Time: %f", (double)tend);
        currentView->show(renderer);
        return currentView->isContinue();
    }

    void keyEvents(const int key) override
    {
        currentView = currentView->keyEventsHandler(key);
    }

    void mouseEvents(const stf::MouseRecord &mr) override
    {
        currentView = currentView->mouseEventsHandler(mr);
    }
};
#include <iostream>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    tbegin = high_resolution_clock::now();
    return MainWindow().run();
}
