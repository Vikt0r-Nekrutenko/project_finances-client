#include "iview.hpp"
#include "ioption.hpp"

IView::IView(AppModel *model, ViewHolder *holder)
    : mModel{model}, mHolder{holder} { }

IView::~IView()
{
    for(size_t i = 0; i < mOptionsList.size(); ++i) {
        delete mOptionsList.at(i);
    }
}

void IView::show(stf::Renderer &renderer) const
{
    mMenuBar->show(renderer);
}

bool IView::isContinue() const
{
    return true;
}

IView *IView::keyHandler(int key)
{
    if(key == 'm') {
        if(mMenuBar->isActive())
            mMenuBar = mInactiveMenuBar;
        else
            mMenuBar = mActiveMenuBar;
    }

    return mMenuBar->keyHandler(this, key);
}

ViewHolder *IView::holder() const
{
    return mHolder;
}
