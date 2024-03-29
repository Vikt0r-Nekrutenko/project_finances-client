#include "ioption.hpp"
#include "depositsview.hpp"
#include "debtsview.hpp"
#include "mainview.hpp"
#include "operationsview.hpp"
#include "categoriesview.hpp"


std::string options::main_view::Deposits::caption() const
{
    return "Deposits";
}

IView *options::main_view::Deposits::execute(IView *sender)
{
    return new DepositsView(sender->model(), sender);
}

std::string options::main_view::Debts::caption() const
{
    return "Debts";
}

IView *options::main_view::Debts::execute(IView *sender)
{
    return new DebtsView(sender->model(), sender);
}

std::string options::main_view::Categories::caption() const
{
    return "Categories";
}

IView *options::main_view::Categories::execute(IView *sender)
{
    return new CategoriesView(sender->model(), sender);
}

std::string options::main_view::Exit::caption() const
{
    return "Exit";
}

IView *options::main_view::Exit::execute(IView *sender)
{
    return new CloseView(sender->model());
}

std::string options::deposits_view::AddNewDeposit::caption() const
{
    return "Add new deposit";
}

IView *options::deposits_view::AddNewDeposit::execute(IView *sender)
{
    return new input_views::deposits_views::AddNewDepositView(sender->model(), sender);
}

std::string options::BackToStartView::caption() const
{
    return "Back to start view";
}

IView *options::BackToStartView::execute(IView *sender)
{
    return new MainView(sender->model());
}

std::string options::deposits_view::ChangeBalance::caption() const
{
    return "Change balance";
}

IView *options::deposits_view::ChangeBalance::execute(IView *sender)
{
    return new input_views::deposits_views::ChangeBalanceView(sender->model(), sender);
}

std::string options::deposits_view::DeleteDeposit::caption() const
{
    return "Delete deposit";
}

IView *options::deposits_view::DeleteDeposit::execute(IView *sender)
{
    return new input_views::deposits_views::DeleteDepositView(sender->model(), sender);
}

std::string options::deposits_view::SelectDeposit::caption() const
{
    return "Select deposit";
}

IView *options::deposits_view::SelectDeposit::execute(IView *sender)
{
    return new input_views::deposits_views::SelectDepositView(sender->model(), sender);
}

std::string options::debts_view::AddNewDebt::caption() const
{
    return "Add new Debt";
}

IView *options::debts_view::AddNewDebt::execute(IView *sender)
{
    return new input_views::debts_views::AddNewDebtView(sender->model(), sender);
}

std::string options::debts_view::ChangeAmount::caption() const
{
    return "Change amount";
}

IView *options::debts_view::ChangeAmount::execute(IView *sender)
{
    return new input_views::debts_views::ChangeAmountView(sender->model(), sender);
}

std::string options::debts_view::DeleteDebt::caption() const
{
    return "Delete Debt";
}

IView *options::debts_view::DeleteDebt::execute(IView *sender)
{
    return new input_views::debts_views::DeleteDebtView(sender->model(), sender);
}

std::string options::categories_view::AddNewCategory::caption() const
{
    return "Add new Category";
}

IView *options::categories_view::AddNewCategory::execute(IView *sender)
{
    return new input_views::categories_views::AddNewCategoryView(sender->model(), sender);
}

std::string options::categories_view::DeleteCategory::caption() const
{
    return "Delete Category";
}

IView *options::categories_view::DeleteCategory::execute(IView *sender)
{
    return new input_views::categories_views::DeleteCategoryView(sender->model(), sender);
}

std::string options::operations_view::AddNewOperation::caption() const
{
    return "Add new Operation";
}

IView *options::operations_view::AddNewOperation::execute(IView *sender)
{
    return new input_views::operations_views::AddNewOperationView(sender->model(), sender);
}

std::string options::operations_view::AddNewTodayOperation::caption() const
{
    return "New Today Operation";
}

IView *options::operations_view::AddNewTodayOperation::execute(IView *sender)
{
    return new input_views::operations_views::AddNewTodayOperationView(sender->model(), sender);
}

std::string options::operations_view::AddNewTodayLendOrRepay::caption() const
{
    return "New Today Lend or Repay";
}

IView *options::operations_view::AddNewTodayLendOrRepay::execute(IView *sender)
{
    return new input_views::operations_views::AddNewTodayLendOrRepayView(sender->model(), sender);
}

std::string options::operations_view::AddNewLendOrRepay::caption() const
{
    return "New Lend or Repay";
}

IView *options::operations_view::AddNewLendOrRepay::execute(IView *sender)
{
    return new input_views::operations_views::AddNewLendOrRepayView(sender->model(), sender);
}

std::string options::operations_view::DeleteOperation::caption() const
{
    return "Delete Operation";
}

IView *options::operations_view::DeleteOperation::execute(IView *sender)
{
    return new input_views::operations_views::DeleteOperationView(sender->model(), sender);
}

std::string options::operations_view::SelectOperations::caption() const
{
    return "Select Operations";
}

IView *options::operations_view::SelectOperations::execute(IView *sender)
{
    return new input_views::operations_views::SelectOperationsView(sender->model(), sender);
}

std::string options::operations_view::ChangeOperation::caption() const
{
    return "Change Operation";
}

IView *options::operations_view::ChangeOperation::execute(IView *sender)
{
    return new input_views::operations_views::ChangeOperationView(sender->model(), sender);
}

std::string options::operations_view::ChangeDate::caption() const
{
    return "Change date";
}

IView *options::operations_view::ChangeDate::execute(IView *sender)
{
    return new input_views::change_operation_views::ChangeDate(sender->model(), sender);
}

std::string options::operations_view::ChangeAmount::caption() const
{
    return "Change amount";
}

IView *options::operations_view::ChangeAmount::execute(IView *sender)
{
    return new input_views::change_operation_views::ChangeAmount(sender->model(), sender);
}

std::string options::operations_view::ChangeCategory::caption() const
{
    return "Change category";
}

IView *options::operations_view::ChangeCategory::execute(IView *sender)
{
    return new input_views::change_operation_views::ChangeCategory(sender->model(), sender);
}

std::string options::deposits_view::MakeTransfer::caption() const
{
    return "Make transfer";
}

IView *options::deposits_view::MakeTransfer::execute(IView *sender)
{
    return new input_views::deposits_views::MakeTransferView(sender->model(), sender);
}
