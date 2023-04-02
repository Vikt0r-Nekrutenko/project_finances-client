#ifndef OPERATIONSLISTVIEW_HPP
#define OPERATIONSLISTVIEW_HPP

#include "modelviewwithinputfield.hpp"

class AppModel;

class OperationsListView : public ModelViewWithInputField
{
public:
    OperationsListView(AppModel *model);
    void show(stf::Renderer &renderer) override;
    void onEnterHandler() override;
    stf::smv::IView *keyEventsHandler(const int key) override;
};

#endif // OPERATIONSLISTVIEW_HPP
