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
    void applyChanges();

    inline const std::vector<DepositModel> &deposits() const { return mDeposits; }
    inline std::vector<DepositModel> &deposits() { return mDeposits; }
    inline std::vector<size_t> &listOfChanges() { return mListOfChanges; }

    std::vector<DepositModel>::iterator findByName(const std::string &name);

protected:

    void parseJsonArray(const QJsonArray &replyJsonArray) final;

private:

    void addNewChange(const size_t index);

    std::vector<size_t> mListOfChanges;
    std::vector<DepositModel> mDeposits;
};

#endif // DEPOSITMODELHANDLER_HPP
