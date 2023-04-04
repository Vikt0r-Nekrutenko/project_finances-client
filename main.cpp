#include <QCoreApplication>
#include <time.hpp>
#include <window.hpp>

#include "closeview.hpp"
#include "menuview.hpp"
#include "appmodel.hpp"
#include "modelviewwithinputfield.hpp"

#define inPercentage(a, b) int(a / (float)b * 100.f)

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

        model.selectFavCategories(9, 5, 1);
        updateStats();
    }

    bool onUpdate(const float) override
    {
        for(int i = 0; i < renderer.Size.x; ++i)
            renderer.drawPixel({i, 1}, '-');
        for(int i = 0; i < renderer.Size.x; ++i)
            renderer.drawPixel({i, int(stf::Renderer::log.y() - 1)}, '-');
        for(int i = 0; i < 59; ++i)
            renderer.drawPixel({i, 13}, '-');
        for(int i = 2; i < int(stf::Renderer::log.y() - 1); ++i)
            renderer.drawPixel({59, i}, '|');

        renderer.draw({60,  2}, "Total earn:.......%m.00 UAH", mSumOfAllEarnOperations);
        renderer.draw({60,  3}, "Total deposits:...%m.00 UAH [%d%c]", mSumOfAllDeposits, inPercentage(mSumOfAllDeposits, mSumOfAllEarnOperations), '%');
        renderer.draw({60,  4}, "Total P&L:........%m.00 UAH [%d%c]", mTotalPnL, inPercentage(mTotalPnL, mSumOfAllEarnOperations), '%');
        renderer.draw({60,  6}, "P&L's:");
        renderer.draw({60,  7}, "Today PnL:...%m.00 UAH [%d%c]", mTodayPnL, inPercentage(mTodayPnL, mSumOfAllEarnOperations), '%');
        renderer.draw({60,  8}, "Week PnL:....%m.00 UAH [%d%c]", mWeekPnL, inPercentage(mWeekPnL, mSumOfAllEarnOperations), '%');
        renderer.draw({60,  9}, "Month PnL:...%m.00 UAH [%d%c]", mMonthPnL, inPercentage(mMonthPnL, mSumOfAllEarnOperations), '%');
        renderer.draw({60, 10}, "Year PnL:....%m.00 UAH [%d%c]", mYearPnL, inPercentage(mYearPnL, mSumOfAllEarnOperations), '%');
        renderer.draw({60,  12}, "Favorite categories:");
        int i = 1;
        for(const auto &favcat : mFavCats) {
            renderer.draw({60,  12 + i}, "%s", favcat.first.toStdString().c_str());
            renderer.draw({70, 12 + i++}, "%m.00 UAH", favcat.second);
        }

        currentView->show(renderer);
        return currentView->isContinue();
    }

    void keyEvents(const int key) override
    {
        currentView = currentView->keyEventsHandler(key);

        if(key == 'r' && (static_cast<ModelViewWithInputField*>(currentView)->option() == 0 || currentView == &menuView))
            updateStats();
    }

    void mouseEvents(const stf::MouseRecord &mr) override
    {
        currentView = currentView->mouseEventsHandler(mr);
    }

private:

    void updateStats()
    {
        model.updateAllHandlers();

        mSumOfAllEarnOperations = model.getSumOfAllEarnOperations();
        mSumOfAllDeposits = model.getSumOfAllDeposits();
        mTodayPnL = model.getTodayPnL();
        mWeekPnL = model.getWeekPnL();
        mMonthPnL = model.getMonthPnL();
        mYearPnL = model.getYearPnl();
        mTotalPnL = mSumOfAllDeposits - mSumOfAllEarnOperations;

        mFavCats.clear();
        for(const auto &favcat : model.favCategories())
            mFavCats.push_back({favcat.name(), model.getSum30DeysOfOperationsByCategory(favcat)});
    }

    QVector<QPair<QString, int>> mFavCats;

    int mSumOfAllEarnOperations = 0,
        mSumOfAllDeposits = 0,
        mTotalPnL = 0,
        mTodayPnL = 0,
        mWeekPnL = 0,
        mMonthPnL = 0,
        mYearPnL = 0;
};
#include <iostream>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    return MainWindow().run();
}
