#ifndef DEPOSITMODEL_HPP
#define DEPOSITMODEL_HPP

#include "basemodel.hpp"

class CORE_EXPORT DepositModel : public BaseModel
{
    friend class DepositModelHandler;

public:

    DepositModel() = default;
    DepositModel(const std::string &name, int balance);
    DepositModel(const std::string &name, int balance, int version, bool isDeleted = 0);

    void create() override;
    void read() override;
    void update() override;
    void remove() override;

    void load(std::ifstream &file) override;
    void save(std::ofstream &file) override;

    inline const std::string &name() const { return mName; }
    inline int balance() const { return mBalance; }

private:

    void parseJsonObject(const QJsonObject &object) override;

    std::string mName;
    int mBalance;
};

#endif // DEPOSITMODEL_HPP
