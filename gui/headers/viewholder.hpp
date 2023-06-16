#ifndef VIEWHOLDER_HPP
#define VIEWHOLDER_HPP

#include "renderer.hpp"
#include <list>

class IView;

class ViewHolder
{
public:

    ~ViewHolder();
    void operator = (IView *view);
    void show(stf::Renderer &renderer);
    IView *keyHandler(int key);

private:

    std::list<IView *> mViews;
    IView *mCurrentView;
};

#endif // VIEWHOLDER_HPP
