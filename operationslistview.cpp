#include "operationslistview.hpp"
#include "appmodel.hpp"
#include "menuview.hpp"

OperationsListView::OperationsListView(AppModel *model)
    : ModelViewWithInputField(model) {}

void OperationsListView::show(stf::Renderer &renderer)
{
    AppModel *app = static_cast<AppModel*>(m_model);

    if(mOption == 0) {
        renderer.drawText({0, 2}, "Choose an option:");
        renderer.drawText({0, 3}, "1.Add new operation.");
        renderer.drawText({0, 4}, "2.Delete operation.");
        renderer.drawText({0, 5}, "3.Change operation.");
        renderer.drawText({0, 6}, "q.Back to menu.");
    } else if(mOption == 1) {
        renderer.drawText({0, 2}, "Type 'date deposit amount category' or 'q' to step back:");
        renderer.drawText({0, 3}, ">> ");
        renderer.drawText({3, 3}, mInput.c_str());
    }

    renderer.drawText({0, 8}, "Your operations:");
    for(int i = 0; i < 59; ++i)
        renderer.drawPixel({i, 9}, '-');

    const auto &operations = app->operations();
    const int listHeinght = operations.size();

    for(int i = operations.size() - 1; i >= 0; --i) {
        const auto &operation = operations.at(i);
        const int y = std::abs(i - listHeinght) + 9;
        renderer.draw({0,  y}, "%d.%s %s", i + 1, operation.date().toStdString().c_str(), operation.deposit().toStdString().c_str());
        renderer.draw({27, y}, "%s.00 UAH", std::to_string(operation.amount()).c_str());
        renderer.draw({40, y}, "%s", operation.category().toStdString().c_str());
    }

}

void OperationsListView::onEnterHandler()
{
    switch (mOption) {
    case 1: {
        int delim = mInput.find(" ");
        std::string date = mInput.substr(0, delim);
        mInput.erase(0, delim + 1);

        delim = mInput.find(" ");
        std::string deposit = mInput.substr(0, delim);
        mInput.erase(0, delim + 1);

        delim = mInput.find(" ");
        int amount = std::stoi(mInput.substr(0, delim));
        mInput.erase(0, delim + 1);

        static_cast<AppModel*>(m_model)->addNewOperation(date.c_str(), deposit.c_str(), amount, mInput.c_str());

        break;
    }
    };
}

stf::smv::IView *OperationsListView::keyEventsHandler(const int key)
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
