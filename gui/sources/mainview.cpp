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

    int y = 2;
    renderer.draw({mMenuBar->Width + 1, y++}, "Earn:......%m.00 UAH", mModel->totalEarn());
    renderer.draw({mMenuBar->Width + 1, y++}, "Deposits:..%m.00 UAH", mModel->totalDeposits());
    renderer.draw({mMenuBar->Width + 1, y++}, "Debts:.....%m.00 UAH", mModel->totalDebts());

    ++y;
    renderer.drawText({mMenuBar->Width + 1, y++}, "P&Ls:");
    renderer.draw({mMenuBar->Width + 1, y++}, (mModel->todayPnL()   > 0 ? "Today....%CG%m.00 UAH%CD" : "Today....%CR%m.00 UAH%CD"), mModel->todayPnL());
    renderer.draw({mMenuBar->Width + 1, y++}, (mModel->monthlyPnL() > 0 ? "Monthly..%CG%m.00 UAH%CD" : "Monthly..%CR%m.00 UAH%CD"), mModel->monthlyPnL());
    renderer.draw({mMenuBar->Width + 1, y++}, (mModel->yearPnL()    > 0 ? "Year.....%CG%m.00 UAH%CD" : "Year.....%CR%m.00 UAH%CD"), mModel->yearPnL());
    renderer.draw({mMenuBar->Width + 1, y++}, (mModel->totalPnL()   > 0 ? "Total....%CG%m.00 UAH%CD" : "Total....%CR%m.00 UAH%CD"), mModel->totalPnL());

    ++y;
    renderer.drawText({mMenuBar->Width + 1, y++}, "Favorite categories(by current month):");
    for(const auto &category : mModel->favoriteCategories()) {
        renderer.drawLine({mMenuBar->Width + 1, y}, {mMenuBar->Width + 15, y}, '.');
        renderer.draw({mMenuBar->Width + 1, y}, "%s:", category.first.c_str());
        renderer.draw({mMenuBar->Width + 15, y++}, (category.second > 0 ? "%CG%m.00 UAH%CD" : "%CR%m.00 UAH%CD"), category.second);
    }

    ++y;
    renderer.drawText({mMenuBar->Width + 1, y++}, "Min & Max loss(by current month):");
    renderer.draw({mMenuBar->Width + 1, y++}, (mModel->minMaxLoss().first.second > 0 ? "%s: %CG%m.00 UAH%CD" : "%s: %CR%m.00 UAH%CD"), mModel->minMaxLoss().first.first.c_str(), mModel->minMaxLoss().first.second);
    renderer.draw({mMenuBar->Width + 1, y++}, (mModel->minMaxLoss().second.second > 0 ? "%s: %CG%m.00 UAH%CD" : "%s: %CR%m.00 UAH%CD"), mModel->minMaxLoss().second.first.c_str(), mModel->minMaxLoss().second.second);
}

IView *MainView::keyHandler(int key)
{
    switchMenuBar(key);
    return mMenuBar->keyHandler(this, key);
}
