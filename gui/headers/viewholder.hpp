#ifndef VIEWHOLDER_HPP
#define VIEWHOLDER_HPP

#include "mainview.hpp"
#include "depositsview.hpp"
#include "debtsview.hpp"
#include "categoriesview.hpp"
#include "operationsview.hpp"
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
    IView *getAddNewDebtView();
    IView *getChangeAmountView();
    IView *getDeleteDebtView();

    IView *getCategoriesView();
    IView *getAddNewCategoryView();
    IView *getDeleteCategoryView();

    IView *getOperationsView();
    IView *getAddNewOperationView();
    IView *getDeleteOperationView();

private:

    MainView mMainView;
    CloseView mCloseView;

    DepositsView mDepositView;
    input_views::deposits_views::AddNewDepositView mAddNewDepositView;
    input_views::deposits_views::ChangeBalanceView mChangeBalanceView;
    input_views::deposits_views::DeleteDepositView mDeleteDepositView;
    input_views::deposits_views::SelectDepositView mSelectDepositView;

    DebtsView mDebtsView;
    input_views::debts_views::AddNewDebtView mAddNewDebtView;
    input_views::debts_views::ChangeAmountView mChangeAmountView;
    input_views::debts_views::DeleteDebtView mDeleteDebtView;

    CategoriesView mCategoriesView;
    input_views::categories_views::AddNewCategoryView mAddNewCategoryView;
    input_views::categories_views::DeleteCategoryView mDeleteCategoryView;

    OperationsView mOperationsView;
    input_views::operations_views::AddNewOperationView mAddNewOperationView;
    input_views::operations_views::DeleteOperationView mDeleteOperationView;
};

#endif // VIEWHOLDER_HPP
