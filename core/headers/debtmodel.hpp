#ifndef DEBTMODEL_HPP
#define DEBTMODEL_HPP

#include "crudmodel.hpp"
#include "localmodel.hpp"

class DebtModel : public CRUDModel, public LocalModel
{
    friend class DebtModelHandler;
public:
    DebtModel(int id, const std::string &name, int amount);

    void create() override;
    void read() override;
    void update() override;
    void remove() override;
    void parseJsonObject(const QJsonObject &) override;

    void load(std::ifstream &file) override;
    void save(std::ofstream &file) override;

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
