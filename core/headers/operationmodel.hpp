#ifndef OPERATIONMODEL_HPP
#define OPERATIONMODEL_HPP

#include "crudmodel.hpp"
#include "localmodel.hpp"

class DepositModel;
class CategoryModel;

class CORE_EXPORT OperationModel : public CRUDModel, public LocalModel
{
    friend class OperationModelHandler;
public:
    OperationModel(int id, const std::string &date, const std::string &deposit, int amount, const std::string &category);

    void create() override;
    void read() override;
    void update() override;
    void remove() override;
    void parseJsonObject(const QJsonObject &) override;

    void save(std::ofstream &file) override;
    void load(std::ifstream &file) override;

    const std::string &date() const;
    const std::string &deposit() const;
    const std::string &category() const;
    int id() const;
    int amount() const;

    QDateTime rawDate() const;
    DepositModel *rawDeposit() const;
    CategoryModel *rawCategory() const;

private:

    std::string mDate;
    std::string mDeposit;
    std::string mCategory;
    int mId, mAmount;    
};

#endif // OPERATIONMODEL_HPP
