#ifndef MENUVIEW_HPP
#define MENUVIEW_HPP

#include <smv/iview.hpp>

class AppModel;

class MenuView : public stf::smv::IView
{
public:
    MenuView(AppModel *model);
    void show(stf::Renderer &renderer) override;

    stf::smv::IView *keyEventsHandler(const int key) override;
};

#endif // MENUVIEW_HPP
