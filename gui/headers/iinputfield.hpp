#ifndef IINPUTFIELD_HPP
#define IINPUTFIELD_HPP

#include "renderer.hpp"

class IView;

class IInputField
{
public:

    std::string Text;

    virtual ~IInputField() = default;
    virtual void show(stf::Renderer &renderer, int x, int y) = 0;
    virtual IView *keyHandler(IView *sender, int key) = 0;

    std::string getStr()
    {
        int pos = Text.find(" ");
        if(pos != int(Text.npos)) {
            std::string result = Text.substr(0, pos);
            Text.erase(0, pos + 1);
            return result;
        } else {
            return Text.erase(0, pos + 1);
        }
    }

protected:

    int mCursor = 0;
};

class ActiveInputField : public IInputField
{
public:

    void show(stf::Renderer &renderer, int x, int y) override
    {
        renderer.draw({x, y}, ">> %s", Text.c_str());
        renderer.draw({3 + x + mCursor, y}, "%CR%c", mCursor >= int(Text.length()) ? ' ' : Text.at(mCursor));
    }
};

#endif // IINPUTFIELD_HPP
