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

#include "headers/datamodel.hpp"

class ViewWithLogItem : public IView
{
public:

    static constexpr int LogHeight = 4;

    ViewWithLogItem(AppModel *model, ViewHolder *holder)
        : IView{model, holder} { }

    void show(stf::Renderer &renderer) override
    {
        renderer.drawLine({mMenuBar->Width + 1, renderer.Size.y - LogHeight - 1},
                          {renderer.Size.x - 1, renderer.Size.y - LogHeight - 1}, '-');

        for(int i = int(log().size()) - LogHeight, j = LogHeight; i < int(log().size()); ++i, --j) {
            if(i < 0)
                continue;
            renderer.draw({mMenuBar->Width + 1, renderer.Size.y - j}, "%d.%s", i, log().at(i).c_str());
        }

        IView::show(renderer);
    }
};

#endif // IVIEW_HPP
