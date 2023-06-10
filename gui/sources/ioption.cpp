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
