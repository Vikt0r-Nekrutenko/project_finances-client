#include "debtlistview.hpp"
#include "appmodel.hpp"
#include "menuview.hpp"

DebtListView::DebtListView(AppModel *model)
    : ModelViewWithInputField(model) {}

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

    renderer.drawText({0, 8}, "Your debts:");
    for(int i = 0; i < 59; ++i)
        renderer.drawPixel({i, 9}, '-');

    const auto &debts = app->debts();

    for(int i = 0; i < debts.size(); ++i) {
        const auto &debt = debts.at(i);
        const int y = i + 10;
        renderer.draw({0,  y}, "%d.%s", i + 1, debt.name().toStdString().c_str());
        renderer.draw({27, y}, "%s.00 UAH", std::to_string(debt.amount()).c_str());
    }
}

void DebtListView::onEnterHandler()
{
    switch (mOption) {
    case 1: {
        int delim = mInput.find(" ");
        std::string name = mInput.substr(0, delim);
        mInput.erase(0, delim + 1);

        delim = mInput.find(" ");
        int amount = std::stoi(mInput.substr(0, delim));
        mInput.erase(0, delim + 1);

        static_cast<AppModel*>(m_model)->addNewDebt(name.c_str(), amount);

        break;
    }
    case 2:
        static_cast<AppModel*>(m_model)->deleteDebt(std::stoi(mInput) - 1);
        break;
    case 3: {
        int delim = mInput.find(" ");
        int id = std::stoi(mInput.substr(0, delim)) - 1;
        mInput.erase(0, delim + 1);

        delim = mInput.find(" ");
        std::string name = mInput.substr(0, delim);
        mInput.erase(0, delim + 1);

        delim = mInput.find(" ");
        int amount = std::stoi(mInput.substr(0, delim));
        mInput.erase(0, delim + 1);

        static_cast<AppModel*>(m_model)->changeDebt(id, name.c_str(), amount);

        break;
    }

    };
}

stf::smv::IView *DebtListView::keyEventsHandler(const int key)
{
    if(mOption == 0) {
        switch (key) {
        case '1':
        case '2':
        case '3':
            mOption = key - '0';
            break;
        case 'q':
            return new MenuView(static_cast<AppModel*>(m_model));
        }
    } else {
        try {
            inputHandler(key);
        } catch(const std::exception &msg) {
            stf::Renderer::log << stf::endl << msg.what();
        }
    }
    return this;
}
