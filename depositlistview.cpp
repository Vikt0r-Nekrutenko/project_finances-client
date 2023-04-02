#include "depositlistview.hpp"
#include "appmodel.hpp"
#include "menuview.hpp"

DepositListView::DepositListView(AppModel *model)
    : stf::smv::IView(model)
{

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

stf::smv::IView *DepositListView::keyEventsHandler(const int key)
{
    switch (mOption) {
    case 0:
        switch (key) {
        case '1':
        case '2':
        case '3':
            mOption = key - '0';
            break;
        case 'q':
            return new MenuView(static_cast<AppModel*>(m_model));
        }
        break;
    case 1:
        if(key == 'q' && mInput.empty())
            mOption = 0;
        else if(key == 13) {
            mOption = 0;
            int delim = mInput.find(" ");
            std::string name = mInput.substr(0, delim);
            int balance = std::stoi(mInput.erase(0, delim + 1));
            static_cast<AppModel*>(m_model)->addNewDeposit(name.c_str(), balance);
        } else if((key >= '0' && key <= 'z') || key == ' ')
            mInput += key;
        else if(key == 8 && !mInput.empty())
            mInput.pop_back();
        break;
    case 2:
        if(key == 'q')
            mOption = 0;
        else if(key == 13) {
            mOption = 0;
            static_cast<AppModel*>(m_model)->deleteDeposit(std::stoi(mInput) - 1);
        } else if(key >= '0' && key <= '9')
            mInput += key;
        else if(key == 8 && !mInput.empty())
            mInput.pop_back();
        break;
    case 3:
        if(key == 'q' && mInput.empty())
            mOption = 0;
        else if(key == 13) {
            mOption = 0;
            int delim = mInput.find(" ");
            int id = std::stoi(mInput.substr(0, delim)) - 1;
            int balance = std::stoi(mInput.erase(0, delim + 1));
            static_cast<AppModel*>(m_model)->changeBalance(id, balance);
        } else if((key >= '0' && key <= 'z') || key == ' ')
            mInput += key;
        else if(key == 8 && !mInput.empty())
            mInput.pop_back();
        break;
    }
    return this;
}
