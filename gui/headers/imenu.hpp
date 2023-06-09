#ifndef IMENU_H
#define IMENU_H

#include "renderer.hpp"
#include <vector>

class IOption;

using MenuBar = std::vector<IOption *>;

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

class ActiveMenu : public IMenu
{
public:

    ActiveMenu(const MenuBar *mbar);
    void show(stf::Renderer &renderer) override;
    bool isActive() const override;
};

class InactiveMenu : public IMenu
{
public:

    InactiveMenu(const MenuBar *mbar);
    void show(stf::Renderer &renderer) override;
    bool isActive() const override;
};

#endif // IMENU_H
