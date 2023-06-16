#include "viewholder.hpp"
#include "iview.hpp"


ViewHolder::~ViewHolder()
{
    for(auto view : mViews)
        delete view;
}

void ViewHolder::operator =(IView *view)
{
    for(auto it = mViews.begin(); it != mViews.end(); ++it) {
        if(*it == view)
            return;

        if(typeid(**it).hash_code() == typeid(*view).hash_code()) {
            delete *it;
            *it = mCurrentView = view;
            return;
        }

        mViews.push_back(view);
    }
}

IView *ViewHolder::currentView()
{
    return mCurrentView;
}
