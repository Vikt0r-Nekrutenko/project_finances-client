#include "menuview.hpp"
#include "appmodel.hpp"
#include "closeview.hpp"

MenuView::MenuView(AppModel *model)
    : stf::smv::IView(model)
{

}

void MenuView::show(stf::Renderer &renderer)
{
    AppModel *app = static_cast<AppModel*>(m_model);
    renderer.draw({0,1}, "Total balance: %d", app->getTotalBalanceOnDeposits());
    renderer.drawText({0, 2}, "Press 'q' to exit.");
}

stf::smv::IView *MenuView::keyEventsHandler(const int key)
{
    switch (key) {
    case 'q': return new CloseView(static_cast<AppModel*>(m_model));
    }
    return this;
}
