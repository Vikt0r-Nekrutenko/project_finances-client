#ifndef DEPOSITMODEL_HPP
#define DEPOSITMODEL_HPP

#include "crudmodel.hpp"
#include "localmodel.hpp"

class CORE_EXPORT DepositModel : public CRUDModel, public LocalModel
{
    friend class DepositModelHandler;
public:
    DepositModel(const std::string &name, int balance);

    void create() override;
    void read() override;
    void update() override;
    void remove() override;
    void parseJsonObject(const QJsonObject &object) override;

    void load(std::ifstream &file) override;
    void save(std::ofstream &file) override;

    const std::string &name() const;
    int balance() const;

    void increaseBalance(int amount);
    void decreaseBalance(int amount);

private:

    std::string mName;
    int mBalance;
};

#endif // DEPOSITMODEL_HPP
