#ifndef MODELVIEWWITHINPUTFIELD_HPP
#define MODELVIEWWITHINPUTFIELD_HPP

#include "smv/iview.hpp"

class AppModel;

class ModelViewWithInputField : public stf::smv::IView
{
public:
    ModelViewWithInputField(AppModel *model);
    virtual void inputHandler(int key);
    virtual void onEnterHandler() = 0;

protected:

    std::string mInput;
    int mOption = 0;
};

#endif // MODELVIEWWITHINPUTFIELD_HPP
