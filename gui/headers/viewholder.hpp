#ifndef VIEWHOLDER_HPP
#define VIEWHOLDER_HPP

#include <list>

class IView;

class ViewHolder
{
public:

    ~ViewHolder();
    void operator = (IView *view);
    IView *currentView();

private:

    std::list<IView *> mViews;
    IView *mCurrentView;
};

#endif // VIEWHOLDER_HPP
