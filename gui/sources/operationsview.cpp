#include "operationsview.hpp"
#include "appmodel.hpp"
#include "ioption.hpp"


OperationsView::OperationsView(AppModel *model, IView *parent)
    : IView{model}, ISubView{parent}
{
    mOptionsList.insert(mOptionsList.end(), {
                                             new options::operations_view::AddNewOperation,
                                             new options::operations_view::AddNewTodayOperation,
                                             new options::operations_view::AddNewTodayLendOrRepay,
                                             new options::operations_view::AddNewLendOrRepay,
                                             new options::operations_view::DeleteOperation,
                                             new options::operations_view::SelectOperations,
                                             new options::operations_view::ChangeOperation,
                                            });
    mActiveMenuBar->recalculateBarWidth();
    mModel->selectOperationsList();
}

void OperationsView::show(stf::Renderer &renderer)
{
    IView::show(renderer);
    mMenuBar->show(renderer);
    drawLogItem(renderer, mMenuBar->Width);

    int y = 2, id = 0;
    for(auto operation = mModel->Operations.query.rbegin(); operation != mModel->Operations.query.rend(); ++operation) {
        if(y == renderer.Size.y - LogHeight - 1)
            break;
        renderer.drawLine({mMenuBar->Width +  1, y}, {renderer.Size.x - 1, y}, '.');
        renderer.draw({mMenuBar->Width +  1, y}, "%d.%s..%m.00 UAH", ++id, (*operation)->date().c_str(), (*operation)->amount());
        renderer.draw({mMenuBar->Width + 33, y}, "%s", (*operation)->category().c_str());
        ++y;
    }
    renderer.draw({mMenuBar->Width + 1, 1}, "%s[%m.00UAH]", mModel->Deposits.selectedDeposit()->name().c_str(), mModel->Deposits.selectedDeposit()->balance());
}

IView *OperationsView::keyHandler(int key)
{
    if(key == VK_ESCAPE1)
        return mParent;
    if (key == 'q') {
        return new CloseView(mModel);
    }
    switchMenuBar(key);
    return mMenuBar->keyHandler(this, key);
}

using namespace input_views::operations_views;

IOperationView::IOperationView(AppModel *model, IView *parent, const std::string &inputTitle)
    : OperationsView{model, parent}, mInputTitle{inputTitle} { }

void IOperationView::show(stf::Renderer &renderer)
{
    OperationsView::show(renderer);
    renderer.drawLine({mMenuBar->Width + 1, renderer.Size.y - LogHeight - 2}, {renderer.Size.x, renderer.Size.y - LogHeight - 2}, ' ');
    drawInputField(renderer, mMenuBar->Width, mInputTitle);
}

IView *IOperationView::keyHandler(int key)
{
    return onKeyPressHandler(key, this, mParent);
}

AddNewOperationView::AddNewOperationView(AppModel *model, IView *parent)
    : IOperationView{model, parent, "Enter 'Date Amount Category' or press ESC to back up"} { }

IView *AddNewOperationView::onEnterPressHandler()
{
    std::string date = mInputField.getStr();
    int amount = mInputField.getExpressionResult();
    std::string category = mInputField.getStr();

    if(mModel->Categories.query.findByName(category) == mModel->Categories.query.end()) {
        mLogItem << "WARNING! Entered name [" << category << "] isn't exist!" << lendl;
        mInputField.restoreText();
        return this;
    }

    mModel->addNewOperation(date, amount, category);
    mLogItem << "Deposit [" << mModel->Deposits.selectedDeposit()->name() << "] balance now: " << mModel->Deposits.selectedDeposit()->balance() << ".00 UAH" << lendl;
    return mParent;
}

AddNewTodayLendOrRepayView::AddNewTodayLendOrRepayView(AppModel *model, IView *parent)
    : IOperationView{model, parent, "Enter 'Amount Name Type[l/r]' or press ESC to back up"} { }

