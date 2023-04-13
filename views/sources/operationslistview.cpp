#include "operationslistview.hpp"
#include "appmodel.hpp"
#include "operationhandler.hpp"

OperationsListView::OperationsListView(AppModel *model, DepositModel *deposit)
    : ModelViewWithInputField(model)
{
    mMenu.insert(mMenu.end(), {
                     new AddNewOperationHandler(deposit),
                     new DeleteOperationHandler(deposit),
                     new ChangeOperationHandler(deposit),
                     new AddLendOperationHandler(deposit),
                     new AddRepayOperationHandler(deposit),
                     new SelectListOperationHandler(deposit),
                     new AddNewTodayOperationHandler(deposit),
                     new AddNewTodayLendOperationHandler(deposit),
                     new AddNewTodayRepayOperationHandler(deposit),
                 });
    mOptrionsCount = 6;
}

OperationsListView::~OperationsListView()
{
    for(auto option : mMenu)
        delete option;
}

void OperationsListView::show(stf::Renderer &renderer)
{
    ModelViewWithInputField::show(renderer);
    AppModel *app = static_cast<AppModel*>(m_model);

    renderer.drawText({0, 2}, "Choose an option:");
    for(size_t i = 0; i < mMenu.size(); ++i)
        renderer.draw({0, 3+i}, "%d.%s", i + 1,  mMenu.at(i)->caption());

    if(mOption)
        renderer.drawText({0, InputInfoY}, mMenu.at(mOption - 1)->operationFieldsInfo());

    renderer.drawText({BeginListX, BeginListY}, "Your operations:");

    const auto &operations = app->operationsByMonth();
    const int listHeinght = operations.size();

    int y = 0;
    for(int i = operations.size() - 1; i >= 0 && y < InputInfoY - 1; --i) {
        const auto &operation = operations.at(i);
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
    if(mOption)
        mMenu.at(mOption - 1)->handle(static_cast<AppModel *>(m_model), mInput);
    return this;
}

stf::smv::IView *OperationsListView::keyEventsHandler(const int key)
{
    return ModelViewWithInputField::keyEventsHandler(key);
}
