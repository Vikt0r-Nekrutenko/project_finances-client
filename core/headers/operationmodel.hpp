#ifndef OPERATIONMODEL_HPP
#define OPERATIONMODEL_HPP

#include "basemodel.hpp"

class DepositModel;
class CategoryModel;
class DepositModelHandler;
class CategoryModelHandler;

class CORE_EXPORT OperationModel : public BaseModel
{
    friend class OperationModelHandler;

public:

    OperationModel() = default;
    OperationModel(int id, const std::string &date, const std::string &deposit, int amount, const std::string &category);
    OperationModel(int id, const std::string &date, const std::string &deposit, int amount, const std::string &category, int version, bool isDeleted = false);

    void create() override;
    void read() override;
    void update() override;
    void remove() override;

    void save(std::ofstream &file) override;
    void load(std::ifstream &file) override;

    inline const std::string &date() const { return mDate; }
    inline const std::string &deposit() const { return mDeposit; }
    inline const std::string &category() const { return mCategory; }
    inline int id() const { return mId; }
    inline int amount() const { return mAmount; }

    const CategoryModel &rawCategory(CategoryModelHandler &handler) const;

private:

    void parseJsonObject(const QJsonObject &) override;

    std::string mDate;
    std::string mDeposit;
    std::string mCategory;
    int mId, mAmount;    
};

#endif // OPERATIONMODEL_HPP
