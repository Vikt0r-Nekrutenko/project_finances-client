#ifndef DEPOSITMODELHANDLER_HPP
#define DEPOSITMODELHANDLER_HPP

#include "depositmodel.hpp"
#include "modelhandler.hpp"

class CORE_EXPORT DepositModelHandler : public DataModelHandler
{
public:
    DepositModelHandler();
    ~DepositModelHandler() override;
    void addNewDeposit(const std::string &name, int balance);
    void updateBalance(int depositIndex, int newBalance);
    void deleteDeposit(int depositIndex);

    inline const std::vector<DepositModel> &deposits() const { return mDeposits; }
    inline std::vector<DepositModel> &deposits() { return mDeposits; }
    std::vector<DepositModel *> currentDeposits();

    std::vector<DepositModel>::iterator findByName(const std::string &name);

protected:

    void parseJsonArray(const QJsonArray &replyJsonArray) final;

private:

    std::vector<DepositModel> mDeposits;
};

#endif // DEPOSITMODELHANDLER_HPP
