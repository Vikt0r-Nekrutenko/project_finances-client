#ifndef OPERATIONSVIEW_HPP
#define OPERATIONSVIEW_HPP

#include "iview.hpp"
#include "headers/queryresult.hpp"

class OperationsView : public IView, public ISubView, public IViewWithMenuItem, public IViewWithLogItem
{
public:

    OperationsView(AppModel *model, IView *parent);

    void show(stf::Renderer &renderer) override;

    IView *keyHandler(int key) override;

    IView *recalculateList();

protected:

    OperationHandlerQuery mOperationsList;
};

namespace input_views {
namespace operations_views {

class IOperationView : public OperationsView, public IViewWithInputField
{
public:

    IOperationView(AppModel *model, IView *parent, const std::string &inputTitle);

    void show(stf::Renderer &renderer) override;

    IView *keyHandler(int key) override;

protected:

    const std::string mInputTitle;
};

class AddNewOperationView : public IOperationView
{
public:

    AddNewOperationView(AppModel *model, IView *parent);

    IView *onEnterPressHandler() override;
};

class DeleteOperationView : public IOperationView
{
public:

    DeleteOperationView(AppModel *model, IView *parent);

    IView *onEnterPressHandler() override;
};

class SelectOperationsView : public IOperationView
{
public:

    SelectOperationsView(AppModel *model, IView *parent);

    IView *onEnterPressHandler() override;
};

}}

#endif // OPERATIONSVIEW_HPP
