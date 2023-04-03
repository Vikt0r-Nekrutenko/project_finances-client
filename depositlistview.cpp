#include "depositlistview.hpp"
#include "appmodel.hpp"

DepositListView::DepositListView(AppModel *model)
    : ModelViewWithInputField(model)
{
    mOptrionsCount = 3;
}

void DepositListView::show(stf::Renderer &renderer)
{
    AppModel *app = static_cast<AppModel*>(m_model);

    if(mOption == 0) {
        renderer.drawText({0, 2}, "Choose an option:");
        renderer.drawText({0, 3}, "1.Add new deposit.");
        renderer.drawText({0, 4}, "2.Delete deposit.");
        renderer.drawText({0, 5}, "3.Change balance.");
        renderer.drawText({0, 6}, "q.Back to menu.");
    } else if(mOption == 1) {
        renderer.drawText({0, 2}, "Type 'name balance' or 'q' to step back:");
        renderer.drawText({0, 3}, ">> ");
        renderer.drawText({3, 3}, mInput.c_str());
    } else if(mOption == 2) {
        renderer.drawText({0, 2}, "Type deposit id or 'q' to step back:");
        renderer.drawText({0, 3}, ">> ");
        renderer.drawText({3, 3}, mInput.c_str());
    } else if(mOption == 3) {
        renderer.drawText({0, 2}, "Type 'id balance' or 'q' to step back:");
        renderer.drawText({0, 3}, ">> ");
        renderer.drawText({3, 3}, mInput.c_str());
    }

    renderer.drawText({0, BeginListY - 1}, "Your deposits:");

    const QVector<DepositModel> &deposits = app->deposits();

    for(int i = 0; i < deposits.size(); ++i) {
        const int y = i + BeginListY + 1;
            if(y >= int(stf::Renderer::log.y() - 1))
                continue;
        renderer.draw({0, y}, "%d.%s", i+1, deposits.at(i).name().toStdString().c_str());
        renderer.draw({17, y}, "- %m.00 UAH", deposits.at(i).balance());
    }
}

void DepositListView::onEnterHandler()
{
    switch (mOption) {
    case 1: {
        std::string name = getStrFromInput();
        int balance = getIntFromInput();
        static_cast<AppModel*>(m_model)->addNewDeposit(name.c_str(), balance);
        break;
    }
    case 2:
        static_cast<AppModel*>(m_model)->deleteDeposit(std::stoi(mInput) - 1);
        break;
    case 3: {
        int id = getIntFromInput() - 1;
        int balance = getIntFromInput();
        static_cast<AppModel*>(m_model)->changeBalance(id, balance);
        break;
    }}
}

stf::smv::IView *DepositListView::keyEventsHandler(const int key)
{
    return ModelViewWithInputField::keyEventsHandler(key);
}
