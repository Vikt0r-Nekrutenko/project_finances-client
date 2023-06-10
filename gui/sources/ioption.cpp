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

IView *options::deposits_view::AddNewDeposit::execute(IView *sender)
{
    return sender->holder()->getAddNewDepositView();
}
