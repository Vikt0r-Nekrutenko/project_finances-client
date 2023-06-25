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
    renderer.draw({renderer.Size.x - 14, 2}, "Currency: %s", mModel->currentCurrency().first.c_str());

    int y = 2;

    auto drawInfo = [&](const std::string &a, int v, int ox = 0) {
        renderer.draw({mMenuBar->Width + 1 + ox, y++}, (a+"%m.00 %s").c_str(), int(float(v) / mModel->currentCurrency().second), mModel->currentCurrency().first.c_str());
    };

    auto drawColoredInfo = [&](const std::string &a, int v, int ox = 0) {
        renderer.draw({mMenuBar->Width + 1 + ox, y++}, (a + (v > 0 ? "%CG%m.00%CD %s" : "%CR%m.00%CD %s")).c_str(), int(float(v) / mModel->currentCurrency().second), mModel->currentCurrency().first.c_str());
    };

    drawInfo("Earn:......", mModel->totalEarn());
    drawInfo("Deposits:..", mModel->totalDeposits());
    drawInfo("Debts:.....", mModel->totalDebts());
//    renderer.draw({mMenuBar->Width + 1, y++}, "Earn:......%m.00 %s", int(float(mModel->totalEarn()) / mModel->currentCurrency().second), mModel->currentCurrency().first.c_str());
//    renderer.draw({mMenuBar->Width + 1, y++}, "Deposits:..%m.00 UAH", mModel->totalDeposits());
//    renderer.draw({mMenuBar->Width + 1, y++}, "Debts:.....%m.00 UAH", mModel->totalDebts());

    ++y;
    renderer.drawText({mMenuBar->Width + 1, y++}, "P&Ls:");
    drawColoredInfo("Today....", mModel->todayPnL());
    drawColoredInfo("Monthly..", mModel->monthlyPnL());
    drawColoredInfo("Year.....", mModel->yearPnL());
    drawColoredInfo("Total....", mModel->totalPnL());
//    renderer.draw({mMenuBar->Width + 1, y++}, (mModel->todayPnL()   > 0 ? "Today....%CG%m.00 UAH%CD" : "Today....%CR%m.00 UAH%CD"), mModel->todayPnL());
//    renderer.draw({mMenuBar->Width + 1, y++}, (mModel->monthlyPnL() > 0 ? "Monthly..%CG%m.00 UAH%CD" : "Monthly..%CR%m.00 UAH%CD"), mModel->monthlyPnL());
//    renderer.draw({mMenuBar->Width + 1, y++}, (mModel->yearPnL()    > 0 ? "Year.....%CG%m.00 UAH%CD" : "Year.....%CR%m.00 UAH%CD"), mModel->yearPnL());
//    renderer.draw({mMenuBar->Width + 1, y++}, (mModel->totalPnL()   > 0 ? "Total....%CG%m.00 UAH%CD" : "Total....%CR%m.00 UAH%CD"), mModel->totalPnL());

    ++y;
    renderer.drawText({mMenuBar->Width + 1, y++}, "Favorite categories(by current month):");
    for(const auto &category : mModel->favoriteCategories()) {
        renderer.drawLine({mMenuBar->Width + 1, y}, {mMenuBar->Width + 15, y}, '.');
        renderer.draw({mMenuBar->Width + 1, y}, "%s:", category.first.c_str());
        drawColoredInfo("", category.second, 15);
//        renderer.draw({mMenuBar->Width + 15, y++}, (category.second > 0 ? "%CG%m.00 UAH%CD" : "%CR%m.00 UAH%CD"), category.second);
    }

    ++y;
    renderer.drawText({mMenuBar->Width + 1, y++}, "Min & Max loss(by current month):");
    drawColoredInfo((mModel->minMaxLoss().first.first+": "), mModel->minMaxLoss().first.second);
    drawColoredInfo((mModel->minMaxLoss().second.first+": "), mModel->minMaxLoss().second.second);
//    renderer.draw({mMenuBar->Width + 1, y++}, (mModel->minMaxLoss().first.second > 0 ? "%s: %CG%m.00 UAH%CD" : "%s: %CR%m.00 UAH%CD"), mModel->minMaxLoss().first.first.c_str(), mModel->minMaxLoss().first.second);
//    renderer.draw({mMenuBar->Width + 1, y++}, (mModel->minMaxLoss().second.second > 0 ? "%s: %CG%m.00 UAH%CD" : "%s: %CR%m.00 UAH%CD"), mModel->minMaxLoss().second.first.c_str(), mModel->minMaxLoss().second.second);
}

IView *MainView::keyHandler(int key)
{
    if(key == 'c')
        mModel->switchCurrency();
    switchMenuBar(key);
    return mMenuBar->keyHandler(this, key);
}
