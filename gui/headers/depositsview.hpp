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

class AddNewDepositView : public DepositsView, public IViewWithInputField
{
public:

    AddNewDepositView(AppModel *model, ViewHolder *holder);

    void show(stf::Renderer &renderer) override;

    IView *keyHandler(int key) override;
};

#endif // DEPOSITSVIEW_H
