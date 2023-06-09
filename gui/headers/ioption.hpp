#ifndef IOPTION_HPP
#define IOPTION_HPP

#include <string>

class IOption
{
public:

    virtual ~IOption() = default;
    virtual std::string caption() const;
};

#endif // IOPTION_HPP