IView *AddNewTodayLendOrRepayView::onEnterPressHandler()
{
    std::string date = QDateTime().currentDateTime().toString("yyyy-MM-dd").toStdString();
    int amount = mInputField.getExpressionResult();
    std::string name = mInputField.getStr();
    std::string type = mInputField.getStr();

    if(type == "l") {
        mModel->addNewOperation(date, amount, "Lend");
        mModel->addOrChangeDebt(name, amount, "Lend");
    } else if(type == "r") {
        mModel->addNewOperation(date, amount, "Repay");
        mModel->addOrChangeDebt(name, amount, "Repay");
    } else {
        mLogItem << "WARNING! Entered type [" << type << "] doesn't exist!" << lendl;
        mInputField.restoreText();
        return this;
    }


    mLogItem << "Deposit [" << mModel->Deposits.selectedDeposit()->name() << "] balance now: " << mModel->Deposits.selectedDeposit()->balance() << ".00 UAH" << lendl;
    mLogItem << "Debt [" << name << "] amount now: " << (*mModel->Debts.query.findByName(name))->amount() << ".00 UAH" << lendl;
    return mParent;
}

AddNewLendOrRepayView::AddNewLendOrRepayView(AppModel *model, IView *parent)
    : IOperationView{model, parent, "Enter 'Date Amount Name Type[l/r]' or press ESC to back up"} { }

IView *AddNewLendOrRepayView::onEnterPressHandler()
{
    std::string date = mInputField.getStr();
    int amount = mInputField.getExpressionResult();
    std::string name = mInputField.getStr();
    std::string type = mInputField.getStr();

    if(type == "l") {
        mModel->addNewOperation(date, amount, "Lend");
        mModel->addOrChangeDebt(name, amount, "Lend");
    } else if(type == "r") {
        mModel->addNewOperation(date, amount, "Repay");
        mModel->addOrChangeDebt(name, amount, "Repay");
    } else {
        mLogItem << "WARNING! Entered type [" << type << "] doesn't exist!" << lendl;
        mInputField.restoreText();
        return this;
    }


    mLogItem << "Deposit [" << mModel->Deposits.selectedDeposit()->name() << "] balance now: " << mModel->Deposits.selectedDeposit()->balance() << ".00 UAH" << lendl;
    mLogItem << "Debt [" << name << "] amount now: " << (*mModel->Debts.query.findByName(name))->amount() << ".00 UAH" << lendl;
    return mParent;
}

AddNewTodayOperationView::AddNewTodayOperationView(AppModel *model, IView *parent)
    : IOperationView{model, parent, "Enter 'Amount Category' or press ESC to back up"} { }

IView *AddNewTodayOperationView::onEnterPressHandler()
{
    std::string date = QDateTime().currentDateTime().toString("yyyy-MM-dd").toStdString();
    int amount = mInputField.getExpressionResult();
    std::string category = mInputField.getStr();

    if(mModel->Categories.query.findByName(category) == mModel->Categories.query.end()) {
        mLogItem << "WARNING! Entered name [" << category << "] isn't exist!" << lendl;
        mInputField.restoreText();
        return this;
    }

    mModel->addNewOperation(date, amount, category);
    mLogItem << "Deposit [" << mModel->Deposits.selectedDeposit()->name() << "] balance now: " << mModel->Deposits.selectedDeposit()->balance() << ".00 UAH" << lendl;
    return mParent;
}

DeleteOperationView::DeleteOperationView(AppModel *model, IView *parent)
    : IOperationView{model, parent, "Enter 'Id' or press ESC to back up"} { }

IView *DeleteOperationView::onEnterPressHandler()
{
    int id = mInputField.getExpressionResult();

    --id;

    if(id < 1 || id > int(mModel->Operations.query.size())) {
        mLogItem << "WARNING! Entered id [" << id + 1 << "] is wrong!" << lendl;
        mInputField.restoreText();
        return this;
    }

    mModel->deleteOperation(id);
    mLogItem << "Deposit [" << mModel->Deposits.selectedDeposit()->name() << "] balance now: " << mModel->Deposits.selectedDeposit()->balance() << ".00 UAH" << lendl;
    return mParent;
}

SelectOperationsView::SelectOperationsView(AppModel *model, IView *parent)
    : IOperationView{model, parent, "Enter 'Year Month' or press ESC to back up"} { }

IView *SelectOperationsView::onEnterPressHandler()
{
    int year = mInputField.getExpressionResult();
    int month = mInputField.getExpressionResult();

    if(year < 0 || month < 0) {
        mLogItem << "WARNING! Entered date is wrong!" << lendl;
        mInputField.restoreText();
        return this;
    }

    mModel->SelectedYear = year;
    mModel->SelectedMonth = month;
    mModel->selectOperationsList();
    return mParent;
}

