#ifndef IVIEW_HPP
#define IVIEW_HPP

#include "renderer.hpp"
#include "imenu.hpp"

class ViewHolder;
class AppModel;

class IView
{
public:

    IView(AppModel *model, ViewHolder *holder);
    virtual ~IView();
    virtual void show(stf::Renderer &);
    virtual bool isContinue() const;
    IView *keyHandler(int key);

    ViewHolder *holder() const;

protected:

    MenuBar mOptionsList;
    ActiveMenu *mActiveMenuBar = new ActiveMenu{&mOptionsList};
    InactiveMenu *mInactiveMenuBar = new InactiveMenu{&mOptionsList};
    IMenu *mMenuBar = mInactiveMenuBar;
    AppModel *mModel;
    ViewHolder *mHolder;
};

class CloseView : public IView
{
public:

    CloseView(AppModel *model, ViewHolder *holder);
    bool isContinue() const override;
};

class ViewWithLogItem : public IView
{
public:

    static constexpr int LogHeight = 4;

    ViewWithLogItem(AppModel *model, ViewHolder *holder);

    void show(stf::Renderer &renderer) override;
};

#endif // IVIEW_HPP
