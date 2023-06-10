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
        renderer.draw({5, 1}, "Deposit View");
    }

    IView *keyHandler(int key) override
    {
        switchMenuBar(key);
        return mMenuBar->keyHandler(this, key);
    }
};

#endif // DEPOSITVIEW_HPP
