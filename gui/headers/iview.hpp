#ifndef IVIEW_HPP
#define IVIEW_HPP

#include "renderer.hpp"
#include "imenu.hpp"
#include "iinputfield.hpp"

class ViewHolder;
class AppModel;

class IView
{
public:

    IView(AppModel *model, ViewHolder *holder);
    virtual ~IView() = default;
    virtual void show(stf::Renderer &) = 0;
    virtual IView *keyHandler(int key) = 0;
    virtual bool isContinue() const;

    ViewHolder *holder() const;

protected:

    AppModel *mModel;
    ViewHolder *mHolder;
};

class IViewWithMenuItem
{
public:

    virtual ~IViewWithMenuItem();

    void switchMenuBar(int key);

protected:

    MenuBar mOptionsList;
    ActiveMenu *mActiveMenuBar = new ActiveMenu{&mOptionsList};
    InactiveMenu *mInactiveMenuBar = new InactiveMenu{&mOptionsList};
    IMenu *mMenuBar = mInactiveMenuBar;
};

class CloseView : public IView
{
public:

    CloseView(AppModel *model, ViewHolder *holder);
    bool isContinue() const override;
    void show(stf::Renderer &) override {}
    IView *keyHandler(int) override {return this;}
};

class IViewWithLogItem
{
public:

    static constexpr int LogHeight = 4;

    void drawLogItem(stf::Renderer &renderer, int menuWidth);
};

class IViewWithInputField
{
public:

    void drawInputField(stf::Renderer &renderer, int menuWidth);

protected:

    ActiveInputField *mActiveInputField = new ActiveInputField;
    InactiveInputField *mInactiveInputField = new InactiveInputField;
    IInputField *mInputField = mInactiveInputField;
};

#endif // IVIEW_HPP
