#include <QCoreApplication>
#include <window.hpp>

class MainWindow : public stf::Window
{
public:

    bool onUpdate(const float dt) override
    {
        return true;
    }

    void keyEvents(const int key) override
    {

    }

    void mouseEvents(const stf::MouseRecord &mr) override
    {

    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    return MainWindow().run();
}
