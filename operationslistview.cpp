#include "operationslistview.hpp"
#include "appmodel.hpp"
#include "menuview.hpp"

OperationsListView::OperationsListView(AppModel *model)
    : ModelViewWithInputField(model) {}

void OperationsListView::show(stf::Renderer &renderer)
{

}

void OperationsListView::onEnterHandler()
{

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