ChangeOperationView::ChangeOperationView(AppModel *model, IView *parent)
    : IOperationView{model, parent, "Enter 'Id' or press ESC to back up"} { }

IView *ChangeOperationView::onEnterPressHandler()
{
    int id = mInputField.getExpressionResult();

    --id;

    if(id < 1 || id > int(mModel->Operations.query.size())) {
        mLogItem << "WARNING! Entered id [" << id + 1 << "] is wrong!" << lendl;
        mInputField.restoreText();
        return this;
    }

    mModel->Operations.selectOperation(id);
    return new OperationView(mModel, mParent);
}

OperationView::OperationView(AppModel *model, IView *parent)
    : IView{model}, ISubView{parent}
{
    mOptionsList.insert(mOptionsList.end(), {
                                                new options::operations_view::ChangeDate,
                                                new options::operations_view::ChangeAmount,
                                                new options::operations_view::ChangeCategory,
                                            });
    mActiveMenuBar->recalculateBarWidth();
}

void OperationView::show(stf::Renderer &renderer)
{
    IView::show(renderer);
    mMenuBar->show(renderer);
    drawLogItem(renderer, mMenuBar->Width);

    auto operation = mModel->selectedOperation();
    renderer.drawLine({mMenuBar->Width +  1, 2}, {renderer.Size.x - 1, 2}, '.');
    renderer.draw({mMenuBar->Width +  1, 2}, "%s..%m.00 UAH", operation.date().c_str(), operation.amount());
    renderer.draw({mMenuBar->Width + 33, 2}, "%s", operation.category().c_str());
}

IView *OperationView::keyHandler(int key)
{
    if(key == VK_ESCAPE1)
        return mParent;
    if (key == 'q') {
        return new CloseView(mModel);
    }
    switchMenuBar(key);
    return mMenuBar->keyHandler(this, key);
}

using namespace input_views::change_operation_views;

IChangeOperationView::IChangeOperationView(AppModel *model, IView *parent, const std::string &inputTitle)
    : OperationView{model, parent}, mInputTitle{inputTitle} { }

void IChangeOperationView::show(stf::Renderer &renderer)
{
    OperationView::show(renderer);
    renderer.drawLine({mMenuBar->Width + 1, renderer.Size.y - LogHeight - 2}, {renderer.Size.x, renderer.Size.y - LogHeight - 2}, ' ');
    drawInputField(renderer, mMenuBar->Width, mInputTitle);
}

IView *IChangeOperationView::keyHandler(int key)
{
    return onKeyPressHandler(key, this, mParent);
}

ChangeDate::ChangeDate(AppModel *model, IView *parent)
    : IChangeOperationView{model, parent, "Enter 'date' or press ESC to back up"} { }

IView *ChangeDate::onEnterPressHandler()
{
    std::string date = mInputField.getStr();

    mModel->Operations.changeDate(date);
    return mParent;
}

ChangeAmount::ChangeAmount(AppModel *model, IView *parent)
    : IChangeOperationView{model, parent, "Enter 'amount' or press ESC to back up"} { }

IView *ChangeAmount::onEnterPressHandler()
{
    int amount = mInputField.getExpressionResult();

    mModel->selectedOperationChangeAmount(amount);
    mLogItem << "Deposit [" << mModel->Deposits.selectedDeposit()->name() << "] balance now: " << mModel->Deposits.selectedDeposit()->balance() << ".00 UAH" << lendl;
    return mParent;
}

ChangeCategory::ChangeCategory(AppModel *model, IView *parent)
    : IChangeOperationView{model, parent, "Enter 'category' or press ESC to back up"} { }

IView *ChangeCategory::onEnterPressHandler()
{
    std::string category = mInputField.getStr();

    if(mModel->Categories.query.findByName(category) == mModel->Categories.query.end()) {
        mLogItem << "WARNING! Entered category [" << category << "] doesn't exist!" << lendl;
        mInputField.restoreText();
        return this;
    }

    mModel->selectedOperationChangeCategory(category);
    mLogItem << "Deposit [" << mModel->Deposits.selectedDeposit()->name() << "] balance now: " << mModel->Deposits.selectedDeposit()->balance() << ".00 UAH" << lendl;
    return mParent;
}

