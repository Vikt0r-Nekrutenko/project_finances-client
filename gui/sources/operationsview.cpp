#include "operationsview.hpp"
#include "appmodel.hpp"
#include "headers/queryresult.hpp"
#include "ioption.hpp"
#include "viewholder.hpp"


OperationsView::OperationsView(AppModel *model, ViewHolder *holder)
    : IView{model, holder}
{
    mOptionsList.insert(mOptionsList.end(), {
                                                new options::BackToStartView,
                                                new options::main_view::Exit
                                            });
    mActiveMenuBar->recalculateBarWidth();
}

void OperationsView::show(stf::Renderer &renderer)
{
    IView::show(renderer);
    mMenuBar->show(renderer);
    drawLogItem(renderer, mMenuBar->Width);

    OperationHandlerQuery operations(&mModel->Operations);
    operations.select().filterByDeposit(mModel->selectedDeposit()->name());

    int index = 1;
    for(const auto &operation : operations) {
        renderer.drawLine({mMenuBar->Width +  1, 1 + index}, {renderer.Size.x - 1, 1 + index}, '.');
        renderer.draw({mMenuBar->Width +  1, 1 + index}, "%d.%s..%m.00 UAH", operation->id(), operation->date().c_str(), operation->amount());
        renderer.draw({mMenuBar->Width + 25, 1 + index}, "%s", operation->category().c_str());
        ++index;
    }
}

IView *OperationsView::keyHandler(int key)
{
    switchMenuBar(key);
    return mMenuBar->keyHandler(this, key);
}

using namespace input_views::operations_views;

IOperationView::IOperationView(AppModel *model, ViewHolder *holder, const std::string &inputTitle)
    : OperationsView{model, holder}, mInputTitle{inputTitle} { }

void IOperationView::show(stf::Renderer &renderer)
{
    OperationsView::show(renderer);
    drawInputField(renderer, mMenuBar->Width, mInputTitle);
}

IView *IOperationView::keyHandler(int key)
{
    return onKeyPressHandler(key, this, mHolder->getOperationsView());
}

AddNewOperationView::AddNewOperationView(AppModel *model, ViewHolder *holder)
    : IOperationView{model, holder, "Enter 'Name Type' or press ESC to back up"} { }

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
    if(date.length() < 9 || (date[4] != '-' && date[7] != '-')) {
        mLogItem << "WARNING! Entered date [" << date << "] is wrong!" << lendl;
        mInputField.restoreText();
        return this;
    }

    mModel->addNewOperation(date, amount, category);
    return mHolder->getCategoriesView();
}

DeleteOperationView::DeleteOperationView(AppModel *model, ViewHolder *holder)
    : IOperationView{model, holder, "Enter 'Id' or press ESC to back up"} { }

IView *DeleteOperationView::onEnterPressHandler()
{
    int id = mInputField.getExpressionResult();

    --id;

    if(id < 0 || id >= int(mModel->Categories.categories().size())) {
        mLogItem << "WARNING! Entered id [" << id + 1 << "] is wrong!" << lendl;
        mInputField.restoreText();
        return this;
    }

    mModel->deleteOperation(id);
    return mHolder->getCategoriesView();
}
