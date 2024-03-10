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

int calculateExpressionResultFromString(const std::string &expression);

class InputField
{
public:

    std::string Text;

    virtual ~InputField() = default;

    virtual void show(stf::Renderer &renderer, int x, int y);

    virtual IView *keyHandler(IView *sender, int key);

    void restoreText();

    std::string getStr();

    int getExpressionResult();

protected:

    static std::vector<std::string> mHistory;
    int mHistoryCursor = 0;
    int mCursor = 0;
};

#endif // INPUTFIELD_H
