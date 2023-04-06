#include "depositlistview.hpp"
#include "appmodel.hpp"

DepositListView::DepositListView(AppModel *model)
    : ModelViewWithInputField(model)
{
    mOptrionsCount = 3;
}

void DepositListView::show(stf::Renderer &renderer)
{
    ModelViewWithInputField::show(renderer);
    AppModel *app = static_cast<AppModel*>(m_model);

    renderer.drawText({0, 2}, "Choose an option:");
    renderer.drawText({0, 3}, "1.Add new deposit.");
    renderer.drawText({0, 4}, "2.Delete deposit.");
    renderer.drawText({0, 5}, "3.Change balance.");
    renderer.drawText({0, 6}, "q.Back to menu.");

    if(mOption == 1) {
        renderer.drawText({0, InputInfoY}, "Type 'name balance' or 'q' to step back:");
    } else if(mOption == 2) {
        renderer.drawText({0, InputInfoY}, "Type deposit id or 'q' to step back:");
    } else if(mOption == 3) {
        renderer.drawText({0, InputInfoY}, "Type 'id balance' or 'q' to step back:");
    }

    renderer.drawText({BeginListX, BeginListY}, "Your deposits:");

    const QVector<DepositModel> &deposits = app->deposits();

    for(int i = 0; i < deposits.size(); ++i) {
        const int y = i + BeginListY + 1;
            if(y >= int(stf::Renderer::log.y() - 1))
                continue;

        for(int j = BeginListX; j < renderer.Size.x; ++j)
            renderer.drawPixel({j, y}, '.');

        renderer.draw({BeginListX, y}, "%d.%s", i+1, deposits.at(i).name().toStdString().c_str());
        renderer.draw({BeginListX + 17, y}, "%m.00 UAH", deposits.at(i).balance());
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