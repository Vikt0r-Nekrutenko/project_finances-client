#include "iview.hpp"


IView::IView(AppModel *model, ViewHolder *holder)
    : mModel{model}, mHolder{holder} { }

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

void IView::keyHandler(int key)
{
    MenuBar->keyHandler(key);

    if(key != 'm')
        return;

    if(MenuBar->isActive()) {
        MenuBar = mInactiveMenuBar;
    } else {
        MenuBar = mActiveMenuBar;
    }
}

ViewHolder *IView::holder() const
{
    return mHolder;
}
