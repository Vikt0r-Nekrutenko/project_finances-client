#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include "ioption.hpp"
#include "iview.hpp"

class MainView : public IView, public IViewWithMenuItem, public IViewWithLogItem, public IViewWithInputField
{
public:
    MainView(AppModel *model, ViewHolder *holder)
        : IView{model, holder}
    {
        mOptionsList.insert(mOptionsList.end(), {
                                                 new options::main_view::Deposits,
                                                 new options::main_view::Exit
                                                });
        mActiveMenuBar->recalculateBarWidth();
    }

    void show(stf::Renderer &renderer) override
    {
        renderer.draw({mMenuBar->Width + 1, 1}, "Main View");
        mMenuBar->show(renderer);
        drawLogItem(renderer, mMenuBar->Width);
        drawInputField(renderer, mMenuBar->Width);
    }

    IView *keyHandler(int key) override
    {
        switchMenuBar(key);
        mInputField->keyHandler(this, key);
        return mMenuBar->keyHandler(this, key);
    }
};

#endif // MAINVIEW_HPP
