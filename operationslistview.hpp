#ifndef OPERATIONSLISTVIEW_HPP
#define OPERATIONSLISTVIEW_HPP

#include "modelviewwithinputfield.hpp"

class AppModel;

class OperationsListView : public ModelViewWithInputField
{
public:
    OperationsListView(AppModel *model);
};

#endif // OPERATIONSLISTVIEW_HPP
