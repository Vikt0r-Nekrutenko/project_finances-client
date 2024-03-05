#include <QCoreApplication>
#include <QTimer>

#include "window.hpp"
#include "viewholder.hpp"
#include "mainview.hpp"
#include "appmodel.hpp"

class App : public stf::Window
{
public:

    App()
    {
        loadSettings();
        mModel = new AppModel;
        mMainView = new MainView{mModel};
        mViewHolder = mMainView;
    }

    ~App()
    {
        delete mModel;
        saveSettings();
        saveLog();
    }

    bool onUpdate(const float) override
    {
        mViewHolder.currentView()->show(renderer);
        return mViewHolder.currentView()->isContinue();
    }

    void keyEvents(const int key) override
    {
        mViewHolder = mViewHolder.currentView()->keyHandler(key);
    }

    void mouseEvents(const stf::MouseRecord &) override { }

private:

    AppModel *mModel;
    MainView *mMainView;
    ViewHolder mViewHolder;

    void saveLog()
    {
        std::ofstream logFile("last_session_log.log");
        for(auto &item : log())
            logFile << item << std::endl;
        logFile.close();
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int appResult = App().run();
    QTimer::singleShot(0, &a, SLOT(quit()));
    return a.exec() | appResult;
}
