#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include "iview.hpp"

class MainView : public IView, public IViewWithMenuItem, public IViewWithLogItem
{
public:

    MainView(AppModel *model);

    void show(stf::Renderer &renderer) override;

    IView *keyHandler(int key) override;
};

#endif // MAINVIEW_HPP
