#include "depositsview.hpp"
#include "viewholder.hpp"

DepositsView::DepositsView(AppModel *model, ViewHolder *holder)
    : IView{model, holder} { }

void DepositsView::show(stf::Renderer &renderer)
{
    IView::show(renderer);
    renderer.draw({5, 1}, "Deposit View");
    mMenuBar->show(renderer);
    drawLogItem(renderer, mMenuBar->Width);
}

IView *DepositsView::keyHandler(int key)
{
    switchMenuBar(key);
    return mMenuBar->keyHandler(this, key);
}

IView *AddNewDepositView::keyHandler(int key)
{
    mInputField.keyHandler(this, key);
    if(key == VK_ENTER1 || key == VK_ENTER2 || key == VK_ESCAPE1) {
        return mHolder->getDepositView();
    }
    return this;
}
