#ifndef CATEGORIESVIEW_HPP
#define CATEGORIESVIEW_HPP

#include "iview.hpp"

class CategoriesView : public IView, public IViewWithMenuItem, public IViewWithLogItem
{
public:

    CategoriesView(AppModel *model, ViewHolder *holder);

    void show(stf::Renderer &renderer) override;

    IView *keyHandler(int key) override;
};

namespace input_views {
namespace categories_views {

class ICategoryView : public CategoriesView, public IViewWithInputField
{
public:

    ICategoryView(AppModel *model, ViewHolder *holder, const std::string &inputTitle);

    void show(stf::Renderer &renderer) override;

    IView *keyHandler(int key) override;

protected:

    const std::string mInputTitle;
};

class AddNewCategoryView : public ICategoryView
{
public:

    AddNewCategoryView(AppModel *model, ViewHolder *holder);

    IView *onEnterPressHandler() override;
};

class DeleteCategoryView : public ICategoryView
{
public:

    DeleteCategoryView(AppModel *model, ViewHolder *holder);

    IView *onEnterPressHandler() override;
};

}}

#endif // CATEGORIESVIEW_HPP
