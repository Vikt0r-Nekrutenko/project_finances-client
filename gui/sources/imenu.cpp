#include "imenu.hpp"
#include "ioption.hpp"


IMenu::IMenu(const MenuBar *mbar)
    : mMenuBar{mbar} { }

void IMenu::show(stf::Renderer &renderer)
{
    renderer.drawLine({Width, 2}, {Width, renderer.Size.y}, '|');

    renderer.drawPixel({0, 2 + int(Selector)}, '[');
    renderer.drawPixel({Width - 1, 2 + int(Selector)}, ']');
}

IView *IMenu::keyHandler(IView *sender, int key)
{
    if(key == 'w')
        if(Selector == 0)
            Selector = mMenuBar->size() - 1;
        else
            --Selector;
    else if(key == 's')
        if(Selector == mMenuBar->size() - 1)
            Selector = 0;
        else
            ++Selector;
    else if(key == VK_ENTER1 || key == VK_ENTER2) {
        return mMenuBar->at(Selector)->execute(sender);
    } else if(key >= '1' && key <= '9' && size_t(key - '0' - 1) < mMenuBar->size()) {
        Selector = key - '0' - 1;
        return mMenuBar->at(Selector)->execute(sender);
    }
    return sender;
}

ActiveMenu::ActiveMenu(const MenuBar *mbar)
    : IMenu(mbar) { }

void ActiveMenu::show(stf::Renderer &renderer)
{
    for(size_t i = 0; i < mMenuBar->size(); ++i) {
        renderer.draw({1, 2 + int(i)}, "%d.%s", i+1, mMenuBar->at(i)->caption().c_str());
    }
    IMenu::show(renderer);
}

void ActiveMenu::recalculateBarWidth()
{
    for(size_t i = 0; i < mMenuBar->size(); ++i) {
        if(int(mMenuBar->at(i)->caption().length()) > Width)
            Width = mMenuBar->at(i)->caption().length();
    }
    Width += 4;
}

bool ActiveMenu::isActive() const
{
    return true;
}

InactiveMenu::InactiveMenu(const MenuBar *mbar)
    : IMenu(mbar) { }

void InactiveMenu::show(stf::Renderer &renderer)
{
    for(size_t i = 0; i < mMenuBar->size(); ++i) {
        renderer.draw({1, 2 + int(i)}, "%d", i+1);
    }
    IMenu::show(renderer);
}

bool InactiveMenu::isActive() const
{
    return false;
}
