#ifndef DEPOSITVIEW_HPP
#define DEPOSITVIEW_HPP

#include "iview.hpp"

class DepositView : public IView
{
public:
    DepositView(AppModel *model, ViewHolder *holder)
        : IView{model, holder} { }
};

#endif // DEPOSITVIEW_HPP
