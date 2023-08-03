#include "mainview.hpp"
#include "ioption.hpp"
#include "appmodel.hpp"



MainView::MainView(AppModel *model)
    : IView{model}
{
    mOptionsList.insert(mOptionsList.end(), {
                                                new options::main_view::Deposits,
                                                new options::main_view::Debts,
                                                new options::main_view::Categories,
                                                new options::main_view::Exit
                                            });
    mActiveMenuBar->recalculateBarWidth();
    mModel->updateStats();
}

void MainView::show(stf::Renderer &renderer)
{
    IView::show(renderer);
    mMenuBar->show(renderer);
    drawLogItem(renderer, mMenuBar->Width);
    renderer.draw({renderer.Size.x - 14, 0}, "Currency: %s", mModel->currentCurrency().first.c_str());

    int y = 2;

    auto drawInfo = [&](const std::string &a, int v, int ox = 0) {
        renderer.draw({mMenuBar->Width + 1 + ox, y++}, (a+"%m.00 %s").c_str(), int(float(v) / mModel->currentCurrency().second), mModel->currentCurrency().first.c_str());
    };

    auto drawColoredInfo = [&](const std::string &a, int v, int ox = 0) {
        return renderer.draw({mMenuBar->Width + 1 + ox, y++}, (a + (v > 0 ? "%CG%m.00%CD %s" : "%CR%m.00%CD %s")).c_str(), int(float(v) / mModel->currentCurrency().second), mModel->currentCurrency().first.c_str());
    };

    drawInfo("Earn:......", mModel->totalEarn());
    drawInfo("Deposits:..", mModel->totalDeposits());
    drawInfo("Debts:.....", mModel->totalDebts());

    ++y;
    renderer.drawText({mMenuBar->Width + 1, y++}, "P&Ls:");
    renderer.draw({mMenuBar->Width + 1, y++}, (std::string("Today....") + (mModel->todayPnL() > 0 ? "%CG%m.00%CD (%CR-%m.00%CD/%CG+%m.00%CD) %s" : "%CR%m.00%CD (%CR-%m.00%CD/%CG+%m.00%CD) %s")).c_str(), mModel->todayPnL(), mModel->todayLoss(), mModel->todayProfit(), mModel->currentCurrency().first.c_str());
    renderer.draw({mMenuBar->Width + 1, y++}, (std::string("Monthly..") + (mModel->monthlyPnL() > 0 ? "%CG%m.00%CD (%CR-%m.00%CD/%CG+%m.00%CD) %s" : "%CR%m.00%CD (%CR-%m.00%CD/%CG+%m.00%CD) %s")).c_str(), mModel->monthlyPnL(), mModel->monthlyLoss(), mModel->monthlyProfit(), mModel->currentCurrency().first.c_str());
    renderer.draw({mMenuBar->Width + 1, y++}, (std::string("Year.....") + (mModel->yearPnL() > 0 ? "%CG%m.00%CD (%CR-%m.00%CD/%CG+%m.00%CD) %s" : "%CR%m.00%CD (%CR-%m.00%CD/%CG+%m.00%CD) %s")).c_str(), mModel->yearPnL(), mModel->yearLoss(), mModel->yearProfit(), mModel->currentCurrency().first.c_str());

    drawColoredInfo("Total....", mModel->totalPnL());

    ++y;
    renderer.drawText({mMenuBar->Width + 1, y++}, "Favorite categories(by current month):");
    for(const auto &category : mModel->favoriteCategories()) {
        renderer.drawLine({mMenuBar->Width + 1, y}, {mMenuBar->Width + 15, y}, '.');
        renderer.draw({mMenuBar->Width + 1, y}, "%s:", category.first.c_str());
        drawColoredInfo("", category.second, 15);
    }

    ++y;
    renderer.drawText({mMenuBar->Width + 1, y++}, "Min & Max loss(by current month):");
    drawColoredInfo((mModel->minMaxLoss().first.first+": "), mModel->minMaxLoss().first.second);
    drawColoredInfo((mModel->minMaxLoss().second.first+": "), mModel->minMaxLoss().second.second);
}

IView *MainView::keyHandler(int key)
{
    if(key == 'c')
        mModel->switchCurrency();
    switchMenuBar(key);
    return mMenuBar->keyHandler(this, key);
}
