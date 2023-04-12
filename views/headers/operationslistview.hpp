#ifndef OPERATIONSLISTVIEW_HPP
#define OPERATIONSLISTVIEW_HPP

#include "modelviewwithinputfield.hpp"

class AppModel;
class OperationHandler;

class OperationsListView : public ModelViewWithInputField
{
public:
    OperationsListView(AppModel *model);
    ~OperationsListView() override;
    void show(stf::Renderer &renderer) override;
    void onEnterHandler() override;
    stf::smv::IView *keyEventsHandler(const int key) override;

private:

    std::vector<OperationHandler *> mMenu;
};

#endif // OPERATIONSLISTVIEW_HPP
