#ifndef INPUTFIELDS_H
#define INPUTFIELDS_H

#include "smv/iview.hpp"

class InputField
{
public:

    const int X, Y;
    const std::string &text() const;
    std::string &text();

    InputField(int x, int y);
    virtual ~InputField() = default;
    virtual InputField *keyEventsHandler(const int) = 0;
    virtual stf::smv::IView *keyEventsHandler(stf::smv::IView *sender, const int key) = 0;
    virtual void show(stf::Renderer &) const = 0;

    int getInt();
    std::string getStr();

protected:

    std::string mText;
    int mCursor = 0;
};

class InactiveInputField : public InputField
{
public:
    InactiveInputField(int x, int y);
    InputField *keyEventsHandler(const int) override;
    stf::smv::IView *keyEventsHandler(stf::smv::IView *sender, const int key) override;
    void show(stf::Renderer &) const override;
};

class ActiveInputField : public InputField
{
public:

    ActiveInputField(int x, int y);
    InputField *keyEventsHandler(const int key) override;
    stf::smv::IView *keyEventsHandler(stf::smv::IView *sender, const int key) override;
    void show(stf::Renderer &renderer) const override;
};

#endif // INPUTFIELDS_H
