#include "iview.hpp"
#include "ioption.hpp"
#include "headers/datamodel.hpp"

#include <QDateTime>

IView::IView(AppModel *model)
    : mModel{model} { }

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

CloseView::CloseView(AppModel *model)
    : IView(model) { }

bool CloseView::isContinue() const
{
    return false;
}

LogItem IViewWithLogItem::mLogItem;
int IViewWithLogItem::mLastCoreLogSize = 0;

void IViewWithLogItem::drawLogItem(stf::Renderer &renderer, int menuWidth)
{
    renderer.drawLine({menuWidth + 1, renderer.Size.y - LogHeight - 1},
                      {renderer.Size.x - 1, renderer.Size.y - LogHeight - 1}, '-');

    if(log().size() > size_t(mLastCoreLogSize)) {
        for(size_t i = mLastCoreLogSize; i < log().size(); ++i)
            mLogItem << *(log().begin() + i) << lendl;
    }
    mLastCoreLogSize = log().size();

    for(int i = int(mLogItem.size() - 1) - LogHeight, j = LogHeight; i < int(mLogItem.size() - 1); ++i, --j) {
        if(i < 0)
            continue;
        int offset = 0;
        for(size_t t = 0; t < mLogItem.at(i).size(); ++t) {
            renderer.draw({menuWidth + 1 + offset, renderer.Size.y - j}, "%s", mLogItem.at(i).at(t).c_str());
            offset += mLogItem.at(i).at(t).length();
        }
    }
}

void IViewWithInputField::drawInputField(stf::Renderer &renderer, int menuWidth, const std::string &title)
{
    renderer.drawLine({menuWidth + 1, renderer.Size.y - 7}, {renderer.Size.x - 1, renderer.Size.y - 7}, '-');
    renderer.drawText({menuWidth + 1, renderer.Size.y - 7}, title.c_str());
    mInputField.show(renderer, menuWidth + 1, renderer.Size.y - 6);
}

IView *IViewWithInputField::onKeyPressHandler(int key, IView *sender, IView *onEscPressView)
{
    mInputField.keyHandler(sender, key);
    if(key == VK_ESCAPE1)
        return onEscPressView;
    else if(key == VK_ENTER1 || key == VK_ENTER2) {
        return onEnterPressHandler();
    }
    return sender;
}
