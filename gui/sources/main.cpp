#include <QCoreApplication>
#include <QTimer>
#include <thread>

#include "window.hpp"
#include "viewholder.hpp"
#include "mainview.hpp"
#include "appmodel.hpp"

class App : public stf::Window
{
public:

    App()
    {
        mViewHolder = new StartView(nullptr);;
        std::thread([this](){
            mModel = new AppModel;
            mMainView = new MainView{mModel};
            mViewHolder = mMainView;
        }).detach();
    }

    ~App()
    {
        delete mModel;
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
};

void printDMH(const DepositModelHandler &dmh)
{
    for(const auto &item : dmh.deposits())
        qDebug() << item.name() << item.balance() << item.version() << item.isCreated() << item.isChanched() << item.isDeleted();
    qDebug() << "---DMH ver:" << dmh.version();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DepositModelHandler dmh;
    printDMH(dmh);

    // dmh.addNewDeposit("Test", 0);
    // printDMH(dmh);
    // dmh.updateBalance(6, 10);
    // printDMH(dmh);
    dmh.deleteDeposit(6);
    printDMH(dmh);

    for(const auto &item : log())
        qDebug() << item;

    QTimer::singleShot(0, &a, SLOT(quit()));
    return a.exec();
    // return App().run();//a.exec();
}
