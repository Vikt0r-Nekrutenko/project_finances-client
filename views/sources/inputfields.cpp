#include "inputfields.hpp"
#include "modelviewwithinputfield.hpp"


const std::string &InputField::text() const
{
    return mText;
}

std::string &InputField::text()
{
    return mText;
}

InputField::InputField(int x, int y) : X{x}, Y{y} { }

int InputField::getInt()
{
    int pos = mText.find(" ");
    if(pos != int(mText.npos)) {
        int result = std::stoi(mText.substr(0, pos));
        mText.erase(0, pos + 1);
        return result;
    } else {
        return std::stoi(mText.erase(0, pos + 1));
    }
}

std::string InputField::getStr()
{
    int pos = mText.find(" ");
    if(pos != int(mText.npos)) {
        std::string result = mText.substr(0, pos);
        mText.erase(0, pos + 1);
        return result;
    } else {
        return mText.erase(0, pos + 1);
    }
}

InactiveInputField::InactiveInputField(int x, int y) : InputField(x, y) { }

InputField *InactiveInputField::keyEventsHandler(const int) { return this; }

stf::smv::IView *InactiveInputField::keyEventsHandler(stf::smv::IView *sender, const int)
{
    return sender;
}

void InactiveInputField::show(stf::Renderer &) const { return; }

InputField *InactiveInputField::changeState() const
{
    return new ActiveInputField(X, Y);
}

ActiveInputField::ActiveInputField(int x, int y) : InputField(x, y) { }

InputField *ActiveInputField::keyEventsHandler(const int key)
{
    if(key == ',') {
        if(mCursor > 0)
            --mCursor;
        return this;
    } else if(key == '.') {
        if(mCursor < int(mText.length()))
            ++mCursor;
        return this;
    } else if((key == 127 || key == 8) && mCursor > 0) {
        mText.erase(--mCursor, 1);
        return this;
    } else if((key < '0' || key > 'z') && key != ' ' && key != '-' && key != '+')
        return this;
    mText.insert(mCursor++, 1, char(key));
    return this;
}

stf::smv::IView *ActiveInputField::keyEventsHandler(stf::smv::IView *sender, const int key)
{
    auto view = static_cast<ModelViewWithInputField *>(sender);
    if(key == 'q' && mText.empty()) {
        view->setOption(0);
        view->setInputField(new InactiveInputField(X, Y));
    } else if(key == 13 || key == 10) {
        view = static_cast<ModelViewWithInputField *>(view->onEnterHandler());
        view->setOption(0);
        view->setInputField(new InactiveInputField(X, Y));
    } else {
        keyEventsHandler(key);
    }
    return view;
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
