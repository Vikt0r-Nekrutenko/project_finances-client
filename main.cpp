#include <QCoreApplication>
#include <time.hpp>
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

        try {
            model.selectFavCategories(9, 5, 1);
            model.updateStats();
        }catch(const std::exception& ex) {
            stf::Renderer::log << stf::endl << ex.what();
        }
    }

    bool onUpdate(const float) override
    {
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
