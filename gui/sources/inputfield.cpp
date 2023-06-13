#include "inputfield.hpp"
#include "imenu.hpp"

void InputField::show(stf::Renderer &renderer, int x, int y)
{
    renderer.draw({x, y}, ">> %s", Text.c_str());
    renderer.draw({3 + x + mCursor, y}, "%CR%c", mCursor >= int(Text.length()) ? ' ' : Text.at(mCursor));
}

IView *InputField::keyHandler(IView *sender, int key)
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
    } else if(key == VK_ENTER1 || key == VK_ENTER2) {
        mBackupText = Text;
    }
    return sender;
}

void InputField::restoreText()
{
    Text = mBackupText;
    mCursor = Text.length();
}

std::string InputField::getStr()
{
    int pos = Text.find(" ");
    if(pos != int(Text.npos)) {
        std::string result = Text.substr(0, pos);
        Text.erase(0, pos + 1);
        mCursor = Text.length() - 1;
        return result;
    } else {
        mCursor = 0;
        std::string result = Text.erase(0, pos + 1);
        Text.clear();
        return result;
    }
}

int InputField::getExpressionResult()
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
