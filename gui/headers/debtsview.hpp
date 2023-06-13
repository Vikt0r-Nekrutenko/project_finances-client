#ifndef DEBTSVIEW_HPP
#define DEBTSVIEW_HPP

#include "iview.hpp"

class DebtsView : public IView, public IViewWithMenuItem, public IViewWithLogItem
{
public:

    DebtsView(AppModel *model, ViewHolder *holder);

    void show(stf::Renderer &renderer) override;

    IView *keyHandler(int key) override;
};

namespace input_views {
namespace debts_views {

class IDebtView : public DebtsView, public IViewWithInputField
{
public:

    IDebtView(AppModel *model, ViewHolder *holder, const std::string &inputTitle);

    void show(stf::Renderer &renderer) override;

    IView *keyHandler(int key) override;

protected:

    const std::string mInputTitle;
};

class AddNewDebtView : public IDebtView
{
public:

    AddNewDebtView(AppModel *model, ViewHolder *holder);

    IView *onEnterPressHandler() override;
};

class ChangeNameView : public IDebtView
{
public:

    ChangeNameView(AppModel *model, ViewHolder *holder);

    IView *onEnterPressHandler() override;
};

class ChangeAmountView : public IDebtView
{
public:

    ChangeAmountView(AppModel *model, ViewHolder *holder);

    IView *onEnterPressHandler() override;
};

class DeleteDebtView : public IDebtView
{
public:

    DeleteDebtView(AppModel *model, ViewHolder *holder);

    IView *onEnterPressHandler() override;
};

}}
#endif // DEBTSVIEW_HPP
