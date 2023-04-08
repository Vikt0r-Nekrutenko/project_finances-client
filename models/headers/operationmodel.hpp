#ifndef OPERATIONMODEL_HPP
#define OPERATIONMODEL_HPP

#include "crudmodel.hpp"

class OperationModel : public CRUDModel
{
    friend class OperationModelHandler;
public:
    OperationModel(int id, const std::string &date, const std::string &deposit, int amount, const std::string &category);

    void create() override;
    void read() override;
    void update() override;
    void remove() override;
    void parseJsonObject(const QJsonObject &) override;

    const std::string &date() const;
    const std::string &deposit() const;
    const std::string &category() const;
    int id() const;
    int amount() const;

private:

    std::string mDate;
    std::string mDeposit;
    std::string mCategory;
    int mId, mAmount;
};

#endif // OPERATIONMODEL_HPP
