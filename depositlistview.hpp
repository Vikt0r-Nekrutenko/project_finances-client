#ifndef DEPOSITLISTVIEW_HPP
#define DEPOSITLISTVIEW_HPP

#include "smv/iview.hpp"

class AppModel;

class DepositListView : stf::smv::IView
{
public:
    DepositListView(AppModel *model);
    void show(stf::Renderer &renderer) override;

    stf::smv::IView *keyEventsHandler(const int key) override;
};

#endif // DEPOSITLISTVIEW_HPP
