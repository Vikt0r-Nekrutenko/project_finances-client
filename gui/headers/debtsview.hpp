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

#endif // DEBTSVIEW_HPP
