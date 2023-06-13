#ifndef OPERATIONSVIEW_HPP
#define OPERATIONSVIEW_HPP

#include "iview.hpp"

class OperationsView : public IView, public IViewWithMenuItem, public IViewWithLogItem
{
public:

    OperationsView(AppModel *model, ViewHolder *holder);

    void show(stf::Renderer &renderer) override;

    IView *keyHandler(int key) override;
};

namespace input_views {
namespace operations_views {

class IOperationView : public OperationsView, public IViewWithInputField
{
public:

    IOperationView(AppModel *model, ViewHolder *holder, const std::string &inputTitle);

    void show(stf::Renderer &renderer) override;

    IView *keyHandler(int key) override;

protected:

    const std::string mInputTitle;
};

class AddNewOperationView : public IOperationView
{
public:

    AddNewOperationView(AppModel *model, ViewHolder *holder);

    IView *onEnterPressHandler() override;
};

class DeleteOperationView : public IOperationView
{
public:

    DeleteOperationView(AppModel *model, ViewHolder *holder);

    IView *onEnterPressHandler() override;
};

}}

#endif // OPERATIONSVIEW_HPP
