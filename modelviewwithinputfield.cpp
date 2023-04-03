#include "modelviewwithinputfield.hpp"
#include "appmodel.hpp"
#include "menuview.hpp"

ModelViewWithInputField::ModelViewWithInputField(AppModel *model)
    : stf::smv::IView(model) {}

void ModelViewWithInputField::inputHandler(int key)
{
    if(key == 'q' && mInput.empty())
        mOption = 0;
    else if(key == ' ' && mInput.empty() && !mInputBackup.empty())
        mInput = mInputBackup;
    else if(key == 13) {
        mInputBackup = mInput;
        onEnterHandler();
        mInput.clear();
        mOption = 0;
    } else if((key >= '0' && key <= 'z') || key == ' ' || key == '-')
        mInput += key;
    else if(key == 8 && !mInput.empty())
        mInput.pop_back();
}

stf::smv::IView *ModelViewWithInputField::keyEventsHandler(const int key)
{
    if(mOption == 0) {
        for(int i = 1; i <= mOptrionsCount; ++i)
            if(key == '0' + i)
                mOption = key - '0';
        if(key == 'q')
            return new MenuView(static_cast<AppModel*>(m_model));
    } else {
        try {
            inputHandler(key);
        } catch(const std::exception &msg) {
            stf::Renderer::log << stf::endl << msg.what();
        }
    }
    return this;
}

int ModelViewWithInputField::option() const
{
    return mOption;
}

std::string ModelViewWithInputField::getStrFromInput()
{
    int pos = mInput.find(" ");
    if(pos != int(mInput.npos)) {
        std::string result = mInput.substr(0, pos);
        mInput.erase(0, pos + 1);
        return result;
    } else {
        return mInput.erase(0, pos + 1);
    }
}

int ModelViewWithInputField::getIntFromInput()
{
    int pos = mInput.find(" ");
    if(pos != int(mInput.npos)) {
        int result = std::stoi(mInput.substr(0, pos));
        mInput.erase(0, pos + 1);
        return result;
    } else {
        return std::stoi(mInput.erase(0, pos + 1));
    }
}
