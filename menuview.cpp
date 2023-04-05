#include "menuview.hpp"
#include "appmodel.hpp"
#include "closeview.hpp"
#include "debtlistview.hpp"
#include "depositlistview.hpp"
#include "operationslistview.hpp"
#include "categorylistview.hpp"

#define inPercentage(a, b) int(a / (float)b * 100.f)

MenuView::MenuView(AppModel *model)
    : stf::smv::IView(model) {}

void MenuView::show(stf::Renderer &renderer)
{
    auto drawLine = [&](int beginX, int endX, int y){
        for(int j = beginX; j < endX; ++j)
            renderer.drawPixel({j, y}, '.');
    };

    renderer.drawText({0, 2}, "1.Deposits.");
    renderer.drawText({0, 3}, "2.Operations.");
    renderer.drawText({0, 4}, "3.Categories.");
    renderer.drawText({0, 5}, "4.Debts.");
    renderer.drawText({0, 6}, "Press 'q' to exit.");

    renderer.draw({60,  2}, "Total earn:.......%m.00 UAH", mSumOfAllEarnOperations);
    renderer.draw({60,  3}, "Total deposits:...%m.00 UAH [%d%c]", mSumOfAllDeposits, inPercentage(mSumOfAllDeposits, mSumOfAllEarnOperations), '%');
    renderer.draw({60,  4}, "Total P&L:........%m.00 UAH [%d%c]", mTotalPnL, inPercentage(mTotalPnL, mSumOfAllEarnOperations), '%');

    renderer.draw({60,  6}, "P&L's:");
    renderer.draw({60,  7}, "Today PnL:...%m.00 UAH", mTodayPnL);

    renderer.draw({90,  7}, "[%d%c]", inPercentage(mTodayPnL, mSumOfAllEarnOperations), '%');

    renderer.draw({60,  8}, "Week PnL:....%m.00 UAH", mWeekPnL);
    renderer.draw({90,  8}, "[%d%c]", inPercentage(mWeekPnL, mSumOfAllEarnOperations), '%');

    renderer.draw({60,  9}, "Month PnL:...%m.00 UAH", mMonthPnL);
    renderer.draw({90,  9}, "[%d%c]", inPercentage(mMonthPnL, mSumOfAllEarnOperations), '%');

    renderer.draw({60, 10}, "Year PnL:....%m.00 UAH", mYearPnL);
    renderer.draw({90, 10}, "[%d%c]", inPercentage(mYearPnL, mSumOfAllEarnOperations), '%');

    renderer.draw({60, 12}, "Favorite categories:");
    int i = 1;
    for(const auto &favcat : mFavCats) {
        renderer.draw({60, 12 + i}, "%s", favcat.first.toStdString().c_str());
        renderer.draw({70, 12 + i}, "%m.00 UAH", favcat.second);
        renderer.draw({85, 12 + i++}, "[%d%c]", inPercentage(favcat.second, mMonthPnL), '%');
    }
}

stf::smv::IView *MenuView::keyEventsHandler(const int key)
{
    switch (key) {
    case '1': return new DepositListView(static_cast<AppModel*>(m_model));
    case '2': return new OperationsListView(static_cast<AppModel*>(m_model));
    case '3': return new CategoryListView(static_cast<AppModel*>(m_model));
    case '4': return new DebtListView(static_cast<AppModel*>(m_model));
    case 'q': return new CloseView(static_cast<AppModel*>(m_model));
    case 'r': updateStats(); break;
    }
    return this;
}

void MenuView::updateStats()
{
    AppModel &model = *static_cast<AppModel*>(m_model);

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
