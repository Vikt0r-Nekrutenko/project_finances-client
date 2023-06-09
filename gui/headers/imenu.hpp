#ifndef IMENU_H
#define IMENU_H

#include "renderer.hpp"
#include <vector>

class Option;

using MenuBar = std::vector<Option *>;

class IMenu
{
public:

    IMenu(MenuBar *mbar);
    virtual ~IMenu();

    virtual void show(stf::Renderer &renderer);

protected:

    MenuBar mMenuBar;
};

#endif // IMENU_H
