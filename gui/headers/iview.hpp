#ifndef IVIEW_HPP
#define IVIEW_HPP

#include "renderer.hpp"
#include "imenu.hpp"
#include "ioption.hpp"

class IView
{
public:

    virtual ~IView();
    void show(stf::Renderer &) const;

protected:

    MenuBar mMenuBar {new IOption, new IOption, new IOption};
    ActiveMenu *mActiveMenuBar = new ActiveMenu{&mMenuBar};
    InactiveMenu *mInactiveMenuBar = new InactiveMenu{&mMenuBar};
    IMenu *MenuBar = mInactiveMenuBar;
};

#endif // IVIEW_HPP
