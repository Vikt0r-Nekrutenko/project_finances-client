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

        updateStats();
    }

    bool onUpdate(const float) override
    {
        for(int i = 0; i < renderer.Size.x; ++i)
            renderer.drawPixel({i, 1}, '-');
        for(int i = 0; i < renderer.Size.x; ++i)
            renderer.drawPixel({i, stf::Renderer::log.y() - 1}, '-');
        for(int i = 0; i < 59; ++i)
            renderer.drawPixel({i, 13}, '-');
        for(int i = 2; i < int(stf::Renderer::log.y() - 1); ++i)
            renderer.drawPixel({59, i}, '|');

        renderer.draw({60, 2}, "Total earn:.......%d.00 UAH", mSumOfAllEarnOperations);
        renderer.draw({60, 3}, "Total deposits:...%d.00 UAH [%d%c]", mSumOfAllDeposits, int(mSumOfAllDeposits / (float)mSumOfAllEarnOperations * 100.f), '%');
        renderer.draw({60, 4}, "Difference:.......%d.00 UAH [%d%c]", mDiffBetweenSoAEOandSoAD, int(mDiffBetweenSoAEOandSoAD / (float)mSumOfAllEarnOperations * 100.f), '%');
        renderer.draw({60, 5}, "Today PnL:........%d.00 UAH [%d%c]", mTodayPnL, int(mDiffBetweenSoAEOandSoAD / (float)mSumOfAllEarnOperations * 100.f), '%');

        currentView->show(renderer);
        return currentView->isContinue();
    }

    void keyEvents(const int key) override
    {
        currentView = currentView->keyEventsHandler(key);

        updateStats();
    }

    void mouseEvents(const stf::MouseRecord &mr) override
    {
        currentView = currentView->mouseEventsHandler(mr);
    }

private:

    void updateStats()
    {
        mSumOfAllEarnOperations = model.getSumOfAllEarnOperations();
        mSumOfAllDeposits = model.getSumOfAllDeposits();
        mTodayPnL = model.getTodayPnL();
        mDiffBetweenSoAEOandSoAD = mSumOfAllDeposits - mSumOfAllEarnOperations;
    }

    int mSumOfAllEarnOperations = 0,
        mSumOfAllDeposits = 0,
        mDiffBetweenSoAEOandSoAD = 0,
        mTodayPnL = 0;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    return MainWindow().run();
}
