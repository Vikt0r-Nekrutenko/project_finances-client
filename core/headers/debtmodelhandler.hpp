#ifndef DEBTMODELHANDLER_HPP
#define DEBTMODELHANDLER_HPP

#include "modelhandler.hpp"
#include "debtmodel.hpp"

class CORE_EXPORT DebtModelHandler : public DataModelHandler
{
public:

    class CORE_EXPORT Query : public std::vector<DebtModel *>
    {
    public:

        Query(DebtModelHandler *handler);
        const Query &select();
        int sum() const;
        std::vector<DebtModel *>::const_iterator findByName(const std::string &name) const;

    private:

        DebtModelHandler *mHandler { nullptr };

    } query {this};

    DebtModelHandler();
    ~DebtModelHandler() override;

    void addNewDebt(const std::string &name, int amount);
    void updateDebt(int index, const std::string &name, int amount);
    void deleteDebt(int index);
    void increaseAmount(int index, int amount);
    void decreaseAmount(int index, int amount);

protected:

    void parseJsonArray(const QJsonArray &replyJsonArray) override;

private:

    std::vector<DebtModel> mDebts;
};

#endif // DEBTMODELHANDLER_HPP
