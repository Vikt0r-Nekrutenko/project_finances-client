#include "mainview.hpp"
#include "ioption.hpp"



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
}

void MainView::show(stf::Renderer &renderer)
{
    IView::show(renderer);
    renderer.draw({mMenuBar->Width + 1, 1}, "Main View");
    mMenuBar->show(renderer);
    drawLogItem(renderer, mMenuBar->Width);
}

IView *MainView::keyHandler(int key)
{
    switchMenuBar(key);
    return mMenuBar->keyHandler(this, key);
}
