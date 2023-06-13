#ifndef VIEWHOLDER_HPP
#define VIEWHOLDER_HPP

#include "mainview.hpp"
#include "depositsview.hpp"
#include "debtsview.hpp"
#include "appmodel.hpp"

class ViewHolder
{
public:

    ViewHolder(AppModel *model);
    
    IView *getStartView();
    IView *getCloseView();

    IView *getDepositView();
    IView *getAddNewDepositView();
    IView *getChangeBalanceView();
    IView *getDeleteDepositView();
    IView *getSelectDepositView();

    IView *getDebtsView();

private:

    MainView mMainView;
    CloseView mCloseView;

    DepositsView mDepositView;
    input_views::deposits_views::AddNewDepositView mAddNewDepositView;
    input_views::deposits_views::ChangeBalanceView mChangeBalanceView;
    input_views::deposits_views::DeleteDepositView mDeleteDepositView;
    input_views::deposits_views::SelectDepositView mSelectDepositView;

    DebtsView mDebtsView;
};

#endif // VIEWHOLDER_HPP
