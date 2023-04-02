#ifndef DEPOSITLISTVIEW_HPP
#define DEPOSITLISTVIEW_HPP

#include "smv/iview.hpp"

class AppModel;

class DepositListView : public stf::smv::IView
{
public:
    DepositListView(AppModel *model);
    void show(stf::Renderer &renderer) override;

    stf::smv::IView *keyEventsHandler(const int key) override;

private:

    std::string mInput;
    int mOption = 0;
};

#endif // DEPOSITLISTVIEW_HPP
