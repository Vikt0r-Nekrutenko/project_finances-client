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

    mModel->selectFavoriteCategories(0, 1, 2);
    mModel->calcTotalEarn();
    mModel->calcTotalDeposits();
    mModel->calcTotalDebts();
    mModel->calcPnLs();
}

void MainView::show(stf::Renderer &renderer)
{
    IView::show(renderer);
    renderer.draw({mMenuBar->Width + 1, 1}, "Main View");
    mMenuBar->show(renderer);
    drawLogItem(renderer, mMenuBar->Width);

    int y = 2;

    for(const auto &category : mModel->favoriteCategories()) {
        renderer.draw({mMenuBar->Width + 1, y++}, "%s: %m.00 UAH", category.first.c_str(), category.second);
    }
    renderer.draw({mMenuBar->Width + 1, y++}, "Total: %m.00 UAH", mModel->totalEarn());
    renderer.draw({mMenuBar->Width + 1, y++}, "Deposits: %m.00 UAH", mModel->totalDeposits());
    renderer.draw({mMenuBar->Width + 1, y++}, "Debts: %m.00 UAH", mModel->totalDebts());
    renderer.draw({mMenuBar->Width + 1, y++}, "Total PnL: %m.00 UAH", mModel->totalPnL());
    renderer.draw({mMenuBar->Width + 1, y++}, "Today PnL: %m.00 UAH", mModel->todayPnL());
    renderer.draw({mMenuBar->Width + 1, y++}, "Monthly PnL: %m.00 UAH", mModel->monthlyPnL());
    renderer.draw({mMenuBar->Width + 1, y++}, "Year PnL: %m.00 UAH", mModel->yearPnL());
}

IView *MainView::keyHandler(int key)
{
    switchMenuBar(key);
    return mMenuBar->keyHandler(this, key);
}
