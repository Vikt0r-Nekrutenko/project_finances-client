#include "inputfields.hpp"


InputField::InputField(int x, int y) : X{x}, Y{y} { }

InactiveInputField::InactiveInputField(int x, int y) : InputField(x, y) { }

void InactiveInputField::keyEventsHandler(const int) { return; }

void InactiveInputField::show(stf::Renderer &) { return; }

ActiveInputField::ActiveInputField(int x, int y) : InputField(x, y) { }

void ActiveInputField::keyEventsHandler(const int key)
{
    mText.insert(mCursor++, 1, key);
}

void ActiveInputField::show(stf::Renderer &renderer)
{
    renderer.draw({X, Y}, ">> %s", mText.c_str());
    renderer.draw({3 + X + mCursor, Y}, "%CR%c", mCursor >= int(mText.length()) ? ' ' : mText.at(mCursor));
}
