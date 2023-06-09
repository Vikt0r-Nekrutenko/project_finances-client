#include "imenu.hpp"


IMenu::IMenu(const MenuBar *mbar)
    : mMenuBar{mbar} { }

void IMenu::show(stf::Renderer &renderer)
{
    renderer.drawLine({Width, 1}, {Width, renderer.Size.y}, '|');
    renderer.drawPixel({0, 2 + Selector}, '[');
    renderer.drawPixel({Width - 1, 2 + Selector}, ']');
}
