#include "debtsview.hpp"
#include "appmodel.hpp"
#include "ioption.hpp"
#include "viewholder.hpp"


DebtsView::DebtsView(AppModel *model, ViewHolder *holder)
    : IView{model, holder}
{
    mOptionsList.insert(mOptionsList.end(), {
                                             new options::debts_view::AddNewDebt,
                                             new options::debts_view::ChangeAmount,
                                             new options::debts_view::DeleteDebt,
                                             new options::BackToStartView,
                                             new options::main_view::Exit
                                            });
    mActiveMenuBar->recalculateBarWidth();
}

void DebtsView::show(stf::Renderer &renderer)
{
    IView::show(renderer);
    mMenuBar->show(renderer);
    drawLogItem(renderer, mMenuBar->Width);

    int index = 1;
    for(const auto &debt : mModel->Debts.debts()) {
        renderer.drawLine({mMenuBar->Width +  1, 1 + index}, {renderer.Size.x - 1, 1 + index}, '.');
        renderer.draw({mMenuBar->Width +  1, 1 + index}, "%d.%s", index, debt.name().c_str());
        renderer.draw({mMenuBar->Width + 15, 1 + index}, "%m.00 UAH", debt.amount());
        ++index;
    }
}

IView *DebtsView::keyHandler(int key)
{
    switchMenuBar(key);
    return mMenuBar->keyHandler(this, key);
}

using namespace input_views::debts_views;

IDebtView::IDebtView(AppModel *model, ViewHolder *holder, const std::string &inputTitle)
    : DebtsView{model, holder}, mInputTitle{inputTitle} { }

void IDebtView::show(stf::Renderer &renderer)
{
    DebtsView::show(renderer);
    drawInputField(renderer, mMenuBar->Width, mInputTitle);
}

IView *IDebtView::keyHandler(int key)
{
    return onKeyPressHandler(key, this, mHolder->getDebtsView());
}

AddNewDebtView::AddNewDebtView(AppModel *model, ViewHolder *holder)
    : IDebtView{model, holder, "Enter 'Name Amount' or press ESC to back up"} { }

IView *AddNewDebtView::onEnterPressHandler()
{
    std::string name = mInputField.getStr();
    int amount = mInputField.getExpressionResult();

    if(mModel->Debts.findByName(name) != mModel->Debts.debts().end()) {
        mLogItem << "WARNING! Entered name [" << name << "] is exist!" << lendl;
        mInputField.restoreText();
        return this;
    }

    mModel->Debts.addNewDebt(name, amount);
    return mHolder->getDebtsView();
}

ChangeAmountView::ChangeAmountView(AppModel *model, ViewHolder *holder)
    : IDebtView{model, holder, "Enter 'Id New amount' or press ESC to back up"} { }

IView *ChangeAmountView::onEnterPressHandler()
{
    int id = mInputField.getExpressionResult();
    int amount = mInputField.getExpressionResult();

    --id;

    if(id < 0 || id >= int(mModel->Debts.debts().size())) {
        mLogItem << "WARNING! Entered id [" << id + 1 << "] is wrong!" << lendl;
        mInputField.restoreText();
        return this;
    }
    mModel->Debts.updateDebt(id, mModel->Debts.debts().at(id).name(), amount);
    return mHolder->getDebtsView();
}

DeleteDebtView::DeleteDebtView(AppModel *model, ViewHolder *holder)
    : IDebtView{model, holder, "Enter 'Id' or press ESC to back up"} { }

IView *DeleteDebtView::onEnterPressHandler()
{
    int id = mInputField.getExpressionResult();

    --id;

    if(id < 0 || id >= int(mModel->Debts.debts().size())) {
        mLogItem << "WARNING! Entered id [" << id + 1 << "] is wrong!" << lendl;
        mInputField.restoreText();
        return this;
    }

    mModel->Debts.deleteDebt(id);
    return mHolder->getDebtsView();
}
