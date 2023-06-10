#ifndef DEPOSITVIEW_HPP
#define DEPOSITVIEW_HPP

#include "iview.hpp"

class DepositView : public IView
{
public:
    DepositView(AppModel *model, ViewHolder *holder)
        : IView{model, holder} { }

    void show(stf::Renderer &renderer) override
    {
        renderer.draw({5, 1}, "Deposit View");
        IView::show(renderer);
    }
};

#endif // DEPOSITVIEW_HPP
