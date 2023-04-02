#include "operationslistview.hpp"
#include "appmodel.hpp"

OperationsListView::OperationsListView(AppModel *model)
    : ModelViewWithInputField(model) {}

void OperationsListView::show(stf::Renderer &renderer)
{

}

void OperationsListView::onEnterHandler()
{

}

stf::smv::IView *OperationsListView::keyEventsHandler(const int key)
{
    return this;
}
