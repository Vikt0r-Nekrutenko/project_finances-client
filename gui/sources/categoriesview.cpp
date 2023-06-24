#include "categoriesview.hpp"
#include "appmodel.hpp"
#include "ioption.hpp"


CategoriesView::CategoriesView(AppModel *model, IView *parent)
    : IView{model}, ISubView{parent}
{
    mOptionsList.insert(mOptionsList.end(), {
                                                new options::categories_view::AddNewCategory,
                                                new options::categories_view::DeleteCategory,
                                                new options::categories_view::SelectFavoriteCategories,
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
    if(key == VK_ESCAPE1)
        return mParent;
    if (key == 'q') {
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
    return mParent;
}

DeleteCategoryView::DeleteCategoryView(AppModel *model, IView *parent)
    : ICategoryView{model, parent, "Enter 'Id' or press ESC to back up"} { }

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
    return mParent;
}

SelectFavoriteCategoriesView::SelectFavoriteCategoriesView(AppModel *model, IView *parent)
    : ICategoryView{model, parent, "Enter 'Id1 Id2 Id3' or press ESC to back up"} { }

IView *SelectFavoriteCategoriesView::onEnterPressHandler()
{
    int id1 = mInputField.getExpressionResult();
    int id2 = mInputField.getExpressionResult();
    int id3 = mInputField.getExpressionResult();

    --id1; --id2; --id3;

    if(id1 < 0 || id1 >= int(mModel->Categories.categories().size()) ||
        id2 < 0 || id2 >= int(mModel->Categories.categories().size()) ||
        id3 < 0 || id3 >= int(mModel->Categories.categories().size()))
    {
        mLogItem << "WARNING! Entered ids is wrong!" << lendl;
        mInputField.restoreText();
        return this;
    }

    mModel->selectFavoriteCategories(id1, id2, id3);
    return mParent;
}
