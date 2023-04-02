#include "menuview.hpp"
#include "appmodel.hpp"
#include "closeview.hpp"

MenuView::MenuView(AppModel *model)
    : stf::smv::IView(model)
{

}

void MenuView::show(stf::Renderer &renderer)
{
    renderer.drawText({0, 1}, "Press 'q' to exit.");
}

stf::smv::IView *MenuView::keyEventsHandler(const int key)
{
    switch (key) {
    case 'q': return new CloseView(static_cast<AppModel*>(m_model));
    }
    return this;
}
