#include "ioption.hpp"
#include "iview.hpp"
#include "viewholder.hpp"



std::string options::main_view::Deposits::caption() const
{
    return "Deposits";
}

IView *options::main_view::Deposits::execute(IView *sender)
{
    return sender->holder()->getDepositView();
}

std::string options::main_view::Debts::caption() const
{
    return "Debts";
}

IView *options::main_view::Debts::execute(IView *sender)
{
    return sender->holder()->getDebtsView();
}

std::string options::main_view::Categories::caption() const
{
    return "Categories";
}

IView *options::main_view::Categories::execute(IView *sender)
{
    return sender->holder()->getCategoriesView();
}

std::string options::main_view::Exit::caption() const
{
    return "Exit";
}

IView *options::main_view::Exit::execute(IView *sender)
{
    return sender->holder()->getCloseView();
}

std::string options::deposits_view::AddNewDeposit::caption() const
{
    return "Add new deposit";
}

IView *options::deposits_view::AddNewDeposit::execute(IView *sender)
{
    return sender->holder()->getAddNewDepositView();
}

std::string options::BackToStartView::caption() const
{
    return "Back to start view";
}

IView *options::BackToStartView::execute(IView *sender)
{
    return sender->holder()->getStartView();
}

std::string options::deposits_view::ChangeBalance::caption() const
{
    return "Change balance";
}

IView *options::deposits_view::ChangeBalance::execute(IView *sender)
{
    return sender->holder()->getChangeBalanceView();
}

std::string options::deposits_view::DeleteDeposit::caption() const
{
    return "Delete deposit";
}

IView *options::deposits_view::DeleteDeposit::execute(IView *sender)
{
    return sender->holder()->getDeleteDepositView();
}

std::string options::deposits_view::SelectDeposit::caption() const
{
    return "Select deposit";
}

IView *options::deposits_view::SelectDeposit::execute(IView *sender)
{
    return sender->holder()->getSelectDepositView();
}

std::string options::debts_view::AddNewDebt::caption() const
{
    return "Add new Debt";
}

IView *options::debts_view::AddNewDebt::execute(IView *sender)
{
    return sender->holder()->getAddNewDebtView();
}

std::string options::debts_view::ChangeAmount::caption() const
{
    return "Change amount";
}

IView *options::debts_view::ChangeAmount::execute(IView *sender)
{
    return sender->holder()->getChangeAmountView();
}

std::string options::debts_view::DeleteDebt::caption() const
{
    return "Delete Debt";
}

IView *options::debts_view::DeleteDebt::execute(IView *sender)
{
    return sender->holder()->getDeleteDebtView();
}

std::string options::categories_view::AddNewCategory::caption() const
{
    return "Add new Category";
}

IView *options::categories_view::AddNewCategory::execute(IView *sender)
{
    return sender->holder()->getAddNewCategoryView();
}

std::string options::categories_view::DeleteCategory::caption() const
{
    return "Delete Category";
}

IView *options::categories_view::DeleteCategory::execute(IView *sender)
{
    return sender->holder()->getDeleteCategoryView();
}

std::string options::operations_view::AddNewOperation::caption() const
{
    return "Add new Operation";
}

IView *options::operations_view::AddNewOperation::execute(IView *sender)
{
    return sender->holder()->getAddNewOperationView();
}

std::string options::operations_view::DeleteOperation::caption() const
{
    return "Delete Operation";
}

IView *options::operations_view::DeleteOperation::execute(IView *sender)
{
    return sender->holder()->getDeleteOperationView();
}

std::string options::operations_view::SelectOperations::caption() const
{
    return "Select Operations";
}

IView *options::operations_view::SelectOperations::execute(IView *sender)
{
    return sender->holder()->getSelectOperationsView();
}
