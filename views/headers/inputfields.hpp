#ifndef INPUTFIELDS_H
#define INPUTFIELDS_H

#include "renderer.hpp"

class InputField
{
public:

    const int X, Y;

    InputField(int x, int y);
    virtual ~InputField() = default;
    virtual void keyEventsHandler(const int) = 0;
    virtual void show(stf::Renderer &) = 0;

protected:

    std::string mText;
    int mCursor = 0;
};

class InactiveInputField : public InputField
{
public:
    InactiveInputField(int x, int y);
    void keyEventsHandler(const int) override;
    void show(stf::Renderer &) override;
};

class ActiveInputField : public InputField
{
public:

    ActiveInputField(int x, int y);
    void keyEventsHandler(const int key) override;
    void show(stf::Renderer &renderer) override;
};

#endif // INPUTFIELDS_H
