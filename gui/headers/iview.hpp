#ifndef IVIEW_HPP
#define IVIEW_HPP

#include "renderer.hpp"
#include "imenu.hpp"
#include "inputfield.hpp"
#include "logitem.hpp"

class ViewHolder;
class AppModel;

class IView
{
public:

    IView(AppModel *model);
    virtual ~IView() = default;
    virtual void show(stf::Renderer &);
    virtual IView *keyHandler(int key) = 0;
    virtual bool isContinue() const;

protected:

    AppModel *mModel;
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

    CloseView(AppModel *model);
    bool isContinue() const override;
    void show(stf::Renderer &) override {}
    IView *keyHandler(int) override {return this;}
};

class ISubView
{
public:

    ISubView(IView *view)
        : mParent{view} { }

protected:

    IView *mParent;
};

class IViewWithLogItem
{
public:

    static constexpr int LogHeight = 4;

    void drawLogItem(stf::Renderer &renderer, int menuWidth);

protected:

    static LogItem mLogItem;
    static int mLastCoreLogSize;
};

class IViewWithInputField
{
public:

    void drawInputField(stf::Renderer &renderer, int menuWidth, const std::string &title = "");
    virtual IView *onEnterPressHandler() = 0;
    virtual IView *onKeyPressHandler(int key, IView *sender, IView *onEscPressView);

protected:
    
    InputField mInputField;
};

#endif // IVIEW_HPP
