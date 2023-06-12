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
