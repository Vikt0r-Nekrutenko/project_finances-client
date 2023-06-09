#ifndef VIEWHOLDER_HPP
#define VIEWHOLDER_HPP

#include "mainview.hpp"
#include "depositview.hpp"
#include "appmodel.hpp"

class ViewHolder
{
public:

    ViewHolder(AppModel *model)
        : mMainView{model, this},
        mDepositView{model, this}
    {}

    IView *getStartedView()
    {
        return &mMainView;
    }

private:

    MainView mMainView;
    DepositView mDepositView;
};

#endif // VIEWHOLDER_HPP
