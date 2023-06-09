#ifndef IMENU_H
#define IMENU_H

#include <vector>

class Option;

using MenuBar = std::vector<Option *>;

class IMenu
{
public:

protected:

    MenuBar mMenuBar;
};

#endif // IMENU_H
