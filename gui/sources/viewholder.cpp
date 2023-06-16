#include "viewholder.hpp"
#include "iview.hpp"


ViewHolder::~ViewHolder()
{
    for(auto view : mViews)
        delete view;
}

IView *ViewHolder::operator =(IView *view)
{
    for(auto it = mViews.begin(); it != mViews.end(); ++it) {
        if(*it == view) {
            return mCurrentView = view;
        }

        if(typeid(**it).hash_code() == typeid(*view).hash_code()) {
            delete *it;
            return *it = mCurrentView = view;
        }
    }

    mViews.push_back(view);
    return mCurrentView = mViews.back();
}

IView *ViewHolder::currentView()
{
    return mCurrentView;
}

int ViewHolder::viewsCount() const
{
    return mViews.size();
}
