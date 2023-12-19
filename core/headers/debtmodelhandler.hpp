#ifndef DEBTMODELHANDLER_HPP
#define DEBTMODELHANDLER_HPP

#include "modelhandler.hpp"
#include "debtmodel.hpp"

class CORE_EXPORT DebtModelHandler : public DataModelHandler
{
public:
    DebtModelHandler();
    ~DebtModelHandler() override;

    void addNewDebt(const std::string &name, int amount);
    void updateDebt(int index, const std::string &name, int amount);
    void deleteDebt(int index);

    inline const std::vector<DebtModel> &debts() const { return mDebts; }

    std::vector<DebtModel>::iterator findByName(const std::string &name);

protected:

    void parseJsonArray(const QJsonArray &replyJsonArray) override;

private:

    std::vector<DebtModel> mDebts;
};

#endif // DEBTMODELHANDLER_HPP
