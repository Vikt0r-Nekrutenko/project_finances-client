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
    void updateStats();
    void show(stf::Renderer &renderer) override;
    void onEnterHandler() override {};
    stf::smv::IView *keyEventsHandler(const int key) override;

private:

    QVector<QPair<QString, int>> mFavCats;

    int mSumOfAllEarnOperations = 0,
        mSumOfAllDeposits = 0,
        mTotalPnL = 0,
        mTodayPnL = 0,
        mWeekPnL = 0,
        mMonthPnL = 0,
        mYearPnL = 0;
};

#endif // MENUVIEW_HPP
