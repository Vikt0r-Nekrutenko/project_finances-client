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

private:

//    std::string mInput;
//    int mOption = 0;

    // ModelViewWithInputField interface
public:
};

#endif // DEPOSITLISTVIEW_HPP
