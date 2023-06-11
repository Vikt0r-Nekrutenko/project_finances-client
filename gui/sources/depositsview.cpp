#include "depositview.hpp"
#include "viewholder.hpp"

IView *AddNewDepositView::keyHandler(int key)
{
    mInputField.keyHandler(this, key);
    if(key == VK_ENTER1 || key == VK_ENTER2) {
        return mHolder->getDepositView();
    }
    return this;
}
