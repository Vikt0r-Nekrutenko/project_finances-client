#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include "ioption.hpp"
#include "iview.hpp"

class MainView : public IView
{
public:
    MainView(AppModel *model, ViewHolder *holder)
        : IView{model, holder}
    {
        mOptionsList.push_back(new options::main_view::Deposits);
        mActiveMenuBar->recalculateBarWidth();
    }

    void show(stf::Renderer &renderer) const override
    {
        renderer.draw({mMenuBar->Width + 1, 1}, "Main View");
        IView::show(renderer);
    }
};

#endif // MAINVIEW_HPP
