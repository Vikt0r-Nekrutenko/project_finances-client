#ifndef OPERATIONSLISTVIEW_HPP
#define OPERATIONSLISTVIEW_HPP

#include "modelviewwithinputfield.hpp"
#include "queryresult.hpp"

class AppModel;
class OperationHandler;
class DepositModel;

class OperationsListView : public ModelViewWithInputField
{
public:
    OperationsListView(AppModel *model, DepositModel *deposit);
    ~OperationsListView() override;
    void show(stf::Renderer &renderer) override;
    stf::smv::IView *onEnterHandler() override;
    stf::smv::IView *onQPressHandler() const override;
    stf::smv::IView *keyEventsHandler(const int key) override;

private:

    std::vector<OperationHandler *> mMenu;
    OperationHandlerQuery mOperationsList;
    DepositModel *mDeposit;
};

#endif // OPERATIONSLISTVIEW_HPP
