#include "debtlistview.hpp"
#include "appmodel.hpp"

DebtListView::DebtListView(AppModel *model)
    : ModelViewWithInputField(model)
{
    mOptrionsCount = 3;
}

void DebtListView::show(stf::Renderer &renderer)
{
    AppModel *app = static_cast<AppModel*>(m_model);

    if(mOption == 0) {
        renderer.drawText({0, 2}, "Choose an option:");
        renderer.drawText({0, 3}, "1.Add new debt.");
        renderer.drawText({0, 4}, "2.Delete debt.");
        renderer.drawText({0, 5}, "3.Change debt.");
        renderer.drawText({0, 6}, "q.Back to menu.");
    } else if(mOption == 1) {
        renderer.drawText({0, 2}, "Type 'name amount' or 'q' to step back:");
        renderer.drawText({0, 3}, ">> ");
        renderer.drawText({3, 3}, mInput.c_str());
    } else if(mOption == 2) {
        renderer.drawText({0, 2}, "Type 'id' or 'q' to step back:");
        renderer.drawText({0, 3}, ">> ");
        renderer.drawText({3, 3}, mInput.c_str());
    } else if(mOption == 3) {
        renderer.drawText({0, 2}, "Type 'id name amount' or 'q' to step back:");
        renderer.drawText({0, 3}, ">> ");
        renderer.drawText({3, 3}, mInput.c_str());
    }

    renderer.drawText({BeginListX, BeginListY}, "Your debts:");

    const auto &debts = app->debts();

    for(int i = 0; i < debts.size(); ++i) {
        const auto &debt = debts.at(i);
        const int y = i + BeginListY + 1;
        if(y >= int(stf::Renderer::log.y() - 1))
            continue;

        for(int j = BeginListX; j < renderer.Size.x; ++j)
            renderer.drawPixel({j, y}, '.');

        renderer.draw({BeginListX,  y}, "%d.%s", i + 1, debt.name().toStdString().c_str());
        renderer.draw({BeginListX + 15, y}, "%m.00 UAH", debt.amount());
    }
    ModelViewWithInputField::show(renderer);
}

void DebtListView::onEnterHandler()
{
    switch (mOption) {
    case 1: {
        std::string name = getStrFromInput();
        int amount = getIntFromInput();

        static_cast<AppModel*>(m_model)->addNewDebt(name.c_str(), amount);
        break;
    }
    case 2: {
        int id = getIntFromInput() - 1;
        static_cast<AppModel*>(m_model)->deleteDebt(id);
        break;
    }
    case 3: {
        int id = getIntFromInput() - 1;
        std::string name = getStrFromInput();
        int amount = getIntFromInput();

        static_cast<AppModel*>(m_model)->changeDebt(id, name.c_str(), amount);
        break;
    }};
}

stf::smv::IView *DebtListView::keyEventsHandler(const int key)
{
    return ModelViewWithInputField::keyEventsHandler(key);
}
