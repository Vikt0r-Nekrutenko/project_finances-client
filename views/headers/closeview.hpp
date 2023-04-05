#ifndef CLOSEVIEW_HPP
#define CLOSEVIEW_HPP

#include <smv/iview.hpp>

class AppModel;

class CloseView : public stf::smv::IView
{
public:
    CloseView(AppModel *model);

    bool isContinue() const override;

    void show(stf::Renderer&) override;;

    IView* update(const float) override;
};

#endif // CLOSEVIEW_HPP
