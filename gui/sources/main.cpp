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
        // std::thread([this](){
            mModel = new AppModel;
            mMainView = new MainView{mModel};
            mViewHolder = mMainView;
        // }).detach();
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
    int i = 0;
    for(const auto &item : dmh.deposits())
        qDebug() << i++ << item.name() << item.balance() << item.version() << item.isDeleted() << item.isForCreate() << item.isForUpdate() << item.isForDelete();
    qDebug() << "---DMH ver:" << dmh.version();
}

void printCMH(const CategoryModelHandler &cmh)
{
    for(const auto &item : cmh.categories())
        qDebug() << item.name() << item.type() << item.version() << item.isDeleted() << item.isForCreate() << item.isForUpdate() << item.isForDelete();
    qDebug() << "---CMH ver:" << cmh.version();
}

void printBMH(const DebtModelHandler &cmh)
{
    for(const auto &item : cmh.debts())
        qDebug() << item.id() << item.name() << item.amount() << item.version() << item.isDeleted() << item.isForCreate() << item.isForUpdate() << item.isForDelete();
    qDebug() << "---BMH ver:" << cmh.version();
}

void printOMH(const OperationModelHandler &omh)
{
    auto item = omh.operations().back();
    // for(const auto &item : omh.operations())
        qDebug() << item.id() << item.date() << item.deposit() << item.amount() << item.category() << item.version() << item.isDeleted() << item.isForCreate() << item.isForUpdate() << item.isForDelete();
    qDebug() << "---OMH ver:" << omh.version();
}

/*
 * TO FIX:
 * 1) + After operations get in MH in lists creates twins with different versions
 * 2) + All changes that has been sent to server has different version after one session (they must have the same version)
 * 3) + The changes must will be send after close the session(work in session only with local data)
 * 4) All changes in MH must be doing though DMH(without native access to MH)
 * 5) If on d1 i have ver.11 unsync data and d2 ver.17 unsync data, then d1 will be sync, d2 never read data with ver.11
 * (TO RESOLVE no.5 need save last sync version and send she in all get request. she change after successful sync)
 * 6) If new deposit name has same name as deposit marked is_deleted, need to change exist deposit instead add new
*/

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // DepositModelHandler dmh;
    // printDMH(dmh);

    // dmh.addNewDeposit("test2", 0);
    // dmh.updateBalance(7, 1000);
    // dmh.updateBalance(8, 2000);
    // dmh.deleteDeposit(7);
    // dmh.updateBalance(7, 10000);

    // for(const auto &item : log())
        // qDebug() << item;
    // auto t1 = std::chrono::high_resolution_clock::now();

    // qDebug() << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count();

    // QTimer::singleShot(0, &a, SLOT(quit()));
    // return a.exec();

    return App().run();//a.exec();
}
