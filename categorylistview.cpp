#include "categorylistview.hpp"
#include "appmodel.hpp"
#include "menuview.hpp"

CategoryListView::CategoryListView(AppModel *model)
    : ModelViewWithInputField(model) {}

void CategoryListView::show(stf::Renderer &renderer)
{
    AppModel *app = static_cast<AppModel*>(m_model);

    if(mOption == 0) {
        renderer.drawText({0, 2}, "Choose an option:");
        renderer.drawText({0, 3}, "1.Add new category.");
        renderer.drawText({0, 4}, "2.Delete category.");
        renderer.drawText({0, 5}, "q.Back to menu.");
    } else if(mOption == 1) {
        renderer.drawText({0, 2}, "Type 'name type' or 'q' to step back:");
        renderer.drawText({0, 3}, ">> ");
        renderer.drawText({3, 3}, mInput.c_str());
    } else if(mOption == 2) {
        renderer.drawText({0, 2}, "Type 'id' or 'q' to step back:");
        renderer.drawText({0, 3}, ">> ");
        renderer.drawText({3, 3}, mInput.c_str());
    }

    renderer.drawText({0, 7}, "Your categories:");
    for(int i = 0; i < 59; ++i)
        renderer.drawPixel({i, 8}, '-');

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

void CategoryListView::onEnterHandler()
{
    switch (mOption) {
    case 1: {
        int delim = mInput.find(" ");
        std::string name = mInput.substr(0, delim);
        mInput.erase(0, delim + 1);

        delim = mInput.find(" ");
        std::string type = mInput.substr(0, delim);
        mInput.erase(0, delim + 1);

        static_cast<AppModel*>(m_model)->addNewOperation(name.c_str(), type.c_str(), amount, mInput.c_str());

        break;
    }
    case 2:
        static_cast<AppModel*>(m_model)->deleteOperation(std::stoi(mInput) - 1);
        break;
    };
}

stf::smv::IView *CategoryListView::keyEventsHandler(const int key)
{
    if(mOption == 0) {
        switch (key) {
        case '1':
        case '2':
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