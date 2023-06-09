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
//    Menu *mActiveMenuBar = new ActiveMenu{&bar};
//    Menu *mInactiveMenuBar = new InactiveMenu{&bar};
    IMenu *MenuBar ;//mInactiveMenuBar;
};

#endif // IVIEW_HPP
