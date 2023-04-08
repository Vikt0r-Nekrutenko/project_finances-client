#ifndef DEPOSITMODELHANDLER_HPP
#define DEPOSITMODELHANDLER_HPP

#include "depositmodel.hpp"
#include "modelhandler.hpp"

class DepositModelHandler : public DataModelHandler
{
public:
    DepositModelHandler();
    void addNewDeposit(const std::string &name, int balance);
    void updateBalance(int depositIndex, int newBalance);
    void deleteDeposit(int depositIndex);
    void parseJsonArray(const QJsonArray &replyJsonArray) override;

    const std::vector<DepositModel> &deposits() const;
    std::vector<DepositModel> &deposits();

    std::vector<DepositModel>::iterator findByName(const std::string &name);

private:

    std::vector<DepositModel> mDeposits;
};

#endif // DEPOSITMODELHANDLER_HPP
