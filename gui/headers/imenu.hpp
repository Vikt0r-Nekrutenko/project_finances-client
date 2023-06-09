#ifndef IMENU_H
#define IMENU_H

#include "renderer.hpp"
#include <vector>

class IOption;
class IView;

using MenuBar = std::vector<IOption *>;

constexpr int VK_ENTER1 = 13;
constexpr int VK_ENTER2 = 10;

class IMenu
{
public:

    size_t Width = 3;
    size_t Selector;

    IMenu(const MenuBar *mbar);
    virtual ~IMenu() = default;

    virtual void show(stf::Renderer &renderer);
    virtual bool isActive() const = 0;

    IView *keyHandler(IView *sender, int key);

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
