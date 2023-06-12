#ifndef INPUTFIELD_H
#define INPUTFIELD_H

#include "renderer.hpp"

class IView;

constexpr int VK_RIGHT_ARROW = '.';
constexpr int VK_LEFT_ARROW = ',';
constexpr int VK_BACKSPACE1 = 127;
constexpr int VK_BACKSPACE2 = 8;
constexpr int VK_ESCAPE1 = 27;
constexpr int VK_TAB1 = 9;

class InputField
{
public:

    std::string Text;

    virtual ~InputField() = default;

    virtual void show(stf::Renderer &renderer, int x, int y);

    virtual IView *keyHandler(IView *sender, int key);

    std::string getStr();

    int getExpressionResult();

protected:

    std::string mBackupText;
    int mCursor = 0;
};

#endif // INPUTFIELD_H
