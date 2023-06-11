#include "depositsview.hpp"
#include "ioption.hpp"
#include "viewholder.hpp"
#include "appmodel.hpp"

DepositsView::DepositsView(AppModel *model, ViewHolder *holder)
    : IView{model, holder}
{
    mOptionsList.insert(mOptionsList.end(), {
                                                new options::deposits_view::AddNewDeposit,
                                                new options::main_view::Exit
                                            });
    mActiveMenuBar->recalculateBarWidth();
}

void DepositsView::show(stf::Renderer &renderer)
{
    IView::show(renderer);
    mMenuBar->show(renderer);
    drawLogItem(renderer, mMenuBar->Width);

    int index = 1;
    for(const auto &deposit : mModel->Deposits.deposits()) {
        renderer.drawLine({mMenuBar->Width +  1, 1 + index}, {renderer.Size.x - 1, 1 + index}, '.');
        renderer.draw({mMenuBar->Width +  1, 1 + index}, "%d.%s", index, deposit.name().c_str());
        renderer.draw({mMenuBar->Width + 15, 1 + index}, "%m.00 UAH", deposit.balance());
        ++index;
    }
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
