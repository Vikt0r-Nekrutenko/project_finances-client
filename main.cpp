#include <QCoreApplication>
#include <window.hpp>
#include <smv/iview.hpp>
#include <smv/imodel.hpp>

class Model : public stf::smv::BaseModel {};

class CloseView : public stf::smv::IView
{
public:
    CloseView(Model *model)
        : stf::smv::IView(model) { }

    bool isContinue() const override
    {
        return false;
    }

    void show(stf::Renderer&) override { };

    IView* update(const float) override
    {
        return this;
    }
};

class MenuView : public stf::smv::IView
{
public:
    MenuView(Model *model)
        : stf::smv::IView(model)
    {

    }
    void show(stf::Renderer &renderer) override
    {

    }

    stf::smv::IView *keyEventsHandler(const int key) override
    {
        switch (key) {
        case 'q': return new CloseView(static_cast<Model*>(m_model));
        }
        return this;
    }
};

class MainWindow : public stf::Window
{
    Model model = Model();
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
