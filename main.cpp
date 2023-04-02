#include <QCoreApplication>
#include <window.hpp>
#include <smv/iview.hpp>

#include <closeview.hpp>
#include <appmodel.hpp>


class MenuView : public stf::smv::IView
{
public:
    MenuView(AppModel *model)
        : stf::smv::IView(model)
    {

    }
    void show(stf::Renderer &renderer) override
    {
        renderer.drawText({0, 1}, "Press 'q' to exit.");
    }

    stf::smv::IView *keyEventsHandler(const int key) override
    {
        switch (key) {
        case 'q': return new CloseView(static_cast<AppModel*>(m_model));
        }
        return this;
    }
};

class MainWindow : public stf::Window
{
    AppModel model = AppModel();
    MenuView menuView = MenuView(&model);
    CloseView closeView = CloseView(&model);
    stf::smv::IView *currentView = &menuView;

public:
    bool onUpdate(const float dt) override
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
