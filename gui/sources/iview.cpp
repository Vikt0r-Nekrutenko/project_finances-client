#include "iview.hpp"
#include "ioption.hpp"
#include "headers/datamodel.hpp"

IView::IView(AppModel *model, ViewHolder *holder)
    : mModel{model}, mHolder{holder} { }

IViewWithMenuItem::~IViewWithMenuItem()
{
    delete mActiveMenuBar;
    delete mInactiveMenuBar;

    for(size_t i = 0; i < mOptionsList.size(); ++i) {
        delete mOptionsList.at(i);
    }
}

bool IView::isContinue() const
{
    return true;
}

void IViewWithMenuItem::switchMenuBar(int key)
{
    if(key == 'm') {
        if(mMenuBar->isActive())
            mMenuBar = mInactiveMenuBar;
        else
            mMenuBar = mActiveMenuBar;
    }
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

void IViewWithLogItem::drawLogItem(stf::Renderer &renderer, int menuWidth)
{
    renderer.drawLine({menuWidth + 1, renderer.Size.y - LogHeight - 1},
                      {renderer.Size.x - 1, renderer.Size.y - LogHeight - 1}, '-');

    for(int i = int(log().size()) - LogHeight, j = LogHeight; i < int(log().size()); ++i, --j) {
        if(i < 0)
            continue;
        renderer.draw({menuWidth + 1, renderer.Size.y - j}, "%d.%s", i, log().at(i).c_str());
    }
}

void IViewWithInputField::drawInputField(stf::Renderer &renderer, int menuWidth)
{
    renderer.drawLine({menuWidth + 1, renderer.Size.y - 7}, {renderer.Size.x - 1, renderer.Size.y - 7}, '-');
    mInputField->show(renderer, menuWidth + 1, renderer.Size.y - 6);
}
