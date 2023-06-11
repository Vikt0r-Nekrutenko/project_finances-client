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
        mAddNewDepositView{model, this}
    {}

    IView *getStartedView()
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

private:

    MainView mMainView;
    DepositsView mDepositView;
    CloseView mCloseView;
    AddNewDepositView mAddNewDepositView;
};

#endif // VIEWHOLDER_HPP
