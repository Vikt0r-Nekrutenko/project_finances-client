#ifndef IINPUTFIELD_HPP
#define IINPUTFIELD_HPP

#include "renderer.hpp"

class IView;

constexpr int VK_UPWARDS_ARROW = 24;
constexpr int VK_DOWNWARDS_ARROW = 25;
constexpr int VK_RIGHT_ARROW = 26;
constexpr int VK_LEFT_ARROW = 27;
constexpr int VK_BACKSPACE1 = 127;
constexpr int VK_BACKSPACE2 = 8;

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

    IView *keyHandler(IView *sender, int key) override
    {
        if(key == VK_LEFT_ARROW) {
            if(mCursor > 0)
                --mCursor;
        } else if(key == VK_RIGHT_ARROW) {
            if(mCursor < int(Text.length()))
                ++mCursor;
        } else if((key == VK_BACKSPACE1 || key == VK_BACKSPACE2) && mCursor > 0) {
            Text.erase(--mCursor, 1);
        } else if((key > '0' && key < 'z') || key == ' ' || key == '-' || key == '+') {
            Text.insert(mCursor++, 1, char(key));
        }
        return sender;
    }
};

#endif // IINPUTFIELD_HPP
