#include "closeview.hpp"

CloseView::CloseView(AppModel *model)
    : stf::smv::IView(model) { }

bool CloseView::isContinue() const
{
    return false;
}

void CloseView::show(stf::Renderer &) { }

stf::smv::IView *CloseView::update(const float)
{
    return this;
}
