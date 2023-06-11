#ifndef DEPOSITVIEW_HPP
#define DEPOSITVIEW_HPP

#include "iview.hpp"

class DepositsView : public IView, public IViewWithMenuItem, public IViewWithLogItem
{
public:
    DepositsView(AppModel *model, ViewHolder *holder)
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

class AddNewDepositView : public DepositsView, public IViewWithInputField
{
public:

    std::string name; int balance;

    AddNewDepositView(AppModel *model, ViewHolder *holder)
        : DepositsView{model, holder} { }

    void show(stf::Renderer &renderer) override
    {
        IView::show(renderer);
        renderer.draw({5, 1}, "Deposit View");
        renderer.draw({5, 2}, "%s %m.00 UAH", name.c_str(), balance);
        drawLogItem(renderer, 0);
        drawInputField(renderer, 0);
    }

    IView *keyHandler(int key) override
    {
        mInputField.keyHandler(this, key);
        if(key == VK_ENTER1 || key == VK_ENTER2) {
            name = mInputField.getStr();
            balance = mInputField.getExpressionResult();
        }
            //return mHolder->getDepositView();
        return this;
    }
};

#endif // DEPOSITVIEW_HPP
