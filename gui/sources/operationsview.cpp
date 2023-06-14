#include "operationsview.hpp"
#include "appmodel.hpp"
#include "ioption.hpp"
#include "viewholder.hpp"


OperationsView::OperationsView(AppModel *model, ViewHolder *holder)
    : IView{model, holder}, mOperationsList{&model->Operations}
{
    mOptionsList.insert(mOptionsList.end(), {
                                             new options::operations_view::AddNewOperation,
                                             new options::operations_view::DeleteOperation,
                                             new options::operations_view::SelectOperations,
                                             new options::main_view::Deposits,
                                             new options::main_view::Exit
                                            });
    mActiveMenuBar->recalculateBarWidth();
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

IOperationView::IOperationView(AppModel *model, ViewHolder *holder, const std::string &inputTitle)
    : OperationsView{model, holder}, mInputTitle{inputTitle} { }

void IOperationView::show(stf::Renderer &renderer)
{
    OperationsView::show(renderer);
    renderer.drawLine({mMenuBar->Width + 1, renderer.Size.y - LogHeight - 2}, {renderer.Size.x, renderer.Size.y - LogHeight - 2}, ' ');
    drawInputField(renderer, mMenuBar->Width, mInputTitle);
}

IView *IOperationView::keyHandler(int key)
{
    return onKeyPressHandler(key, this, mHolder->getOperationsView());
}

AddNewOperationView::AddNewOperationView(AppModel *model, ViewHolder *holder)
    : IOperationView{model, holder, "Enter 'Date Name Type' or press ESC to back up"} { }

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
    if(date.length() != 9 || date[4] != '-' || date[7] != '-') {
        mLogItem << "WARNING! Entered date [" << date << "] is wrong!" << lendl;
        mInputField.restoreText();
        return this;
    }

    mModel->addNewOperation(date, amount, category);
    return mHolder->getOperationsView();
}

DeleteOperationView::DeleteOperationView(AppModel *model, ViewHolder *holder)
    : IOperationView{model, holder, "Enter 'Id' or press ESC to back up"} { }

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
    return mHolder->getOperationsView();
}

SelectOperationsView::SelectOperationsView(AppModel *model, ViewHolder *holder)
    : IOperationView{model, holder, "Enter 'Year Month' or press ESC to back up"} { }

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
    return mHolder->getOperationsView();
}
