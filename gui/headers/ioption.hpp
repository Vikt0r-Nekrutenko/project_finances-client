#ifndef IOPTION_HPP
#define IOPTION_HPP

#include <string>

class IView;

class IOption
{
public:

    virtual ~IOption() = default;
    virtual std::string caption() const = 0;
    virtual IView *execute(IView *sender) = 0;
};

namespace options {
namespace main_view {

class Deposits : public IOption
{
public:

    std::string caption() const override;

    IView *execute(IView *sender) override;
};

class Exit : public IOption
{
public:

    std::string caption() const override;

    IView *execute(IView *sender) override;
};

}}

#endif // IOPTION_HPP
