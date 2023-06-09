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

#endif // IOPTION_HPP
