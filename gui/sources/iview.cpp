#include "iview.hpp"
#include "ioption.hpp"
#include "headers/datamodel.hpp"

IView::IView(AppModel *model, ViewHolder *holder)
    : mModel{model}, mHolder{holder} { }

IView::~IView()
{
    delete mActiveMenuBar;
    delete mInactiveMenuBar;

    for(size_t i = 0; i < mOptionsList.size(); ++i) {
        delete mOptionsList.at(i);
    }
}

void IView::show(stf::Renderer &renderer)
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

CloseView::CloseView(AppModel *model, ViewHolder *holder)
    : IView(model, holder) { }

bool CloseView::isContinue() const
{
    return false;
}

ViewWithLogItem::ViewWithLogItem(AppModel *model, ViewHolder *holder)
    : IView{model, holder} { }

void ViewWithLogItem::show(stf::Renderer &renderer)
{
    renderer.drawLine({mMenuBar->Width + 1, renderer.Size.y - LogHeight - 1},
                      {renderer.Size.x - 1, renderer.Size.y - LogHeight - 1}, '-');

    for(int i = int(log().size()) - LogHeight, j = LogHeight; i < int(log().size()); ++i, --j) {
        if(i < 0)
            continue;
        renderer.draw({mMenuBar->Width + 1, renderer.Size.y - j}, "%d.%s", i, log().at(i).c_str());
    }

    IView::show(renderer);
}
