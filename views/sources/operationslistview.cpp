#include "operationslistview.hpp"
#include "appmodel.hpp"
#include "depositlistview.hpp"
#include "operationhandler.hpp"
#include "queryresult.hpp"

OperationsListView::OperationsListView(AppModel *model, DepositModel *deposit)
    : ModelViewWithInputField(model), mOperationsList{model}, mDeposit{deposit}
{
    mMenu.insert(mMenu.end(), {
                     new AddNewOperationHandler(deposit),
                     new DeleteOperationHandler(deposit),
                     new ChangeOperationHandler(deposit),
                     new AddLendOperationHandler(deposit),
                     new AddRepayOperationHandler(deposit),
                     new AddNewTodayOperationHandler(deposit),
                     new AddNewTodayLendOperationHandler(deposit),
                     new AddNewTodayRepayOperationHandler(deposit),
                 });
    mOptrionsCount = 8;

    mOperationsList.select().filterByCurrentYear().filterByCurrentMonth().filterByDeposit(mDeposit->name());
}

OperationsListView::~OperationsListView()
{
    for(auto option : mMenu)
        delete option;
}

void OperationsListView::show(stf::Renderer &renderer)
{
    ModelViewWithInputField::show(renderer);

    renderer.drawText({0, 2}, "Choose an option:");
    renderer.drawText({0, 3}, "1.Select a list.");
    for(size_t i = 0; i < mMenu.size(); ++i)
        renderer.draw({0, 4+i}, "%d.%s", i + 2,  mMenu.at(i)->caption());

    if(mOption == 1) {
        renderer.drawText({0, InputInfoY}, "Type 'year month'");
    } else if(mOption > 1)
        renderer.drawText({0, InputInfoY}, mMenu.at(mOption - 2)->operationFieldsInfo());

    renderer.drawText({BeginListX, BeginListY}, "Your operations:");

    const int listHeinght = mOperationsList.size();
    int y = 0, i = mOperationsList.size() - 1;

    for(auto it = mOperationsList.rbegin(); it != mOperationsList.rend() && y < InputInfoY - 1; ++it, --i){
        const auto &operation = **it;
        y = std::abs(i - listHeinght) + BeginListY;
        if(y >= int(stf::Renderer::log.y() - 1))
            continue;

        for(int j = BeginListX; j < renderer.Size.x; ++j)
            renderer.drawPixel({j, y}, '.');

        renderer.draw({BeginListX,  y}, "[%d].%s...%s", operation.id() + 1, operation.date().c_str(), operation.deposit().c_str());
        renderer.draw({BeginListX + 31, y}, "%m.00 UAH", operation.amount());
        renderer.draw({BeginListX + 47, y}, "%s", operation.category().c_str());
    }
}

stf::smv::IView *OperationsListView::onEnterHandler()
{
    if(mOption == 1) {
        int year = getIntFromInput();
        int month = getIntFromInput();
        mOperationsList.select().filterByYear(year).filterByMonth(month).filterByDeposit(mDeposit->name());
    } else if(mOption > 1) {
        mMenu.at(mOption - 1)->handle(static_cast<AppModel *>(m_model), mInput);
        mOperationsList.select().filterByCurrentYear().filterByCurrentMonth().filterByDeposit(mDeposit->name());
    }
    return this;
}

stf::smv::IView *OperationsListView::onQPressHandler() const
{
    return new DepositListView(static_cast<AppModel*>(m_model));
}

stf::smv::IView *OperationsListView::keyEventsHandler(const int key)
{
    return ModelViewWithInputField::keyEventsHandler(key);
}
