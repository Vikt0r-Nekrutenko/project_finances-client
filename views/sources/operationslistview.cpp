#include "operationslistview.hpp"
#include "appmodel.hpp"
#include "operationhandler.hpp"

OperationsListView::OperationsListView(AppModel *model)
    : ModelViewWithInputField(model)
{
    mMenu.push_back(new AddNewOperationHandler);
    mOptrionsCount = 9;
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
//    renderer.drawText({0, 3}, "1.Add new operation.");
//    renderer.drawText({0, 4}, "2.Delete operation.");
//    renderer.drawText({0, 5}, "3.Change operation.");
//    renderer.drawText({0, 6}, "4.Lend operation.");
//    renderer.drawText({0, 7}, "5.Repay operation.");
//    renderer.drawText({0, 8}, "6.Select list.");
//    renderer.drawText({0, 10}, "Add operations Presets:");
//    renderer.drawText({0, 11}, "7.Today PrivatBank.");
//    renderer.drawText({0, 12}, "8.Today PrivatBank Lend.");
//    renderer.drawText({0, 13}, "9.Today PrivatBank Repay.");
//    renderer.drawText({0, 14}, "q.Back to menu.");
    for(size_t i = 0; i < mMenu.size(); ++i)
        renderer.draw({0, 3+i}, "%d.%s", i + 1,  mMenu.at(i)->caption());

    if(mOption)
        renderer.drawText({0, InputInfoY}, mMenu.at(mOption - 1)->operationFieldsInfo());

    renderer.drawText({BeginListX, BeginListY}, "Your operations:");

    const auto &operations = app->operationsByMonth();
    const int listHeinght = operations.size();

    for(int i = operations.size() - 1; i >= 0; --i) {
        const auto &operation = operations.at(i);
        const int y = std::abs(i - listHeinght) + BeginListY;
        if(y >= int(stf::Renderer::log.y() - 1))
            continue;

        for(int j = BeginListX; j < renderer.Size.x; ++j)
            renderer.drawPixel({j, y}, '.');

        renderer.draw({BeginListX,  y}, "[%d].%s...%s", operation.id() + 1, operation.date().c_str(), operation.deposit().c_str());
        renderer.draw({BeginListX + 31, y}, "%m.00 UAH", operation.amount());
        renderer.draw({BeginListX + 47, y}, "%s", operation.category().c_str());
    }
}

void OperationsListView::onEnterHandler()
{
    auto updateOperationsList = [&](const std::string &date){
        const int year = QDateTime().fromString(date.c_str(), "yyyy-MM-dd").date().year();
        const int month = QDateTime().fromString(date.c_str(), "yyyy-MM-dd").date().month();
        static_cast<AppModel*>(m_model)->getOperationsByMonth(year, month);
    };

    if(mOption)
        mMenu.at(mOption - 1)->handle(static_cast<AppModel *>(m_model), mInput);

    return;

    switch (mOption) {
    case 1: {
        std::string date = getStrFromInput();
        std::string deposit = getStrFromInput();
        int amount = getIntFromInput();
        std::string category = getStrFromInput();

        static_cast<AppModel*>(m_model)->addNewOperation(date.c_str(), deposit.c_str(), amount, category.c_str());
        updateOperationsList(date);
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
        updateOperationsList(date);
        break;
    }
    case 4: {
        std::string date = getStrFromInput();
        std::string deposit = getStrFromInput();
        int amount = getIntFromInput();
        std::string name = getStrFromInput();

        static_cast<AppModel*>(m_model)->addNewLendOperation(date.c_str(), deposit.c_str(), amount, name.c_str());
        updateOperationsList(date);
        break;
    }
    case 5: {
        std::string date = getStrFromInput();
        std::string deposit = getStrFromInput();
        int amount = getIntFromInput();
        std::string name = getStrFromInput();

        static_cast<AppModel*>(m_model)->addNewRepayOperation(date.c_str(), deposit.c_str(), amount, name.c_str());
        updateOperationsList(date);
        break;
    }
    case 6: {
        int year = getIntFromInput();
        int month = getIntFromInput();

        static_cast<AppModel*>(m_model)->getOperationsByMonth(year, month);
        break;
    }
    case 7: {
        int amount = getIntFromInput();
        std::string category = getStrFromInput();

        static_cast<AppModel*>(m_model)->addNewOperation(QDateTime().currentDateTime().toString("yyyy-MM-dd").toStdString().c_str(), "PrivatBank", amount, category.c_str());
        break;
    }
    case 8: {
        int amount = getIntFromInput();
        std::string name = getStrFromInput();

        static_cast<AppModel*>(m_model)->addNewLendOperation(QDateTime().currentDateTime().toString("yyyy-MM-dd").toStdString().c_str(), "PrivatBank", amount, name.c_str());
        break;
    }
    case 9: {
        int amount = getIntFromInput();
        std::string name = getStrFromInput();

        static_cast<AppModel*>(m_model)->addNewRepayOperation(QDateTime().currentDateTime().toString("yyyy-MM-dd").toStdString().c_str(), "PrivatBank", amount, name.c_str());
        break;
    }
    };
}

stf::smv::IView *OperationsListView::keyEventsHandler(const int key)
{
    return ModelViewWithInputField::keyEventsHandler(key);
}
