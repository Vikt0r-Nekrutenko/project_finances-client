#include "categoriesview.hpp"
#include "appmodel.hpp"
#include "ioption.hpp"


CategoriesView::CategoriesView(AppModel *model, IView *parent)
    : IView{model}, ISubView{parent}
{
    mOptionsList.insert(mOptionsList.end(), {
                                                new options::categories_view::AddNewCategory,
                                                new options::categories_view::DeleteCategory,
                                            });
    mActiveMenuBar->recalculateBarWidth();
    mModel->calcPnLsByCategories();
}

void CategoriesView::show(stf::Renderer &renderer)
{
    IView::show(renderer);
    mMenuBar->show(renderer);
    drawLogItem(renderer, mMenuBar->Width);

    int index = 1;
    auto drawColoredInfo = [&](const std::string &a, int v, int ox = 0) {
        renderer.draw({mMenuBar->Width + 1 + ox, 1 + index}, (a + (v > 0 ? "%CG%m.00%CD %s" : "%CR%m.00%CD %s")).c_str(), int(float(v) / mModel->currentCurrency().second), mModel->currentCurrency().first.c_str());
    };

    for(auto [category, daily, monthly, yearly] : mModel->pnlsByCategories()) {
        renderer.drawLine({mMenuBar->Width +  1, 1 + index}, {renderer.Size.x - 1, 1 + index}, '.');
        renderer.draw({mMenuBar->Width +  1, 1 + index}, "%d.%s", index, category->name().c_str());
        drawColoredInfo("", daily, 15);
        drawColoredInfo("", monthly, 30);
        drawColoredInfo("", yearly, 50);
        ++index;
    }
}

IView *CategoriesView::keyHandler(int key)
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

using namespace input_views::categories_views;

ICategoryView::ICategoryView(AppModel *model, IView *parent, const std::string &inputTitle)
    : CategoriesView{model, parent}, mInputTitle{inputTitle} { }

void ICategoryView::show(stf::Renderer &renderer)
{
    CategoriesView::show(renderer);
    drawInputField(renderer, mMenuBar->Width, mInputTitle);
}

IView *ICategoryView::keyHandler(int key)
{
    return onKeyPressHandler(key, this, mParent);
}

AddNewCategoryView::AddNewCategoryView(AppModel *model, IView *parent)
    : ICategoryView{model, parent, "Enter 'Name Type' or press ESC to back up"} { }

IView *AddNewCategoryView::onEnterPressHandler()
{
    std::string name, type;

    try {
        name = mInputField.getStr();
        type = mInputField.getStr();
    } catch(...) {
        return this;
    }

    if(mModel->Categories.query.findByName(name) != mModel->Categories.query.end()) {
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
    return mParent;
}

DeleteCategoryView::DeleteCategoryView(AppModel *model, IView *parent)
    : ICategoryView{model, parent, "WARNING! You gonna delete category! Enter 'Id' or press ESC to back up"} { }

IView *DeleteCategoryView::onEnterPressHandler()
{
    int id = 0;
    try {
        id = mInputField.getExpressionResult();
    } catch(const std::invalid_argument &) {
        return this;
    }

    --id;

    if(id < 0 || id >= int(mModel->Categories.query.size())) {
        mLogItem << "WARNING! Entered id [" << id + 1 << "] is wrong!" << lendl;
        mInputField.restoreText();
        return this;
    }

    mModel->Categories.deleteCategory(id);
    return mParent;
}
