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

class ChangeOperationView : public IOperationView
{
public:

    ChangeOperationView(AppModel *model, IView *parent);

    IView *onEnterPressHandler() override;
};

}}

class OperationView : public IView, public ISubView, public IViewWithMenuItem, public IViewWithLogItem
{
public:

    OperationView(AppModel *model, IView *parent);

    void show(stf::Renderer &renderer) override;

    IView *keyHandler(int key) override;

    IView *recalculateList();
};

namespace input_views {
namespace change_operation_views {

class IChangeOperationView : public OperationsView, public IViewWithInputField
{
public:

    IChangeOperationView(AppModel *model, IView *parent, const std::string &inputTitle);

    void show(stf::Renderer &renderer) override;

    IView *keyHandler(int key) override;

protected:

    const std::string mInputTitle;
};

class ChangeDate : public IChangeOperationView
{
public:

    ChangeDate(AppModel *model, IView *parent);

    IView *onEnterPressHandler() override;
};

class ChangeDeposit : public IChangeOperationView
{
public:

    ChangeDeposit(AppModel *model, IView *parent);

    IView *onEnterPressHandler() override;
};

class ChangeAmount : public IChangeOperationView
{
public:

    ChangeAmount(AppModel *model, IView *parent);

    IView *onEnterPressHandler() override;
};

class ChangeCategory : public IChangeOperationView
{
public:

    ChangeCategory(AppModel *model, IView *parent);

    IView *onEnterPressHandler() override;
};

}}

#endif // OPERATIONSVIEW_HPP
