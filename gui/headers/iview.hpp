#ifndef IVIEW_HPP
#define IVIEW_HPP

#include "renderer.hpp"
#include "imenu.hpp"

class IView
{
public:

    void show(stf::Renderer &) const;

protected:

    MenuBar mMenuBar;
    ActiveMenu *mActiveMenuBar = new ActiveMenu{&mMenuBar};
    InactiveMenu *mInactiveMenuBar = new InactiveMenu{&mMenuBar};
    IMenu *MenuBar = mInactiveMenuBar;
};

#endif // IVIEW_HPP
