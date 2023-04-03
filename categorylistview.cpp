#include "categorylistview.hpp"
#include "appmodel.hpp"
#include "menuview.hpp"

CategoryListView::CategoryListView(AppModel *model)
    : ModelViewWithInputField(model)
{
    mOptrionsCount = 2;
}

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

    const auto &categories = app->categories();
    const int listHeinght = categories.size();

    for(int i = categories.size() - 1; i >= 0; --i) {
        const auto &category = categories.at(i);
        const int y = std::abs(i - listHeinght) + 8;
        renderer.draw({0,  y}, "%d.%s -- %s", i + 1, category.name().toStdString().c_str(), category.type().toStdString().c_str());
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

        static_cast<AppModel*>(m_model)->addNewCategory(name.c_str(), type.c_str());

        break;
    }
    case 2:
        static_cast<AppModel*>(m_model)->deleteCategory(std::stoi(mInput) - 1);
        break;
    };
}

stf::smv::IView *CategoryListView::keyEventsHandler(const int key)
{
    return ModelViewWithInputField::keyEventsHandler(key);
}
