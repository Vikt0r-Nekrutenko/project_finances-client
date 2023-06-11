#ifndef IINPUTFIELD_HPP
#define IINPUTFIELD_HPP

#include "renderer.hpp"

class IView;

constexpr int VK_RIGHT_ARROW = '.';
constexpr int VK_LEFT_ARROW = ',';
constexpr int VK_BACKSPACE1 = 127;
constexpr int VK_BACKSPACE2 = 8;
constexpr int VK_ESCAPE1 = 27;
constexpr int VK_TAB1 = 9;

class IInputField
{
public:

    std::string Text;

    virtual ~IInputField() = default;

    virtual void show(stf::Renderer &renderer, int x, int y)
    {
        renderer.draw({x, y}, ">> %s", Text.c_str());
        renderer.draw({3 + x + mCursor, y}, "%CR%c", mCursor >= int(Text.length()) ? ' ' : Text.at(mCursor));
    }

    virtual IView *keyHandler(IView *sender, int key)
    {
        if(key == VK_LEFT_ARROW) {
            if(mCursor > 0)
                --mCursor;
        } else if(key == VK_RIGHT_ARROW) {
            if(mCursor < int(Text.length()))
                ++mCursor;
        } else if((key == VK_BACKSPACE1 || key == VK_BACKSPACE2) && mCursor > 0) {
            Text.erase(--mCursor, 1);
        } else if((key >= '0' && key <= 'z') || key == ' ' || key == '-' || key == '+') {
            Text.insert(mCursor++, 1, char(key));
        }
        return sender;
    }

    std::string getStr()
    {
        int pos = Text.find(" ");
        if(pos != int(Text.npos)) {
            std::string result = Text.substr(0, pos);
            Text.erase(0, pos + 1);
            mCursor = Text.length() - 1;
            return result;
        } else {
            mCursor = 0;
            return Text.erase(0, pos + 1);
        }
    }

    int getExpressionResult()
    {
        std::string expression = getStr();
        std::vector<char> operators;
        std::vector<int> operands;
        std::string::iterator it = expression.begin(), jt = expression.begin();

        for(; it != expression.end(); ++it) {
            if(*it == '+' || *it == '-') {
                operators.push_back(*it);
                operands.push_back(std::stoi(std::string(jt, it)));
                jt = it + 1;
            }
        }
        operands.push_back(std::stoi(std::string(jt, it)));

        int result = operands.at(0);
        std::vector<int>::iterator operand = operands.begin() + 1;

        for(auto op : operators) {
            switch (op) {
            case '+': result += *operand; break;
            case '-': result -= *operand; break;
            }
            ++operand;
        }
        return result;
    }

protected:

    int mCursor = 0;
};

#endif // IINPUTFIELD_HPP
