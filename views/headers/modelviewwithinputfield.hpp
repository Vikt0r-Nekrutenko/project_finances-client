#ifndef MODELVIEWWITHINPUTFIELD_HPP
#define MODELVIEWWITHINPUTFIELD_HPP

#include "smv/iview.hpp"

class AppModel;

class ModelViewWithInputField : public stf::smv::IView
{
public:
    const int BeginListY = 2;
    const int BeginListX = 26;
    const int InputPrewievY;
    const int InputInfoY;

    ModelViewWithInputField(AppModel *model);
    virtual void inputHandler(int key);
    virtual void onEnterHandler() = 0;

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
