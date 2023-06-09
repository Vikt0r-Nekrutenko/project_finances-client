#ifndef IMENU_H
#define IMENU_H

#include "renderer.hpp"
#include <vector>

class IOption;
class IView;

using MenuBar = std::vector<IOption *>;

constexpr int VK_ENTER1 = 13;
constexpr int VK_ENTER2 = 10;
constexpr int DEFAULT_MENU_WIDTH = 3;

class IMenu
{
public:

    int Width = DEFAULT_MENU_WIDTH;

    IMenu(const MenuBar *mbar);
    virtual ~IMenu() = default;

    virtual void show(stf::Renderer &renderer);
    virtual bool isActive() const = 0;

    IView *keyHandler(IView *sender, int key);

protected:

    const MenuBar *mMenuBar;
    size_t Selector = 0;
};

class ActiveMenu : public IMenu
{
public:

    ActiveMenu(const MenuBar *mbar);
    void recalculateBarWidth();
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
