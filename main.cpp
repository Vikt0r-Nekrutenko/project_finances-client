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

    bool onUpdate(const float) override
    {
        for(int i = 0; i < renderer.Size.x; ++i)
            renderer.drawPixel({i, 1}, '-');
        for(int i = 0; i < 59; ++i)
            renderer.drawPixel({i, 8}, '-');
        for(int i = 2; i < renderer.Size.y; ++i)
            renderer.drawPixel({59, i}, '|');

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

    stf::Renderer::log.setX(60);
    stf::Renderer::log.setHeight(20);
    stf::Renderer::log.setY(2);

    MainWindow wnd;
    wnd.enableLog();
    return wnd.run();
}
