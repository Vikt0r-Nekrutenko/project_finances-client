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
    auto drawInRG = [&](int x, int y, int value, char sym = ' ', const char *addstr = ""){
        if(sym == ' ')
            renderer.draw({x, y}, value > 0 ? "%s%CG%m.00%CD UAH" : "%s%CR%m.00%CD UAH", addstr, value);
        else
            renderer.draw({x, y}, value > 0 ? "%s%CG%d%c%CD" : "%s%CR%d%c%CD", addstr, value, '%');
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
    drawInRG(BeginListX + 19,  3, m->sumOfAllDeposits());
    drawInRG(BeginListX + 40,  3, inPercentage(m->getSumOfAllDeposits(), m->sumOfAllEarnOperations()), '%');
    drawInRG(BeginListX + 19,  4, m->totalPnL());
    drawInRG(BeginListX + 40,  4, inPercentage(m->totalPnL(), m->sumOfAllEarnOperations()), '%');

    renderer.drawSprite(mPnLStatsTable, false, {BeginListX, 6});

    drawInRG(BeginListX + 16,  7, m->todayPnL());
    drawInRG(BeginListX + 37,  7, inPercentage(m->todayPnL(), m->sumOfAllEarnOperations()), '%');

    drawInRG(BeginListX + 16,  8, m->weekPnL());
    drawInRG(BeginListX + 37,  8, inPercentage(m->weekPnL(), m->sumOfAllEarnOperations()), '%');

    drawInRG(BeginListX + 16,  9, m->monthPnL());
    drawInRG(BeginListX + 37,  9, inPercentage(m->monthPnL(), m->sumOfAllEarnOperations()), '%');

    drawInRG(BeginListX + 16, 10, m->yearPnL());
    drawInRG(BeginListX + 37, 10, inPercentage(m->yearPnL(), m->sumOfAllEarnOperations()), '%');

    renderer.draw({BeginListX, 12}, "Favorite categories:");
    int i = 1;
    renderer.draw({BeginListX, 12 + i++}, "____Name_____|_________PnL________|__%c of total PnL by 30 days__________", '%');
    for(const auto &favcat : m->sumByFavCategories()) {
        for(int j = BeginListX; j < renderer.Size.x; ++j)
            renderer.drawPixel({j, 12 + i}, '.');
        renderer.draw({BeginListX, 12 + i}, "%s", favcat.first.c_str());
        drawInRG(BeginListX + 13, 12 + i, favcat.second, ' ', "|..");
        drawInRG(BeginListX + 34, 12 + i++, inPercentage(favcat.second, m->monthPnL()), '%', "|..");
    }

    const auto minLoss = m->minMaxLosses().first;
    const auto maxLoss = m->minMaxLosses().second;
    renderer.draw({BeginListX, 13 + i}, "_______Name________|_______Amount_______", '%');
    renderer.draw({BeginListX, 14 + i}, "Max loss: %s", maxLoss.second.c_str());
    drawInRG(BeginListX + 19, 14 + i, maxLoss.first, ' ', "|..");
    renderer.draw({BeginListX, 15 + i}, "Min loss: %s", minLoss.second.c_str());
    drawInRG(BeginListX + 19, 15 + i, minLoss.first, ' ', "|..");

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
