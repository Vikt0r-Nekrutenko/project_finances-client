#include "menuview.hpp"
#include "appmodel.hpp"
#include "closeview.hpp"
#include "debtlistview.hpp"
#include "depositlistview.hpp"
#include "operationslistview.hpp"
#include "categorylistview.hpp"

#define inPercentage(a, b) int(a / (float)b * 100.f)

MenuView::MenuView(AppModel *model)
    : ModelViewWithInputField(model) {}

void MenuView::show(stf::Renderer &renderer)
{
    auto drawInRGMoney = [&](int x, int y, int value){
        renderer.draw({x, y}, value > 0 ? "%CG%m.00%CD UAH" : "%CR%m.00%CD UAH", value);
    };

    auto drawInRGPercetage = [&](int x, int y, int value){
        renderer.draw({x, y}, value > 0 ? "%CG%d%c%CD" : "%CR%d%c%CD", value, '%');
    };

    renderer.drawText({0, 2}, "1.Deposits.");
    renderer.drawText({0, 3}, "2.Operations.");
    renderer.drawText({0, 4}, "3.Categories.");
    renderer.drawText({0, 5}, "4.Debts.");
    renderer.drawText({0, 6}, "r.Update.");
    renderer.drawText({0, 7}, "q.Exit.");

    AppModel *m = static_cast<AppModel*>(m_model);

    for(int i = 2; i < 5; ++i)
        for(int j = BeginListX; j < renderer.Size.x; ++j)
            renderer.drawPixel({j, i}, '.');

    renderer.drawSprite(mMainStatsTable, false, {BeginListX, 2});
    renderer.draw({BeginListX + 19,  2}, "%m.00 UAH", m->sumOfAllEarnOperations());
    drawInRGMoney(BeginListX + 19,  3, m->sumOfAllDeposits());
    drawInRGPercetage(BeginListX + 40,  3, inPercentage(m->getSumOfAllDeposits(), m->sumOfAllEarnOperations()));
    drawInRGMoney(BeginListX + 19,  4, m->totalPnL());
    drawInRGPercetage(BeginListX + 40,  4, inPercentage(m->totalPnL(), m->sumOfAllEarnOperations()));

    renderer.drawSprite(mPnLStatsTable, false, {BeginListX, 6});

    renderer.draw({BeginListX + 15,  7}, "%m.00 UAH", m->todayPnL());
    renderer.draw({BeginListX + 36,  7}, "[%d%c]", inPercentage(m->todayPnL(), m->sumOfAllEarnOperations()), '%');

    renderer.draw({BeginListX + 15,  8}, "%m.00 UAH", m->weekPnL());
    renderer.draw({BeginListX + 36,  8}, "[%d%c]", inPercentage(m->weekPnL(), m->sumOfAllEarnOperations()), '%');

    renderer.draw({BeginListX + 15,  9}, "%m.00 UAH", m->monthPnL());
    renderer.draw({BeginListX + 36,  9}, "[%d%c]", inPercentage(m->monthPnL(), m->sumOfAllEarnOperations()), '%');

    renderer.draw({BeginListX + 15, 10}, "%m.00 UAH", m->yearPnL());
    renderer.draw({BeginListX + 36, 10}, "[%d%c]", inPercentage(m->yearPnL(), m->sumOfAllEarnOperations()), '%');

    renderer.draw({BeginListX, 12}, "Favorite categories:");
    int i = 1;
    renderer.draw({BeginListX, 12 + i++}, "____Name_____|_________PnL________|__%c of total PnL by 30 days__________", '%');
    for(const auto &favcat : m->sumByFavCategories()) {
        for(int j = BeginListX; j < renderer.Size.x; ++j)
            renderer.drawPixel({j, 12 + i}, '.');
        renderer.draw({BeginListX, 12 + i}, "%s", favcat.first.c_str());
        renderer.draw({BeginListX + 13, 12 + i}, "|..%m.00 UAH", favcat.second);
        renderer.draw({BeginListX + 34, 12 + i++}, "|..[%d%c]", inPercentage(favcat.second, m->monthPnL()), '%');
    }
    ModelViewWithInputField::show(renderer);
}

stf::smv::IView *MenuView::keyEventsHandler(const int key)
{
    switch (key) {
    case '1': return new DepositListView(static_cast<AppModel*>(m_model));
    case '2': return new OperationsListView(static_cast<AppModel*>(m_model));
    case '3': return new CategoryListView(static_cast<AppModel*>(m_model));
    case '4': return new DebtListView(static_cast<AppModel*>(m_model));
    case 'q': return new CloseView(static_cast<AppModel*>(m_model));
    case 'r':
        static_cast<AppModel*>(m_model)->updateAllHandlers();
        static_cast<AppModel*>(m_model)->updateStats(); break;
    }
    return this;
}
