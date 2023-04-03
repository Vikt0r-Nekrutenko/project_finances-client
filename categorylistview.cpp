#include "categorylistview.hpp"
#include "appmodel.hpp"

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

    renderer.drawText({0, BeginListY - 1}, "Your categories:");

    const auto &categories = app->categories();
    const int listHeinght = categories.size();

    for(int i = categories.size() - 1; i >= 0; --i) {
        const auto &category = categories.at(i);
        const int y = std::abs(i - listHeinght) + BeginListY;
        if(y >= int(stf::Renderer::log.y() - 1))
            continue;
        renderer.draw({0,  y}, "%d.%s -- %s", i + 1, category.name().toStdString().c_str(), category.type().toStdString().c_str());
    }
}

void CategoryListView::onEnterHandler()
{
    switch (mOption) {
    case 1: {
        std::string name = getStrFromInput();
        std::string type = getStrFromInput();

        static_cast<AppModel*>(m_model)->addNewCategory(name.c_str(), type.c_str());
        break;
    }
    case 2: {
        int id = getIntFromInput() - 1;
        static_cast<AppModel*>(m_model)->deleteCategory(id);
        break;
    }};
}

stf::smv::IView *CategoryListView::keyEventsHandler(const int key)
{
    return ModelViewWithInputField::keyEventsHandler(key);
}
