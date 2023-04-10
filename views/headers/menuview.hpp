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

private:

    stf::Sprite mMainStatsTable = stf::Sprite("sprs/main_stats.spr");
    stf::Sprite mPnLStatsTable = stf::Sprite("sprs/pnl_stats.spr");
    stf::Sprite mLossesTable = stf::Sprite("sprs/losses.spr");
};

#endif // MENUVIEW_HPP
