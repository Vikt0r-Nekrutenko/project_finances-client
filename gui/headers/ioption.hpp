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

class BackToStartView : public IOption
{
public:
    std::string caption() const override;

    IView *execute(IView *sender) override;
};

namespace main_view {

class Deposits : public IOption
{
public:

    std::string caption() const override;

    IView *execute(IView *sender) override;
};

class Debts : public IOption
{
public:

    std::string caption() const override;

    IView *execute(IView *sender) override;
};

class Categories : public IOption
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

}

namespace deposits_view {
class AddNewDeposit : public IOption
{
public:

    std::string caption() const override;

    IView *execute(IView *sender) override;
};

class ChangeBalance : public IOption
{
public:

    std::string caption() const override;

    IView *execute(IView *sender) override;
};

class DeleteDeposit : public IOption
{
public:

    std::string caption() const override;

    IView *execute(IView *sender) override;
};

class SelectDeposit : public IOption
{
public:

    std::string caption() const override;

    IView *execute(IView *sender) override;
};

class MakeTransfer : public IOption
{
public:

    std::string caption() const override;

    IView *execute(IView *sender) override;
};

}

namespace debts_view {
class AddNewDebt : public IOption
{
public:

    std::string caption() const override;

    IView *execute(IView *sender) override;
};

class ChangeAmount : public IOption
{
public:

    std::string caption() const override;

    IView *execute(IView *sender) override;
};

class DeleteDebt : public IOption
{
public:

    std::string caption() const override;

    IView *execute(IView *sender) override;
};

}

namespace categories_view {
class AddNewCategory : public IOption
{
public:

    std::string caption() const override;

    IView *execute(IView *sender) override;
};

class DeleteCategory : public IOption
{
public:

    std::string caption() const override;

    IView *execute(IView *sender) override;
};

}

namespace operations_view {
class AddNewOperation : public IOption
{
public:

    std::string caption() const override;

    IView *execute(IView *sender) override;
};

class AddNewTodayOperation : public IOption
{
public:

    std::string caption() const override;

    IView *execute(IView *sender) override;
};

class AddNewTodayLendOrRepay : public IOption
{
public:

    std::string caption() const override;

    IView *execute(IView *sender) override;
};

class AddNewLendOrRepay : public IOption
{
public:

    std::string caption() const override;

    IView *execute(IView *sender) override;
};

class DeleteOperation : public IOption
{
public:

    std::string caption() const override;

    IView *execute(IView *sender) override;
};

class SelectOperations : public IOption
{
public:

    std::string caption() const override;

    IView *execute(IView *sender) override;
};

class ChangeOperation : public IOption
{
public:

    std::string caption() const override;

    IView *execute(IView *sender) override;
};

class ChangeDate : public IOption
{
public:

    std::string caption() const override;

    IView *execute(IView *sender) override;
};

class ChangeAmount : public IOption
{
public:

    std::string caption() const override;

    IView *execute(IView *sender) override;
};

class ChangeCategory : public IOption
{
public:

    std::string caption() const override;

    IView *execute(IView *sender) override;
};


}

}

#endif // IOPTION_HPP
