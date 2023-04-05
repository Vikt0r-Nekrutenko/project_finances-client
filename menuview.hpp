#ifndef MENUVIEW_HPP
#define MENUVIEW_HPP

#include "modelviewwithinputfield.hpp"
#include <QString>
#include <QVector>

class AppModel;

class MenuView : public ModelViewWithInputField
{
public:
    MenuView(AppModel *model);
    void show(stf::Renderer &renderer) override;
    void onEnterHandler() override {};
    stf::smv::IView *keyEventsHandler(const int key) override;
};

#endif // MENUVIEW_HPP
