#ifndef DEBTSVIEW_HPP
#define DEBTSVIEW_HPP

#include "iview.hpp"

class DebtsView : public IView, public ISubView, public IViewWithMenuItem, public IViewWithLogItem
{
public:

    DebtsView(AppModel *model, IView *parent);

    void show(stf::Renderer &renderer) override;

    IView *keyHandler(int key) override;
};

namespace input_views {
namespace debts_views {

class IDebtView : public DebtsView, public IViewWithInputField
{
public:

    IDebtView(AppModel *model, IView *parent, const std::string &inputTitle);

    void show(stf::Renderer &renderer) override;

    IView *keyHandler(int key) override;

protected:

    const std::string mInputTitle;
};

class AddNewDebtView : public IDebtView
{
public:

    AddNewDebtView(AppModel *model, IView *parent);

    IView *onEnterPressHandler() override;
};

class ChangeAmountView : public IDebtView
{
public:

    ChangeAmountView(AppModel *model, IView *parent);

    IView *onEnterPressHandler() override;
};

class DeleteDebtView : public IDebtView
{
public:

    DeleteDebtView(AppModel *model, IView *parent);

    IView *onEnterPressHandler() override;
};

}}
#endif // DEBTSVIEW_HPP
