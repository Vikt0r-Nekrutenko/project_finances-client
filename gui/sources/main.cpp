#include <QCoreApplication>
#include <QTimer>
#include <iostream>

#include "window.hpp"
#include "viewholder.hpp"
#include "mainview.hpp"
#include "appmodel.hpp"
#include "icommand.hpp"

int parseCmdParams(const std::unordered_map<std::string, ICommand *> &commandsList, int argc, char **argv)
{
    int n = 1;
    do {
        if(argv[n][0] == '@') {
            auto result = commandsList.find(argv[n]);
            if(result != commandsList.end()) {
                std::cout << result->second->info() << std::endl;
                result->second->execute(n, argv);
            }
        }
    } while(++n < argc);
    return 0;
}

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
    int appResult = 0;

    if(argc > 1) {
        AppModel model;
        std::unordered_map<std::string, ICommand *> commands {
            {"@help", new commands::Help},
            {"@log", new commands::Log},
            {"@addop", new commands::AddOperation{&model}},
            {"@addtdop", new commands::AddTodayOperation{&model}},
        };
        dynamic_cast<commands::Help *>(commands["@help"])->addCommandsList(&commands);

        appResult = parseCmdParams(commands, argc, argv);
    } else
        appResult = App().run();

    QTimer::singleShot(0, &a, SLOT(quit()));
    return a.exec() | appResult;
}
