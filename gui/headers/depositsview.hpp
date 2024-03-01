#ifndef DEPOSITSVIEW_H
#define DEPOSITSVIEW_H

#include "iview.hpp"

class DepositsView : public IView, public ISubView, public IViewWithMenuItem, public IViewWithLogItem
{
public:

    DepositsView(AppModel *model, IView *parent);

    void show(stf::Renderer &renderer) override;

    IView *keyHandler(int key) override;
};

namespace input_views {
namespace deposits_views {

class IDepositView : public DepositsView, public IViewWithInputField
{
public:

    IDepositView(AppModel *model, IView *parent, const std::string &inputTitle);

    void show(stf::Renderer &renderer) override;

    IView *keyHandler(int key) override;

protected:

    const std::string mInputTitle;
};

class AddNewDepositView : public IDepositView
{
public:

    AddNewDepositView(AppModel *model, IView *parent);

    IView *onEnterPressHandler() override;
};

class ChangeBalanceView : public IDepositView
{
public:

    ChangeBalanceView(AppModel *model, IView *parent);

    IView *onEnterPressHandler() override;
};

class DeleteDepositView : public IDepositView
{
public:

    DeleteDepositView(AppModel *model, IView *parent);

    IView *onEnterPressHandler() override;
};

class SelectDepositView : public IDepositView
{
public:

    SelectDepositView(AppModel *model, IView *parent);

    IView *onEnterPressHandler() override;
};

class MakeTransferView : public IDepositView
{
public:

    MakeTransferView(AppModel *model, IView *parent);

    IView *onEnterPressHandler() override;
};

}}

#endif // DEPOSITSVIEW_H
