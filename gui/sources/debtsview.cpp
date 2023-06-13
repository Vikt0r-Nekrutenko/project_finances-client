#include "debtsview.hpp"
#include "appmodel.hpp"
#include "ioption.hpp"


DebtsView::DebtsView(AppModel *model, ViewHolder *holder)
    : IView{model, holder}
{
    mOptionsList.insert(mOptionsList.end(), {
                                             new options::BackToStartView,
                                             new options::main_view::Exit
                                            });
    mActiveMenuBar->recalculateBarWidth();
}

void DebtsView::show(stf::Renderer &renderer)
{
    IView::show(renderer);
    mMenuBar->show(renderer);
    drawLogItem(renderer, mMenuBar->Width);

    int index = 1;
    for(const auto &debt : mModel->Debts.debts()) {
        renderer.drawLine({mMenuBar->Width +  1, 1 + index}, {renderer.Size.x - 1, 1 + index}, '.');
        renderer.draw({mMenuBar->Width +  1, 1 + index}, "%d.%s", index, debt.name().c_str());
        renderer.draw({mMenuBar->Width + 15, 1 + index}, "%m.00 UAH", debt.amount());
        ++index;
    }
}

IView *DebtsView::keyHandler(int key)
{
    switchMenuBar(key);
    return mMenuBar->keyHandler(this, key);
}
