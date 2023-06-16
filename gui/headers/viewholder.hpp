#ifndef VIEWHOLDER_HPP
#define VIEWHOLDER_HPP

#include <list>

class IView;

class ViewHolder
{
public:

    ~ViewHolder();
    IView *operator = (IView *view);
    IView *currentView();
    int viewsCount() const;

private:

    std::list<IView *> mViews;
    IView *mCurrentView;
};

#endif // VIEWHOLDER_HPP
