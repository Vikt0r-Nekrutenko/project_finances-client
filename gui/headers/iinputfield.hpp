#ifndef IINPUTFIELD_HPP
#define IINPUTFIELD_HPP

#include "renderer.hpp"

class IView;

class IInputField
{
public:

    std::string Text;

    IInputField() {}
    virtual ~IInputField() = default;

    virtual void show(stf::Renderer &renderer) = 0;
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

#endif // IINPUTFIELD_HPP
