#ifndef CATEGORYLISTVIEW_HPP
#define CATEGORYLISTVIEW_HPP

#include "modelviewwithinputfield.hpp"

class AppModel;

class CategoryListView : public ModelViewWithInputField
{
public:
    CategoryListView(AppModel *model);
    void show(stf::Renderer &renderer) override;
    void onEnterHandler() override;
    stf::smv::IView *keyEventsHandler(const int key) override;
};

#endif // CATEGORYLISTVIEW_HPP
