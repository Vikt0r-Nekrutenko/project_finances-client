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

ActiveMenu::ActiveMenu(const MenuBar *mbar)
    : IMenu(mbar) { }

void ActiveMenu::show(stf::Renderer &renderer)
{
    for(size_t i = 0, it = 0; i < mMenuBar->size(); ++i) {
        renderer.draw({1, 2 + it++}, "%d.%s", it, mMenuBar->at(i)->caption().c_str());
    }
    IMenu::show(renderer);
}
