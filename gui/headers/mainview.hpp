#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include "iview.hpp"

class MainView : public IView
{
public:
    MainView(AppModel *model, ViewHolder *holder)
        : IView{model, holder} { }
};

#endif // MAINVIEW_HPP
