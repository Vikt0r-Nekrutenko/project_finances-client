#include "modelviewwithinputfield.hpp"
#include "appmodel.hpp"

ModelViewWithInputField::ModelViewWithInputField(AppModel *model)
    : stf::smv::IView(model) {}

void ModelViewWithInputField::inputHandler(int key)
{
    if(key == 'q' && mInput.empty())
        mOption = 0;
    else if(key == 13) {
        onEnterHandler();
        mInput.clear();
        mOption = 0;
    } else if((key >= '0' && key <= 'z') || key == ' ')
        mInput += key;
    else if(key == 8 && !mInput.empty())
        mInput.pop_back();
}
