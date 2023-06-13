#ifndef DEPOSITSVIEW_H
#define DEPOSITSVIEW_H

#include "iview.hpp"

class DepositsView : public IView, public IViewWithMenuItem, public IViewWithLogItem
{
public:

    DepositsView(AppModel *model, ViewHolder *holder);

    void show(stf::Renderer &renderer) override;

    IView *keyHandler(int key) override;
};

namespace input_views {
namespace deposits_views {

class IDepositView : public DepositsView, public IViewWithInputField
{
public:

    IDepositView(AppModel *model, ViewHolder *holder, const std::string &inputTitle);

    void show(stf::Renderer &renderer) override;

    IView *keyHandler(int key) override;

protected:

    const std::string mInputTitle;
};

class AddNewDepositView : public DepositsView, public IViewWithInputField
{
public:

    AddNewDepositView(AppModel *model, ViewHolder *holder);

    void show(stf::Renderer &renderer) override;

    IView *keyHandler(int key) override;

    IView *onEnterPressHandler() override;
};

class ChangeBalanceView : public DepositsView, public IViewWithInputField
{
public:

    ChangeBalanceView(AppModel *model, ViewHolder *holder);

    void show(stf::Renderer &renderer) override;

    IView *keyHandler(int key) override;

    IView *onEnterPressHandler() override;
};

class DeleteDepositView : public DepositsView, public IViewWithInputField
{
public:

    DeleteDepositView(AppModel *model, ViewHolder *holder);

    void show(stf::Renderer &renderer) override;

    IView *keyHandler(int key) override;

    IView *onEnterPressHandler() override;
};

class SelectDepositView : public DepositsView, public IViewWithInputField
{
public:

    SelectDepositView(AppModel *model, ViewHolder *holder);

    void show(stf::Renderer &renderer) override;

    IView *keyHandler(int key) override;

    IView *onEnterPressHandler() override;
};

}}

#endif // DEPOSITSVIEW_H
