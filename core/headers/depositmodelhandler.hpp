#ifndef DEPOSITMODELHANDLER_HPP
#define DEPOSITMODELHANDLER_HPP

#include "depositmodel.hpp"
#include "modelhandler.hpp"

class CORE_EXPORT DepositModelHandler : public DataModelHandler
{
public:

    class CORE_EXPORT Query : public std::vector<DepositModel *>
    {
    public:

        Query(DepositModelHandler *handler);
        const Query &select();
        int sum() const;
        std::vector<DepositModel *>::const_iterator findByName(const std::string &name) const;

    private:

        DepositModelHandler *mHandler { nullptr };

    } query {this};

    std::thread *asyncConstruct() final;
    std::thread *asyncDestruct() final;
    void addNewDeposit(const std::string &name, int balance);
    void selectDeposit(int index);
    void updateBalance(int index, int newBalance);
    void deleteDeposit(int index);
    void increaseBalance(int amount);
    void decreaseBalance(int amount);
    void makeTransfer(int fromId, int toId, int amount);

    inline const DepositModel *selectedDeposit() const { return mSelectedDeposit; }

protected:

    void parseJsonArray(const QJsonArray &replyJsonArray) final;

private:

    std::vector<DepositModel> mDeposits;
    DepositModel *mSelectedDeposit { nullptr };
};

#endif // DEPOSITMODELHANDLER_HPP
