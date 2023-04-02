#ifndef DEPOSITLISTVIEW_HPP
#define DEPOSITLISTVIEW_HPP

#include "modelviewwithinputfield.hpp"

class AppModel;

class DepositListView : public ModelViewWithInputField
{
public:
    DepositListView(AppModel *model);
    void show(stf::Renderer &renderer) override;
    void onEnterHandler() override;
    stf::smv::IView *keyEventsHandler(const int key) override;
};

#endif // DEPOSITLISTVIEW_HPP
