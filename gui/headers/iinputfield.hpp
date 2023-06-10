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

    std::string getStr();

protected:

    int mCursor = 0;
};

#endif // IINPUTFIELD_HPP
