#include <QCoreApplication>
#include <window.hpp>

#include "closeview.hpp"
#include "menuview.hpp"
#include "appmodel.hpp"

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
    }

    bool onUpdate(const float) override
    {
        for(int i = 0; i < renderer.Size.x; ++i)
            renderer.drawPixel({i, 1}, '-');
        for(int i = 0; i < renderer.Size.x; ++i)
            renderer.drawPixel({i, stf::Renderer::log.y() - 1}, '-');
        for(int i = 0; i < 59; ++i)
            renderer.drawPixel({i, 13}, '-');
        for(int i = 2; i < int(stf::Renderer::log.y() - 1); ++i)
            renderer.drawPixel({59, i}, '|');

        renderer.draw({60, 2}, "Total earn: %d.00 UAH", model.calculateAllEarnOperations());

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

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    return MainWindow().run();
}
