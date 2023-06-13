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

std::string options::debts_view::ChangeName::caption() const
{
    return "Change name";
}

IView *options::debts_view::ChangeName::execute(IView *sender)
{
    return sender->holder()->getChangeNameView();
}
