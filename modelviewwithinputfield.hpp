#ifndef MODELVIEWWITHINPUTFIELD_HPP
#define MODELVIEWWITHINPUTFIELD_HPP

#include "smv/iview.hpp"

class AppModel;

class ModelViewWithInputField : public stf::smv::IView
{
public:
    const int BeginListY = 13;

    ModelViewWithInputField(AppModel *model);
    virtual void inputHandler(int key);
    virtual void onEnterHandler() = 0;
    virtual stf::smv::IView *keyEventsHandler(const int key);

protected:

    std::string getStrFromInput();
    int getIntFromInput();

    std::string mInput;
    std::string mInputBackup;
    int mOption = 0, mOptrionsCount = 0;
};

#endif // MODELVIEWWITHINPUTFIELD_HPP
