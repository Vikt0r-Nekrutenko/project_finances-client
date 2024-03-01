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
                                             new options::deposits_view::DeleteDeposit,
                                            });
    mActiveMenuBar->recalculateBarWidth();
}

void DepositsView::show(stf::Renderer &renderer)
{
    IView::show(renderer);
    mMenuBar->show(renderer);
    drawLogItem(renderer, mMenuBar->Width);

    int index = 1;
    for(const auto &deposit : mModel->Deposits.query) {
        renderer.drawLine({mMenuBar->Width +  1, 1 + index}, {renderer.Size.x - 1, 1 + index}, '.');
        renderer.draw({mMenuBar->Width +  1, 1 + index}, "%d.%s", index, deposit->name().c_str());
        renderer.draw({mMenuBar->Width + 15, 1 + index}, "%m.00 %s", int(deposit->balance() / mModel->currentCurrency().second), mModel->currentCurrency().first.c_str());
        ++index;
    }
}

IView *DepositsView::keyHandler(int key)
{
    if(key == VK_ESCAPE1){
        mModel->updateStats();
        return mParent;
    } else if (key == 'q') {
        return new CloseView(mModel);
    }
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
    std::string name;
    int balance = 0;

    try {
        name = mInputField.getStr();
        balance = mInputField.getExpressionResult();
    } catch(...) {
        return this;
    }

    if(mModel->Deposits.query.findByName(name) != mModel->Deposits.query.end()) {
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
    int id = 0, balance = 0;

    try {
        id = mInputField.getExpressionResult();
        balance = mInputField.getExpressionResult();
    } catch(const std::invalid_argument &) {
        return this;
    }

    --id;

    if(id < 0 || id >= int(mModel->Deposits.query.size())) {
        mLogItem << "WARNING! Entered id [" << id + 1 << "] is wrong!" << lendl;
        mInputField.restoreText();
        return this;
    }
    mModel->Deposits.updateBalance(id, balance);
    return mParent;
}

DeleteDepositView::DeleteDepositView(AppModel *model, IView *parent)
    : IDepositView{model, parent, "WARNING! You gonna delete deposit! Enter 'Id' or press ESC to back up"} { }

IView *DeleteDepositView::onEnterPressHandler()
{
    int id = 0;
    try {
        id = mInputField.getExpressionResult();
    } catch(const std::invalid_argument &) {
        return this;
    }

    --id;

    if(id < 0 || id >= int(mModel->Deposits.query.size())) {
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
    int id = 0;
    try {
        id = mInputField.getExpressionResult();
    } catch(const std::invalid_argument &) {
        return this;
    }

    --id;

    if(id < 0 || id >= int(mModel->Deposits.query.size())) {
        mLogItem << "WARNING! Entered id [" << id + 1 << "] is wrong!" << lendl;
        mInputField.restoreText();
        return this;
    }

    mModel->Deposits.selectDeposit(id);
    return new OperationsView(mModel, mParent);
}

MakeTransfer::MakeTransfer(AppModel *model, IView *parent)
    : IDepositView{model, parent, "Enter 'From ID to ID amount' or press ESC to back up"} { }

IView *MakeTransfer::onEnterPressHandler()
{
    int fromId = 0,
        toId = 0,
        amount = 0;

    try {
        fromId = mInputField.getExpressionResult();
        toId = mInputField.getExpressionResult();
        amount = mInputField.getExpressionResult();
    } catch(const std::invalid_argument &ex) {
        return this;
    }

    --fromId;
    --toId;

    if(fromId < 0 || toId < 0 || fromId >= int(mModel->Deposits.query.size()) || toId >= int(mModel->Deposits.query.size())) {
        mLogItem << "WARNING! Entered id/s is wrong!" << lendl;
        mInputField.restoreText();
        return this;
    }

    mModel->makeTransfer(fromId, toId, amount);
    return mParent;
}
