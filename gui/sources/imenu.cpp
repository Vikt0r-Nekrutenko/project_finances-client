#include "imenu.hpp"
#include "ioption.hpp"


IMenu::IMenu(const MenuBar *mbar)
    : mMenuBar{mbar} { }

void IMenu::show(stf::Renderer &renderer)
{
    renderer.drawLine({Width, 1}, {Width, renderer.Size.y}, '|');
    renderer.drawPixel({0, 2 + Selector}, '[');
    renderer.drawPixel({Width - 1, 2 + Selector}, ']');
}

void IMenu::keyHandler(int key)
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
    else if(key >= '1' && key <= '9' && size_t(key - '0' - 1) < mMenuBar->size()) {
        Selector = key - '0' - 1;
    }
}

ActiveMenu::ActiveMenu(const MenuBar *mbar)
    : IMenu(mbar)
{
    for(size_t i = 0; i < mMenuBar->size(); ++i) {
        if(mMenuBar->at(i)->caption().length() > Width)
            Width = mMenuBar->at(i)->caption().length() + 4;
    }
}

void ActiveMenu::show(stf::Renderer &renderer)
{
    for(size_t i = 0, it = 0; i < mMenuBar->size(); ++i) {
        renderer.draw({1, 2 + it++}, "%d.%s", it, mMenuBar->at(i)->caption().c_str());
    }
    IMenu::show(renderer);
}

bool ActiveMenu::isActive() const
{
    return true;
}

InactiveMenu::InactiveMenu(const MenuBar *mbar)
    : IMenu(mbar) { }

void InactiveMenu::show(stf::Renderer &renderer)
{
    for(size_t i = 0, it = 0; i < mMenuBar->size(); ++i) {
        renderer.draw({1, 2 + it++}, "%d", it);
    }
    IMenu::show(renderer);
}

bool InactiveMenu::isActive() const
{
    return false;
}
