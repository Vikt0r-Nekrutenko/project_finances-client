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
    void parseJsonArray(const QJsonArray &replyJsonArray) override;

    const std::vector<DebtModel> &debts() const;

    std::vector<DebtModel>::iterator findByName(const std::string &name);

private:

    std::vector<DebtModel> mDebts;
};

#endif // DEBTMODELHANDLER_HPP
