#ifndef DEPOSITVIEW_HPP
#define DEPOSITVIEW_HPP

#include "iview.hpp"

class DepositView : public IView, public IViewWithMenuItem, public IViewWithLogItem
{
public:
    DepositView(AppModel *model, ViewHolder *holder)
        : IView{model, holder} { }

    void show(stf::Renderer &renderer) override
    {
        IView::show(renderer);
        renderer.draw({5, 1}, "Deposit View");
        mMenuBar->show(renderer);
        drawLogItem(renderer, mMenuBar->Width);
    }

    IView *keyHandler(int key) override
    {
        switchMenuBar(key);
        return mMenuBar->keyHandler(this, key);
    }
};

class AddNewDepositView : public DepositView, public IViewWithInputField
{
public:

    AddNewDepositView(AppModel *model, ViewHolder *holder)
        : DepositView{model, holder} { }

    void show(stf::Renderer &renderer) override
    {
        IView::show(renderer);
        renderer.draw({5, 1}, "Deposit View");
        drawLogItem(renderer, 0);
        drawInputField(renderer, 0);
    }

    IView *keyHandler(int key) override
    {
        mInputField->keyHandler(this, key);
        if(key == VK_ENTER1 || key == VK_ENTER2)
            //return mHolder->getDepositView();
        return this;
    }
};

#endif // DEPOSITVIEW_HPP
