#include "debtsview.hpp"
#include "appmodel.hpp"
#include "ioption.hpp"


DebtsView::DebtsView(AppModel *model, IView *parent)
    : IView{model}, ISubView{parent}
{
    mOptionsList.insert(mOptionsList.end(), {
                                             new options::debts_view::AddNewDebt,
                                             new options::debts_view::ChangeAmount,
                                             new options::debts_view::DeleteDebt,
                                            });
    mActiveMenuBar->recalculateBarWidth();
}

void DebtsView::show(stf::Renderer &renderer)
{
    IView::show(renderer);
    mMenuBar->show(renderer);
    drawLogItem(renderer, mMenuBar->Width);

    int index = 1;
    for(const auto &debt : mModel->Debts.query) {
        renderer.drawLine({mMenuBar->Width +  1, 1 + index}, {renderer.Size.x - 1, 1 + index}, '.');
        renderer.draw({mMenuBar->Width +  1, 1 + index}, "%d.%s", index, debt->name().c_str());
        renderer.draw({mMenuBar->Width + 15, 1 + index}, "%m.00 UAH", debt->amount());
        ++index;
    }
}

IView *DebtsView::keyHandler(int key)
{
    if(key == VK_ESCAPE1) {
        mModel->updateStats();
        return mParent;
    } else if (key == 'q') {
        return new CloseView(mModel);
    }
    switchMenuBar(key);
    return mMenuBar->keyHandler(this, key);
}

using namespace input_views::debts_views;

IDebtView::IDebtView(AppModel *model, IView *parent, const std::string &inputTitle)
    : DebtsView{model, parent}, mInputTitle{inputTitle} { }

void IDebtView::show(stf::Renderer &renderer)
{
    DebtsView::show(renderer);
    drawInputField(renderer, mMenuBar->Width, mInputTitle);
}

IView *IDebtView::keyHandler(int key)
{
    return onKeyPressHandler(key, this, mParent);
}

AddNewDebtView::AddNewDebtView(AppModel *model, IView *parent)
    : IDebtView{model, parent, "Enter 'Name Amount' or press ESC to back up"} { }

IView *AddNewDebtView::onEnterPressHandler()
{
    std::string name = mInputField.getStr();
    int amount = mInputField.getExpressionResult();

    if(mModel->Debts.query.findByName(name) != mModel->Debts.query.end()) {
        mLogItem << "WARNING! Entered name [" << name << "] is exist!" << lendl;
        mInputField.restoreText();
        return this;
    }

    mModel->Debts.addNewDebt(name, amount);
    return mParent;
}

ChangeAmountView::ChangeAmountView(AppModel *model, IView *parent)
    : IDebtView{model, parent, "Enter 'Id New amount' or press ESC to back up"} { }

IView *ChangeAmountView::onEnterPressHandler()
{
    int id = mInputField.getExpressionResult();
    int amount = mInputField.getExpressionResult();

    --id;

    if(id < 0 || id >= int(mModel->Debts.query.size())) {
        mLogItem << "WARNING! Entered id [" << id + 1 << "] is wrong!" << lendl;
        mInputField.restoreText();
        return this;
    }
    mModel->Debts.updateDebt(id, mModel->Debts.query.at(id)->name(), amount);
    return mParent;
}

DeleteDebtView::DeleteDebtView(AppModel *model, IView *parent)
    : IDebtView{model, parent, "Enter 'Id' or press ESC to back up"} { }

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
    return mParent;
}
