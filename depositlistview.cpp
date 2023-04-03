#include "depositlistview.hpp"
#include "appmodel.hpp"
#include "menuview.hpp"

DepositListView::DepositListView(AppModel *model)
    : ModelViewWithInputField(model)
{
    mOptrionsCount = 3;
}

void DepositListView::show(stf::Renderer &renderer)
{
    AppModel *app = static_cast<AppModel*>(m_model);

    renderer.drawText({0,2}, "Your deposits:");

    const QVector<DepositModel> &deposits = app->deposits();
    int i = 0;
    for(; i < deposits.size(); ++i) {
        renderer.draw({0, 3 + i}, "%d.%s", i+1, deposits.at(i).name().toStdString().c_str());
        renderer.draw({17, 3 + i}, "- %s.00 UAH", std::to_string(deposits.at(i).balance()).c_str());
    }

    if(mOption == 0) {
        renderer.drawText({0, 3 + i + 1}, "Choose an option:");
        renderer.drawText({0, 3 + i + 2}, "1.Add new deposit.");
        renderer.drawText({0, 3 + i + 3}, "2.Delete deposit.");
        renderer.drawText({0, 3 + i + 4}, "3.Change balance.");
        renderer.drawText({0, 3 + i + 5}, "q.Back to menu.");
    } else if(mOption == 1) {
        renderer.drawText({0, 3 + i + 1}, "Type 'name balance' or 'q' to step back:");
        renderer.drawText({0, 3 + i + 2}, ">> ");
        renderer.drawText({3, 3 + i + 2}, mInput.c_str());
    } else if(mOption == 2) {
        renderer.drawText({0, 3 + i + 1}, "Type deposit id or 'q' to step back:");
        renderer.drawText({0, 3 + i + 2}, ">> ");
        renderer.drawText({3, 3 + i + 2}, mInput.c_str());
    } else if(mOption == 3) {
        renderer.drawText({0, 3 + i + 1}, "Type 'id balance' or 'q' to step back:");
        renderer.drawText({0, 3 + i + 2}, ">> ");
        renderer.drawText({3, 3 + i + 2}, mInput.c_str());
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
