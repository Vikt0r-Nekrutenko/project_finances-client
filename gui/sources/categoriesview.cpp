#include "categoriesview.hpp"
#include "appmodel.hpp"
#include "ioption.hpp"
#include "viewholder.hpp"


CategoriesView::CategoriesView(AppModel *model, ViewHolder *holder)
    : IView{model, holder}
{
    mOptionsList.insert(mOptionsList.end(), {
                                                new options::categories_view::AddNewCategory,
                                                new options::categories_view::DeleteCategory,
                                                new options::BackToStartView,
                                                new options::main_view::Exit
                                            });
    mActiveMenuBar->recalculateBarWidth();
}

void CategoriesView::show(stf::Renderer &renderer)
{
    IView::show(renderer);
    mMenuBar->show(renderer);
    drawLogItem(renderer, mMenuBar->Width);

    int index = 1;
    for(const auto &Category : mModel->Categories.categories()) {
        renderer.drawLine({mMenuBar->Width +  1, 1 + index}, {renderer.Size.x - 1, 1 + index}, '.');
        renderer.draw({mMenuBar->Width +  1, 1 + index}, "%d.%s", index, Category.name().c_str());
        renderer.draw({mMenuBar->Width + 15, 1 + index}, "%s", Category.type().c_str());
        ++index;
    }
}

IView *CategoriesView::keyHandler(int key)
{
    switchMenuBar(key);
    return mMenuBar->keyHandler(this, key);
}

using namespace input_views::categories_views;

ICategoryView::ICategoryView(AppModel *model, ViewHolder *holder, const std::string &inputTitle)
    : CategoriesView{model, holder}, mInputTitle{inputTitle} { }

void ICategoryView::show(stf::Renderer &renderer)
{
    CategoriesView::show(renderer);
    drawInputField(renderer, mMenuBar->Width, mInputTitle);
}

IView *ICategoryView::keyHandler(int key)
{
    return onKeyPressHandler(key, this, mHolder->getCategoriesView());
}

AddNewCategoryView::AddNewCategoryView(AppModel *model, ViewHolder *holder)
    : ICategoryView{model, holder, "Enter 'Name Type' or press ESC to back up"} { }

IView *AddNewCategoryView::onEnterPressHandler()
{
    std::string name = mInputField.getStr();
    std::string type = mInputField.getStr();

    if(mModel->Categories.findByName(name) != mModel->Categories.categories().end()) {
        mLogItem << "WARNING! Entered name [" << name << "] is exist!" << lendl;
        mInputField.restoreText();
        return this;
    }
    if(type != "positive" && type != "negative" && type != "earn") {
        mLogItem << "WARNING! Entered type [" << type << "] isn't exist!" << lendl;
        mInputField.restoreText();
        return this;
    }

    mModel->Categories.addNewCategory(name, type);
    return mHolder->getCategoriesView();
}

DeleteCategoryView::DeleteCategoryView(AppModel *model, ViewHolder *holder)
    : ICategoryView{model, holder, "Enter 'Id' or press ESC to back up"} { }

IView *DeleteCategoryView::onEnterPressHandler()
{
    int id = mInputField.getExpressionResult();

    --id;

    if(id < 0 || id >= int(mModel->Categories.categories().size())) {
        mLogItem << "WARNING! Entered id [" << id + 1 << "] is wrong!" << lendl;
        mInputField.restoreText();
        return this;
    }

    mModel->Categories.deleteCategory(id);
    return mHolder->getCategoriesView();
}
