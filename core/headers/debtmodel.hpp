#ifndef DEBTMODEL_HPP
#define DEBTMODEL_HPP

#include "crudmodel.hpp"

class DebtModel : public CRUDModel
{
    friend class DebtModelHandler;
public:
    DebtModel(int id, const std::string &name, int amount);

    void create() override;
    void read() override;
    void update() override;
    void remove() override;
    void parseJsonObject(const QJsonObject &) override;

    const std::string &name() const;
    int amount() const;
    int id() const;

    void increase(int amount);
    void decrease(int amount);

private:

    std::string mName;
    int mId, mAmount;
};

#endif // DEBTMODEL_HPP
