#ifndef MODELVIEWWITHINPUTFIELD_HPP
#define MODELVIEWWITHINPUTFIELD_HPP

#include "smv/iview.hpp"

class AppModel;
class InputField;

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
    virtual stf::smv::IView *onQPressHandler();

    stf::smv::IView *keyEventsHandler(const int key) override;
    void show(stf::Renderer &renderer) override;
    int option() const;

protected:

    std::string getStrFromInput();
    int getIntFromInput();

    InputField *mInputField;
//    std::string mInput;
//    std::string mInputBackup;
    int mOption = 0, mOptrionsCount = 0;
};

#endif // MODELVIEWWITHINPUTFIELD_HPP
