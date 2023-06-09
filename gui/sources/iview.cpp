#include "iview.hpp"
#include "ioption.hpp"

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

IView *IView::keyHandler(int key)
{
    if(key == 'm') {
        if(MenuBar->isActive())
            MenuBar = mInactiveMenuBar;
        else
            MenuBar = mActiveMenuBar;
    }

    return MenuBar->keyHandler(this, key);
}

ViewHolder *IView::holder() const
{
    return mHolder;
}
