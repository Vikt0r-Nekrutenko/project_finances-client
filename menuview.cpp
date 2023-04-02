#include "menuview.hpp"
#include "appmodel.hpp"
#include "closeview.hpp"
#include "debtlistview.hpp"
#include "depositlistview.hpp"
#include "operationslistview.hpp"
#include "categorylistview.hpp"

MenuView::MenuView(AppModel *model)
    : stf::smv::IView(model) {}

void MenuView::show(stf::Renderer &renderer)
{
    renderer.drawText({0, 2}, "1.Deposits.");
    renderer.drawText({0, 3}, "2.Operations.");
    renderer.drawText({0, 4}, "3.Categories.");
    renderer.drawText({0, 5}, "4.Debts.");
    renderer.drawText({0, 6}, "5.Press 'q' to exit.");
}

stf::smv::IView *MenuView::keyEventsHandler(const int key)
{
    switch (key) {
    case '1': return new DepositListView(static_cast<AppModel*>(m_model));
    case '2': return new OperationsListView(static_cast<AppModel*>(m_model));
    case '3': return new CategoryListView(static_cast<AppModel*>(m_model));
    case '4': return new DebtListView(static_cast<AppModel*>(m_model));
    case 'q': return new CloseView(static_cast<AppModel*>(m_model));
    }
    return this;
}
