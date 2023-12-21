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
        qDebug() << item.name() << item.balance() << item.version() << item.isDeleted() << item.isForCreate() << item.isForUpdate() << item.isForDelete();
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
 * 1) After operations get in MH in lists creates twins with different versions
 * 2) All changes that has been sent to server has different version after one session (they must have the same version)
 * 3) The changes must will be send after close the session(work in session only with local data)
 * 4) All changes in MH must be doing though DMH(without native access to MH)
*/

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DepositModelHandler dmh;
    printDMH(dmh);

    dmh.addNewDeposit("test2", 0);
    dmh.updateBalance(0, 10);
    dmh.addNewDeposit("test3", 1000);
    dmh.updateBalance(0, 2000);
    dmh.updateBalance(1, 0);
    dmh.deleteDeposit(0);
    dmh.updateBalance(0, 10000);
    dmh.applyChanges();

    int i = 0;
    for(auto item : dmh.listOfChanges())
        // qDebug() << i++ << item->name() << item->balance() << item->version() << item->isDeleted() << item->isForCreate() << item->isForUpdate() << item->isForDelete();
        qDebug() << i++ << item;
    printDMH(dmh);

    for(const auto &item : log())
        qDebug() << item;
    // auto t1 = std::chrono::high_resolution_clock::now();

    // qDebug() << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count();

    QTimer::singleShot(0, &a, SLOT(quit()));
    return a.exec();

    // return App().run();//a.exec();
}
