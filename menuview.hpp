#ifndef MENUVIEW_HPP
#define MENUVIEW_HPP

#include <smv/iview.hpp>
#include <QString>
#include <QVector>

class AppModel;

class MenuView : public stf::smv::IView
{
public:
    MenuView(AppModel *model);
    void updateStats();
    void show(stf::Renderer &renderer) override;

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
