#ifndef DEBTMODEL_HPP
#define DEBTMODEL_HPP

#include "crudmodel.hpp"
#include "localmodel.hpp"

class CORE_EXPORT DebtModel : public CRUDModel, public LocalModel
{
    friend class DebtModelHandler;

public:

    DebtModel(int id, const std::string &name, int amount);

    void create() override;
    void read() override;
    void update() override;
    void remove() override;

    void load(std::ifstream &file) override;
    void save(std::ofstream &file) override;

    inline const std::string &name() const { return mName; }
    inline int amount() const { return mAmount; }
    inline int id() const { return mId; }

    void increase(int amount);
    void decrease(int amount);

private:

    void parseJsonObject(const QJsonObject &) override;

    std::string mName;
    int mId, mAmount;
};

#endif // DEBTMODEL_HPP
