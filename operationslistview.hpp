#ifndef OPERATIONSLISTVIEW_HPP
#define OPERATIONSLISTVIEW_HPP

#include "smv/iview.hpp"

class AppModel;

class OperationsListView : public stf::smv::IView
{
public:
    OperationsListView(AppModel *model);
};

#endif // OPERATIONSLISTVIEW_HPP
