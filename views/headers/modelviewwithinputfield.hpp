#ifndef MODELVIEWWITHINPUTFIELD_HPP
#define MODELVIEWWITHINPUTFIELD_HPP

#include "smv/iview.hpp"

class InputField
{
public:

    const int X, Y;

    InputField(int x, int y) : X{x}, Y{y} { }
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
    void keyEventsHandler(const int) override { return; }
    void show(stf::Renderer &) override { return; }
};

class ActiveInputField : public InputField
{
public:
    void keyEventsHandler(const int key) override
    {

    }

    void show(stf::Renderer &renderer) override
    {

    }
};

class AppModel;

class ModelViewWithInputField : public stf::smv::IView
{
public:
    const int BeginListY = 2;
    const int BeginListX = 26;
    const int InputPrewievY;
    const int InputInfoY;

    ModelViewWithInputField(AppModel *model);
    virtual stf::smv::IView *inputHandler(int key);
    virtual stf::smv::IView *onEnterHandler() = 0;
    virtual stf::smv::IView *onQPressHandler() const;

    stf::smv::IView *keyEventsHandler(const int key) override;
    void show(stf::Renderer &renderer) override;
    int option() const;

protected:

    std::string getStrFromInput();
    int getIntFromInput();

    std::string mInput;
    std::string mInputBackup;
    int mOption = 0, mOptrionsCount = 0;
};

#endif // MODELVIEWWITHINPUTFIELD_HPP
