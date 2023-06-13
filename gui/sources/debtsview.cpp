#include "debtsview.hpp"


DebtsView::DebtsView(AppModel *model, ViewHolder *holder)
    : IView{model, holder}
{
    mOptionsList.insert(mOptionsList.end(), {
                                            });
    mActiveMenuBar->recalculateBarWidth();
}

void DebtsView::show(stf::Renderer &renderer)
{
    IView::show(renderer);
    mMenuBar->show(renderer);
    drawLogItem(renderer, mMenuBar->Width);

    int index = 1;
}

IView *DebtsView::keyHandler(int key)
{
    switchMenuBar(key);
    return mMenuBar->keyHandler(this, key);
}
