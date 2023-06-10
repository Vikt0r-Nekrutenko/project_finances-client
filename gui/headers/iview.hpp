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

#endif // IVIEW_HPP
