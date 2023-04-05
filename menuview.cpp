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
    renderer.drawText({0, 2}, "1.Deposits.");
    renderer.drawText({0, 3}, "2.Operations.");
    renderer.drawText({0, 4}, "3.Categories.");
    renderer.drawText({0, 5}, "4.Debts.");
    renderer.drawText({0, 6}, "q.Exit.");

    AppModel *m = static_cast<AppModel*>(m_model);

    renderer.draw({BeginListX,  2}, "Total earn:.......%m.00 UAH", m->sumOfAllEarnOperations());
    renderer.draw({BeginListX,  3}, "Total deposits:...%m.00 UAH [%d%c]", m->sumOfAllDeposits(), inPercentage(m->getSumOfAllDeposits(), m->sumOfAllEarnOperations()), '%');
    renderer.draw({BeginListX,  4}, "Total P&L:........%m.00 UAH [%d%c]", m->totalPnL(), inPercentage(m->totalPnL(), m->sumOfAllEarnOperations()), '%');

    renderer.draw({BeginListX,  6}, "P&L's:");
    renderer.draw({BeginListX,  7}, "Today PnL:...%m.00 UAH", m->todayPnL());

    renderer.draw({BeginListX + 30,  7}, "[%d%c]", inPercentage(m->todayPnL(), m->sumOfAllEarnOperations()), '%');

    renderer.draw({BeginListX,  8}, "Week PnL:....%m.00 UAH", m->weekPnL());
    renderer.draw({BeginListX + 30,  8}, "[%d%c]", inPercentage(m->weekPnL(), m->sumOfAllEarnOperations()), '%');

    renderer.draw({BeginListX,  9}, "Month PnL:...%m.00 UAH", m->monthPnL());
    renderer.draw({BeginListX + 30,  9}, "[%d%c]", inPercentage(m->monthPnL(), m->sumOfAllEarnOperations()), '%');

    renderer.draw({BeginListX, 10}, "Year PnL:....%m.00 UAH", m->yearPnL());
    renderer.draw({BeginListX + 30, 10}, "[%d%c]", inPercentage(m->yearPnL(), m->sumOfAllEarnOperations()), '%');

    renderer.draw({BeginListX, 12}, "Favorite categories:");
    int i = 1;
    for(const auto &favcat : m->sumByFavCategories()) {
        renderer.draw({BeginListX, 12 + i}, "%s", favcat.first.toStdString().c_str());
        renderer.draw({BeginListX + 10, 12 + i}, "%m.00 UAH", favcat.second);
        renderer.draw({BeginListX + 25, 12 + i++}, "[%d%c]", inPercentage(favcat.second, m->monthPnL()), '%');
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
    case 'r': static_cast<AppModel*>(m_model)->updateStats(); break;
    }
    return this;
}
