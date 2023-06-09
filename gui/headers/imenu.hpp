#ifndef IMENU_H
#define IMENU_H

#include "renderer.hpp"
#include <vector>

class Option;

using MenuBar = std::vector<Option *>;

class IMenu
{
public:

    size_t Width = 3;
    size_t Selector;

    IMenu(const MenuBar *mbar);
    virtual ~IMenu() = default;

    virtual void show(stf::Renderer &renderer);
    virtual bool isActive() const = 0;

protected:

    const MenuBar *mMenuBar;
};

#endif // IMENU_H
