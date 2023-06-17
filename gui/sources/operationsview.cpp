#include "operationsview.hpp"
#include "appmodel.hpp"
#include "ioption.hpp"


OperationsView::OperationsView(AppModel *model, IView *parent)
    : IView{model}, ISubView{parent}, mOperationsList{&model->Operations}
{
    mOptionsList.insert(mOptionsList.end(), {
                                             new options::operations_view::AddNewOperation,
                                             new options::operations_view::DeleteOperation,
                                             new options::operations_view::SelectOperations,
                                             new options::operations_view::ChangeOperation,
                                            });
    mActiveMenuBar->recalculateBarWidth();
    recalculateList();
}

void OperationsView::show(stf::Renderer &renderer)
{
    IView::show(renderer);
    mMenuBar->show(renderer);
    drawLogItem(renderer, mMenuBar->Width);

    int y = 2;
    for(auto operation = mOperationsList.rbegin(); operation != mOperationsList.rend(); ++operation) {
        if(y == renderer.Size.y - LogHeight - 1)
            break;
        renderer.drawLine({mMenuBar->Width +  1, y}, {renderer.Size.x - 1, y}, '.');
        renderer.draw({mMenuBar->Width +  1, y}, "%d.%s..%m.00 UAH", (*operation)->id() + 1, (*operation)->date().c_str(), (*operation)->amount());
        renderer.draw({mMenuBar->Width + 33, y}, "%s", (*operation)->category().c_str());
        ++y;
    }
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

IView *OperationsView::recalculateList()
{

    mOperationsList.select().filterByDeposit(mModel->selectedDeposit()->name());
    if(mModel->SelectedYear == 0 || mModel->SelectedMonth == 0) {
        mOperationsList.filterByCurrentYear().filterByCurrentMonth();
        return this;
    }
    mOperationsList.filterByYear(mModel->SelectedYear).filterByMonth(mModel->SelectedMonth);
    return this;
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

    if(mModel->Categories.findByName(category) == mModel->Categories.categories().end()) {
        mLogItem << "WARNING! Entered name [" << category << "] isn't exist!" << lendl;
        mInputField.restoreText();
        return this;
    }

    mModel->addNewOperation(date, amount, category);
    return static_cast<OperationsView *>(mParent)->recalculateList();
}

DeleteOperationView::DeleteOperationView(AppModel *model, IView *parent)
    : IOperationView{model, parent, "Enter 'Id' or press ESC to back up"} { }

IView *DeleteOperationView::onEnterPressHandler()
{
    int id = mInputField.getExpressionResult();

    --id;

    if(id < 0 || id >= int(mModel->Operations.operations().size())) {
        mLogItem << "WARNING! Entered id [" << id + 1 << "/" << int(mModel->Operations.operations().size()) << "] is wrong!" << lendl;
        mInputField.restoreText();
        return this;
    }

    mModel->deleteOperation(id);
    return static_cast<OperationsView *>(mParent)->recalculateList();
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
    return mParent;
}

ChangeOperationView::ChangeOperationView(AppModel *model, IView *parent)
    : IOperationView{model, parent, "Enter 'Id' or press ESC to back up"} { }

IView *ChangeOperationView::onEnterPressHandler()
{
    int id = mInputField.getExpressionResult();

    --id;

    if(mModel->Operations.at(id) == mModel->Operations.operations().end()) {
        mLogItem << "WARNING! Entered id [" << id + 1 << "] is wrong!" << lendl;
        mInputField.restoreText();
        return this;
    }

    mModel->selectOperation(id);
    return new OperationView(mModel, mParent);
}

OperationView::OperationView(AppModel *model, IView *parent)
    : IView{model}, ISubView{parent}
{
    mOptionsList.insert(mOptionsList.end(), {
                                                new options::operations_view::ChangeDate,
                                                new options::operations_view::ChangeAmount,
                                                new options::operations_view::ChangeCategory,
                                                new options::main_view::Exit
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
    renderer.draw({mMenuBar->Width +  1, 2}, "%d.%s..%m.00 UAH", operation.id() + 1, operation.date().c_str(), operation.amount());
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

    mModel->selectedOperationChangeDate(date);
    return mParent;
}

ChangeAmount::ChangeAmount(AppModel *model, IView *parent)
    : IChangeOperationView{model, parent, "Enter 'amount' or press ESC to back up"} { }

IView *ChangeAmount::onEnterPressHandler()
{
    int amount = mInputField.getExpressionResult();

    mModel->selectedOperationChangeAmount(amount);
    return mParent;
}

ChangeCategory::ChangeCategory(AppModel *model, IView *parent)
    : IChangeOperationView{model, parent, "Enter 'category' or press ESC to back up"} { }

IView *ChangeCategory::onEnterPressHandler()
{
    std::string category = mInputField.getStr();

    if(mModel->Categories.findByName(category) == mModel->Categories.categories().end()) {
        mLogItem << "WARNING! Entered category [" << category << "] doesn't exist!" << lendl;
        mInputField.restoreText();
        return this;
    }

    mModel->selectedOperationChangeCategory(category);
    return mParent;
}

