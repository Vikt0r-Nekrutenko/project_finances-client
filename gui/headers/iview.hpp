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
    void show(stf::Renderer &) const;
    IView *keyHandler(int key);

    ViewHolder *holder() const;

protected:

    MenuBar mMenuBar;
    ActiveMenu *mActiveMenuBar = new ActiveMenu{&mMenuBar};
    InactiveMenu *mInactiveMenuBar = new InactiveMenu{&mMenuBar};
    IMenu *MenuBar = mInactiveMenuBar;
    AppModel *mModel;
    ViewHolder *mHolder;
};

#endif // IVIEW_HPP
