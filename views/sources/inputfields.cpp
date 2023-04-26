#include "inputfields.hpp"


InputField::InputField(int x, int y) : X{x}, Y{y} { }

InactiveInputField::InactiveInputField(int x, int y) : InputField(x, y) { }

void InactiveInputField::keyEventsHandler(const int) { return; }

void InactiveInputField::show(stf::Renderer &) const { return; }

InputField *InactiveInputField::changeState() const
{
    return new ActiveInputField(X, Y);
}

ActiveInputField::ActiveInputField(int x, int y) : InputField(x, y) { }

void ActiveInputField::keyEventsHandler(const int key)
{
    if(key == ',') {
        if(mCursor > 0)
            --mCursor;
        return;
    } else if(key == '.') {
        if(mCursor < int(mText.length()))
            ++mCursor;
        return;
    } else if((key == 127 || key == 8) && mCursor > 0) {
        mText.erase(--mCursor, 1);
        return;
    } else if((key < '0' || key > 'z') && key != ' ' && key != '-' && key != '+')
        return;
    mText.insert(mCursor++, 1, char(key));
}

void ActiveInputField::show(stf::Renderer &renderer) const
{
    renderer.draw({X, Y}, ">> %s", mText.c_str());
    renderer.draw({3 + X + mCursor, Y}, "%CR%c", mCursor >= int(mText.length()) ? ' ' : mText.at(mCursor));
}

InputField *ActiveInputField::changeState() const
{
    return new InactiveInputField(X, Y);
}
