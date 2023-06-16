#include "depositsview.hpp"
#include "ioption.hpp"
#include "appmodel.hpp"
#include "operationsview.hpp"

DepositsView::DepositsView(AppModel *model, IView *parent)
    : IView{model}, ISubView{parent}
{
    mOptionsList.insert(mOptionsList.end(), {
                                             new options::deposits_view::AddNewDeposit,
                                             new options::deposits_view::ChangeBalance,
                                             new options::deposits_view::SelectDeposit,
//                                             new options::deposits_view::DeleteDeposit,
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

IDepositView::IDepositView(AppModel *model, IView *parent, const std::string &inputTitle)
    : DepositsView{model, parent}, mInputTitle{inputTitle} { }

void IDepositView::show(stf::Renderer &renderer)
{
    DepositsView::show(renderer);
    drawInputField(renderer, mMenuBar->Width, mInputTitle);
}

IView *IDepositView::keyHandler(int key)
{
    return onKeyPressHandler(key, this, mParent);
}

AddNewDepositView::AddNewDepositView(AppModel *model, IView *parent)
    : IDepositView{model, parent, "Enter 'Name Balance' or press ESC to back up"} { }

IView *AddNewDepositView::onEnterPressHandler()
{
    std::string name = mInputField.getStr();
    int balance = mInputField.getExpressionResult();

    if(mModel->Deposits.findByName(name) != mModel->Deposits.deposits().end()) {
        mLogItem << "WARNING! Entered name [" << name << "] is exist!" << lendl;
        mInputField.restoreText();
        return this;
    }

    mModel->Deposits.addNewDeposit(name, balance);
    return mParent;
}

ChangeBalanceView::ChangeBalanceView(AppModel *model, IView *parent)
    : IDepositView{model, parent, "Enter 'Id New balance' or press ESC to back up"} { }

IView *ChangeBalanceView::onEnterPressHandler()
{
    int id = mInputField.getExpressionResult();
    int balance = mInputField.getExpressionResult();

    --id;

    if(id < 0 || id >= int(mModel->Deposits.deposits().size())) {
        mLogItem << "WARNING! Entered id [" << id + 1 << "] is wrong!" << lendl;
        mInputField.restoreText();
        return this;
    }
    mModel->Deposits.updateBalance(id, balance);
    return mParent;
}

DeleteDepositView::DeleteDepositView(AppModel *model, IView *parent)
    : IDepositView{model, parent, "Enter 'Id' or press ESC to back up"} { }

IView *DeleteDepositView::onEnterPressHandler()
{
    int id = mInputField.getExpressionResult();

    --id;

    if(id < 0 || id >= int(mModel->Deposits.deposits().size())) {
        mLogItem << "WARNING! Entered id [" << id + 1 << "] is wrong!" << lendl;
        mInputField.restoreText();
        return this;
    }

    mModel->Deposits.deleteDeposit(id);
    return mParent;
}

SelectDepositView::SelectDepositView(AppModel *model, IView *parent)
    : IDepositView{model, parent, "Enter 'Id' or press ESC to back up"} { }

IView *SelectDepositView::onEnterPressHandler()
{
    int id = mInputField.getExpressionResult();

    --id;

    if(id < 0 || id >= int(mModel->Deposits.deposits().size())) {
        mLogItem << "WARNING! Entered id [" << id + 1 << "] is wrong!" << lendl;
        mInputField.restoreText();
        return this;
    }

    mModel->selectDeposit(id);
    return (new OperationsView(mModel, mParent))->recalculateList();
}
