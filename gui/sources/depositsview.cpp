#include "depositsview.hpp"
#include "ioption.hpp"
#include "viewholder.hpp"
#include "appmodel.hpp"

DepositsView::DepositsView(AppModel *model, ViewHolder *holder)
    : IView{model, holder}
{
    mOptionsList.insert(mOptionsList.end(), {
                                             new options::deposits_view::AddNewDeposit,
                                             new options::BackToStartView,
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

using namespace input_views::deposits_views;

AddNewDepositView::AddNewDepositView(AppModel *model, ViewHolder *holder)
    : DepositsView{model, holder} { }

void AddNewDepositView::show(stf::Renderer &renderer)
{
    DepositsView::show(renderer);
    drawInputField(renderer, mMenuBar->Width, "Enter 'Name Balance' or press ESC to back up");
}

IView *AddNewDepositView::keyHandler(int key)
{
    return onKeyPressHandler(key, this, mHolder->getDepositView());
}

IView *AddNewDepositView::onEnterPressHandler()
{
    std::string name = mInputField.getStr();
    int balance = mInputField.getExpressionResult();

    if(mModel->Deposits.findByName(name) != mModel->Deposits.deposits().end()) {
        mLogItem << "WARNING! Entered name [" << name << "] is exist!" << lendl;
        mInputField.restoreText();
        return this;
    }
    return mHolder->getDepositView();
}
