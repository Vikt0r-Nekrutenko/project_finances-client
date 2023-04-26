#include "modelviewwithinputfield.hpp"
#include "appmodel.hpp"
#include "menuview.hpp"
#include "inputfields.hpp"

ModelViewWithInputField::ModelViewWithInputField(AppModel *model)
    : stf::smv::IView(model),
      InputPrewievY(stf::Renderer::log.y() - 2),
      InputInfoY(stf::Renderer::log.y() - 3),
      mInputField(new InactiveInputField(0, InputPrewievY)) {}

stf::smv::IView *ModelViewWithInputField::inputHandler(int key)
{
//    if(key == 'q' && mInput.empty()) {
//        mOption = 0;

//        InputField *newState = mInputField->changeState();
//        delete mInputField;
//        mInputField = newState;
//    else if(key == ' ' && mInput.empty() && !mInputBackup.empty())
//        mInput = mInputBackup;
//    } else if(key == 13 || key == 10) {
//        mInputBackup = mInput;
//        stf::smv::IView *resultView = onEnterHandler();
//        mInput.clear();
//        mOption = 0;
//        return resultView;
//    }
//    } else if((key >= '0' && key <= 'z') || key == ' ' || key == '-' || key == '+')
//        mInput += key;
//    else if((key == 127 || key == 8) && !mInput.empty())
//        mInput.pop_back();
    return this;
}

stf::smv::IView *ModelViewWithInputField::onQPressHandler()
{
    return new MenuView(static_cast<AppModel*>(m_model));
}

stf::smv::IView *ModelViewWithInputField::keyEventsHandler(const int key)
{
    try {
        if(mOption == 0) {
            if(key == 'q') {
                return onQPressHandler();
            }
            int tmpOption = key - '0';
            if(tmpOption < 1 || tmpOption > mOptrionsCount)
                return this;
            mOption = tmpOption;
            delete mInputField;
            mInputField = new ActiveInputField(0, InputPrewievY);
        } else {
            if(key == 'q' && mInputField->text().empty()) {
                delete mInputField;
                mInputField = new InactiveInputField(0, InputPrewievY);
                mOption = 0;
            } else if(key == 13 || key == 10) {
//                mInputBackup = mInput;
                stf::smv::IView *resultView = onEnterHandler();
//                mInput.clear();
                mOption = 0;
                return resultView;
            } else {
                mInputField->keyEventsHandler(key);
            }
        }
    } catch(const std::exception &msg) {
        stf::Renderer::log << stf::endl << msg.what();
    }
    return this;
}

void ModelViewWithInputField::show(stf::Renderer &renderer)
{
    for(int i = 0; i < renderer.Size.x; ++i)
        renderer.drawPixel({i, 1}, '-');
    for(int i = 0; i < renderer.Size.x; ++i)
        renderer.drawPixel({i, int(stf::Renderer::log.y() - 3)}, '-');
    for(int i = 0; i < renderer.Size.x; ++i)
        renderer.drawPixel({i, int(stf::Renderer::log.y() - 1)}, '-');
    for(int i = 2; i < int(stf::Renderer::log.y() - 3); ++i)
        renderer.drawPixel({BeginListX - 1, i}, '|');

//    if(mOption != 0)
//        renderer.draw({0, InputPrewievY}, ">> %s", mInput.c_str());
    mInputField->show(renderer);
}

int ModelViewWithInputField::option() const
{
    return mOption;
}

std::string ModelViewWithInputField::getStrFromInput()
{
    return mInputField->getStr();
}

int ModelViewWithInputField::getIntFromInput()
{
    return mInputField->getInt();
}
