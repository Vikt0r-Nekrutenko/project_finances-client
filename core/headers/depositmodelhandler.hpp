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

    DepositModelHandler();
    ~DepositModelHandler() override;
    void addNewDeposit(const std::string &name, int balance);
    void updateBalance(int depositIndex, int newBalance);
    void deleteDeposit(int depositIndex);

protected:

    void parseJsonArray(const QJsonArray &replyJsonArray) final;

private:

    std::vector<DepositModel> mDeposits;
};

#endif // DEPOSITMODELHANDLER_HPP
