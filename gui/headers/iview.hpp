#ifndef IVIEW_HPP
#define IVIEW_HPP

#include "renderer.hpp"
#include "imenu.hpp"

class ViewHolder;
class AppModel;

class IView
{
public:

    IView(AppModel *model, ViewHolder *holder);
    virtual ~IView();
    virtual void show(stf::Renderer &) const;
    virtual bool isContinue() const;
    IView *keyHandler(int key);

    ViewHolder *holder() const;

protected:

    MenuBar mOptionsList;
    ActiveMenu *mActiveMenuBar = new ActiveMenu{&mOptionsList};
    InactiveMenu *mInactiveMenuBar = new InactiveMenu{&mOptionsList};
    IMenu *mMenuBar = mInactiveMenuBar;
    AppModel *mModel;
    ViewHolder *mHolder;
};

class CloseView : public IView
{
public:

    CloseView(AppModel *model, ViewHolder *holder);
    bool isContinue() const override;
};

class ViewWithLogItem : public IView
{
public:

    ViewWithLogItem(AppModel *model, ViewHolder *holder)
        : IView{model, holder} { }

    void show(stf::Renderer &renderer) const override
    {
        renderer.drawLine({mMenuBar->Width + 1, renderer.Size.y - 4},
                          {renderer.Size.x - 1, renderer.Size.y - 4}, '-');
        IView::show(renderer);
    }

private:

    int mLastLogSize = 0;
};

#endif // IVIEW_HPP
