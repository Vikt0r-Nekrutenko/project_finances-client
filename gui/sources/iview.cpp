#include "iview.hpp"
#include "ioption.hpp"
#include "headers/datamodel.hpp"

#include <QDateTime>

IView::IView(AppModel *model, ViewHolder *holder)
    : mModel{model}, mHolder{holder} { }

void IView::show(stf::Renderer &renderer)
{
    renderer.drawLine({0, 1}, {renderer.Size.x - 1, 1}, '-');
}

IViewWithMenuItem::~IViewWithMenuItem()
{
    delete mActiveMenuBar;
    delete mInactiveMenuBar;

    for(size_t i = 0; i < mOptionsList.size(); ++i) {
        delete mOptionsList.at(i);
    }
}

bool IView::isContinue() const
{
    return true;
}

void IViewWithMenuItem::switchMenuBar(int key)
{
    if(key == 'm') {
        if(mMenuBar->isActive())
            mMenuBar = mInactiveMenuBar;
        else
            mMenuBar = mActiveMenuBar;
    }
}

ViewHolder *IView::holder() const
{
    return mHolder;
}

CloseView::CloseView(AppModel *model, ViewHolder *holder)
    : IView(model, holder) { }

bool CloseView::isContinue() const
{
    return false;
}

void IViewWithLogItem::drawLogItem(stf::Renderer &renderer, int menuWidth)
{
    renderer.drawLine({menuWidth + 1, renderer.Size.y - LogHeight - 1},
                      {renderer.Size.x - 1, renderer.Size.y - LogHeight - 1}, '-');

    if(log().size() > size_t(mLastCoreLogSize)) {
        for(size_t i = mLastCoreLogSize; i < log().size(); ++i)
            mLogItem.push_back({QDateTime().currentDateTime().time().toString("hh:mm:ss").toStdString(), *(log().begin() + i)});
    }
    mLastCoreLogSize = log().size();

    for(int i = int(mLogItem.size()) - LogHeight, j = LogHeight; i < int(mLogItem.size()); ++i, --j) {
        if(i < 0)
            continue;
        int offset = 0;
        for(size_t t = 0; t < mLogItem.at(i).size(); ++t) {
            renderer.draw({menuWidth + 1 + offset, renderer.Size.y - j}, "%s", mLogItem.at(i).at(t).c_str());
            offset += mLogItem.at(i).at(t).length() + 1;
        }
    }
}

void IViewWithInputField::drawInputField(stf::Renderer &renderer, int menuWidth, const std::string &title)
{
    renderer.drawLine({menuWidth + 1, renderer.Size.y - 7}, {renderer.Size.x - 1, renderer.Size.y - 7}, '-');
    renderer.drawText({menuWidth + 1, renderer.Size.y - 7}, title.c_str());
    mInputField.show(renderer, menuWidth + 1, renderer.Size.y - 6);
}
