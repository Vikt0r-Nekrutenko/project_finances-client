#include "modelviewwithinputfield.hpp"
#include "appmodel.hpp"
#include "menuview.hpp"
#include "inputfields.hpp"

ModelViewWithInputField::ModelViewWithInputField(AppModel *model)
    : stf::smv::IView(model),
      InputPrewievY(stf::Renderer::log.y() - 2),
      InputInfoY(stf::Renderer::log.y() - 3),
      mInputField(new InactiveInputField(0, InputPrewievY)) {}

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
            setInputField(new ActiveInputField(0, InputPrewievY));
        } else {
            return mInputField->keyEventsHandler(this, key);
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

    mInputField->show(renderer);
}

int ModelViewWithInputField::option() const
{
    return mOption;
}

void ModelViewWithInputField::setOption(int value)
{
    mOption = value;
}

void ModelViewWithInputField::setInputField(InputField *newIF)
{
    delete mInputField;
    mInputField = newIF;
}

std::string ModelViewWithInputField::getStrFromInput()
{
    return mInputField->getStr();
}

int ModelViewWithInputField::getIntFromInput()
{
    return mInputField->getInt();
}
