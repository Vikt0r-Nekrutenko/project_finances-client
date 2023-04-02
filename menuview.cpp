#include "menuview.hpp"
#include "appmodel.hpp"
#include "closeview.hpp"
#include "depositlistview.hpp"
#include "operationslistview.hpp"

MenuView::MenuView(AppModel *model)
    : stf::smv::IView(model) {}

void MenuView::show(stf::Renderer &renderer)
{
    renderer.drawText({0, 2}, "1.Deposits.");
    renderer.drawText({0, 3}, "2.Operations.");
    renderer.drawText({0, 4}, "3.Press 'q' to exit.");
}

stf::smv::IView *MenuView::keyEventsHandler(const int key)
{
    switch (key) {
    case '1': return new DepositListView(static_cast<AppModel*>(m_model));
    case '2': return new OperationsListView(static_cast<AppModel*>(m_model));
    case 'q': return new CloseView(static_cast<AppModel*>(m_model));
    }
    return this;
}
