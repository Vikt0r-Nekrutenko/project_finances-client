#ifndef DEBTLISTVIEW_HPP
#define DEBTLISTVIEW_HPP

#include "modelviewwithinputfield.hpp"

class AppModel;

class DebtListView : public ModelViewWithInputField
{
public:
    DebtListView(AppModel *model);
    void show(stf::Renderer &renderer) override;
    void onEnterHandler() override;
    stf::smv::IView *keyEventsHandler(const int key) override;
};

#endif // DEBTLISTVIEW_HPP
