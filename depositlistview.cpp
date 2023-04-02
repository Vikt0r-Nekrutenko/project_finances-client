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
        renderer.drawText({0, 3 + i}, deposits.at(i).name().toStdString().c_str());
        renderer.draw({15, 3 + i}, "- %s.00 UAH", std::to_string(deposits.at(i).balance()).c_str());
    }

    renderer.drawText({0, 3 + i + 1}, "Choose an option:");
    renderer.drawText({0, 3 + i + 2}, "1.Add new deposit.");
    renderer.drawText({0, 3 + i + 3}, "2.Delete deposit.");
    renderer.drawText({0, 3 + i + 4}, "q.Delete deposit.");
}

stf::smv::IView *DepositListView::keyEventsHandler(const int key)
{
    switch(key) {
    case 'q': return new MenuView(static_cast<AppModel*>(m_model));
    }
    return this;
}
