#include "debtsview.hpp"


DebtsView::DebtsView(AppModel *model, ViewHolder *holder)
    : IView{model, holder}
{
    mOptionsList.insert(mOptionsList.end(), {
                                            });
    mActiveMenuBar->recalculateBarWidth();
}
