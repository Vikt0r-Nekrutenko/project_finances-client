#ifndef VIEWHOLDER_HPP
#define VIEWHOLDER_HPP

#include "mainview.hpp"
#include "depositsview.hpp"
#include "appmodel.hpp"

class ViewHolder
{
public:

    ViewHolder(AppModel *model)
        : mMainView{model, this},
        mDepositView{model, this},
        mCloseView{model, this},
        mAddNewDepositView{model, this},
        mChangeBalanceView{model, this}
    {}
    
    IView *getStartView()
    {
        return &mMainView;
    }

    IView *getDepositView()
    {
        return &mDepositView;
    }

    IView *getCloseView()
    {
        return &mCloseView;
    }

    IView *getAddNewDepositView()
    {
        return &mAddNewDepositView;
    }

    IView *getChangeBalanceView()
    {
        return &mChangeBalanceView;
    }

    IView *getDeleteDepositView()
    {
        return &mDeleteDepositView;
    }

private:

    MainView mMainView;
    DepositsView mDepositView;
    CloseView mCloseView;

    input_views::deposits_views::AddNewDepositView mAddNewDepositView;
    input_views::deposits_views::ChangeBalanceView mChangeBalanceView;
    input_views::deposits_views::DeleteDepositView mDeleteDepositView;
};

#endif // VIEWHOLDER_HPP
