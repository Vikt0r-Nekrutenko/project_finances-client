#include "iview.hpp"


IView::~IView()
{
    for(size_t i = 0; i < mMenuBar.size(); ++i) {
        delete mMenuBar.at(i);
    }
}

void IView::show(stf::Renderer &renderer) const
{
    MenuBar->show(renderer);
}
