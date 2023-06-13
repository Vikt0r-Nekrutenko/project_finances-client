#include "viewholder.hpp"

ViewHolder::ViewHolder(AppModel *model)
    : mMainView{model, this},
    mCloseView{model, this},
    mDepositView{model, this},
    mAddNewDepositView{model, this},
    mChangeBalanceView{model, this},
    mDeleteDepositView{model, this},
    mSelectDepositView{model, this},
    mDebtsView{model, this},
    mAddNewDebtView{model, this},
    mChangeAmountView{model, this},
    mDeleteDebtView{model, this}
{}

IView *ViewHolder::getStartView()
{
    return &mMainView;
}

IView *ViewHolder::getDepositView()
{
    return &mDepositView;
}

IView *ViewHolder::getCloseView()
{
    return &mCloseView;
}

IView *ViewHolder::getAddNewDepositView()
{
    return &mAddNewDepositView;
}

IView *ViewHolder::getChangeBalanceView()
{
    return &mChangeBalanceView;
}

IView *ViewHolder::getDeleteDepositView()
{
    return &mDeleteDepositView;
}

IView *ViewHolder::getSelectDepositView()
{
    return &mSelectDepositView;
}

IView *ViewHolder::getDebtsView()
{
    return &mDebtsView;
}

IView *ViewHolder::getAddNewDebtView()
{
    return &mAddNewDebtView;
}

IView *ViewHolder::getChangeAmountView()
{
    return &mChangeAmountView;
}

IView *ViewHolder::getDeleteDebtView()
{
    return &mDeleteDebtView;
}
