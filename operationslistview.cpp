#include "operationslistview.hpp"
#include "appmodel.hpp"

OperationsListView::OperationsListView(AppModel *model)
    : ModelViewWithInputField(model)
{
    mOptrionsCount = 5;
}

void OperationsListView::show(stf::Renderer &renderer)
{
    AppModel *app = static_cast<AppModel*>(m_model);

    if(mOption == 0) {
        renderer.drawText({0, 2}, "Choose an option:");
        renderer.drawText({0, 3}, "1.Add new operation.");
        renderer.drawText({0, 4}, "2.Delete operation.");
        renderer.drawText({0, 5}, "3.Change operation.");
        renderer.drawText({0, 6}, "4.Lend operation.");
        renderer.drawText({0, 7}, "5.Repay operation.");
        renderer.drawText({0, 8}, "q.Back to menu.");
    } else if(mOption == 1) {
        renderer.drawText({0, 2}, "Type 'date deposit amount category' or 'q' to step back:");
        renderer.drawText({0, 3}, ">> ");
        renderer.drawText({3, 3}, mInput.c_str());
    } else if(mOption == 2) {
        renderer.drawText({0, 2}, "Type 'id' or 'q' to step back:");
        renderer.drawText({0, 3}, ">> ");
        renderer.drawText({3, 3}, mInput.c_str());
    } else if(mOption == 3) {
        renderer.drawText({0, 2}, "Type 'id date deposit amount category' or 'q' to step back:");
        renderer.drawText({0, 3}, ">> ");
        renderer.drawText({3, 3}, mInput.c_str());
    } else if(mOption == 4) {
        renderer.drawText({0, 2}, "Type 'date deposit amount name' or 'q' to step back:");
        renderer.drawText({0, 3}, ">> ");
        renderer.drawText({3, 3}, mInput.c_str());
    } else if(mOption == 5) {
        renderer.drawText({0, 2}, "Type 'date deposit amount name' or 'q' to step back:");
        renderer.drawText({0, 3}, ">> ");
        renderer.drawText({3, 3}, mInput.c_str());
    }

    renderer.drawText({BeginListX, BeginListY}, "Your operations:");

    const auto &operations = app->operationsByCurrentMonth();
    const int listHeinght = operations.size();

    for(int i = operations.size() - 1; i >= 0; --i) {
        const auto &operation = operations.at(i);
        const int y = std::abs(i - listHeinght) + BeginListY;
        if(y >= int(stf::Renderer::log.y() - 1))
            continue;

        for(int j = BeginListX; j < renderer.Size.x; ++j)
            renderer.drawPixel({j, y}, '.');

        renderer.draw({BeginListX,  y}, "[%d].%s...%s", operation.id() + 1, operation.date().toStdString().c_str(), operation.deposit().toStdString().c_str());
        renderer.draw({BeginListX + 31, y}, "%m.00 UAH", operation.amount());
        renderer.draw({BeginListX + 47, y}, "%s", operation.category().toStdString().c_str());
    }

    ModelViewWithInputField::show(renderer);
}

void OperationsListView::onEnterHandler()
{
    switch (mOption) {
    case 1: {
        std::string date = getStrFromInput();
        std::string deposit = getStrFromInput();
        int amount = getIntFromInput();
        std::string category = getStrFromInput();

        static_cast<AppModel*>(m_model)->addNewOperation(date.c_str(), deposit.c_str(), amount, category.c_str());
        break;
    }
    case 2: {
        int id = getIntFromInput() - 1;
        static_cast<AppModel*>(m_model)->deleteOperation(id);
        break;
    }
    case 3: {
        int id = getIntFromInput() - 1;
        std::string date = getStrFromInput();
        std::string deposit = getStrFromInput();
        int amount = getIntFromInput();
        std::string category = getStrFromInput();

        static_cast<AppModel*>(m_model)->changeOperation(id, date.c_str(), deposit.c_str(), amount, category.c_str());
        break;
    }
    case 4: {
        std::string date = getStrFromInput();
        std::string deposit = getStrFromInput();
        int amount = getIntFromInput();
        std::string name = getStrFromInput();

        static_cast<AppModel*>(m_model)->addNewLendOperation(date.c_str(), deposit.c_str(), amount, name.c_str());
        break;
    }
    case 5: {
        std::string date = getStrFromInput();
        std::string deposit = getStrFromInput();
        int amount = getIntFromInput();
        std::string name = getStrFromInput();

        static_cast<AppModel*>(m_model)->addNewRepayOperation(date.c_str(), deposit.c_str(), amount, name.c_str());
        break;
    }};
}

stf::smv::IView *OperationsListView::keyEventsHandler(const int key)
{
    return ModelViewWithInputField::keyEventsHandler(key);
}
