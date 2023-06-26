#ifndef APPMODEL_HPP
#define APPMODEL_HPP

#include "headers/depositmodelhandler.hpp"
#include "headers/debtmodelhandler.hpp"
#include "headers/categorymodelhandler.hpp"
#include "headers/operationmodelhandler.hpp"
#include "headers/queryresult.hpp"

class AppModel
{
public:

    DepositModelHandler Deposits;
    DebtModelHandler Debts;
    CategoryModelHandler Categories;
    OperationModelHandler Operations;

    using FavoriteCategoryList = std::vector<std::pair<std::string, int>>;
    using MinMaxLoss = std::pair<std::pair<std::string, int>, std::pair<std::string, int>>;

    AppModel();

    const OperationHandlerQuery &operationsList() const;

    const FavoriteCategoryList &favoriteCategories() const;

    const MinMaxLoss &minMaxLoss() const;

    const std::pair<std::string, float> &currentCurrency() const;

    const std::vector<std::pair<CategoryModel *, int>> &monthlyPnlsByCategories() const;

    DepositModel *selectedDeposit();

    int totalEarn() const;

    int totalDeposits() const;

    int totalDebts() const;

    int totalPnL() const;

    int todayPnL() const;

    int monthlyPnL() const;

    int yearPnL() const;

    void addNewOperation(const std::string &date, int amount, const std::string &category);

    void deleteOperation(int id);

    void selectOperationsList();

    void selectOperation(int id);

    OperationModel &selectedOperation();

    void selectedOperationChangeDate(const std::string &date);

    void selectedOperationChangeDeposit(const std::string &deposit);

    void selectedOperationChangeAmount(int amount);

    void selectedOperationChangeCategory(const std::string &category);

    void selectDeposit(size_t id);

    void addOrChangeDebt(const std::string &name, int amount, const std::string &lendOrRepay);

    void selectFavoriteCategories(int id1, int id2, int id3);

    int calcTotalEarn();

    int calcTotalDeposits();

    int calcTotalDebts();

    void calcPnLs();

    void calcMinMaxLoss();

    void calcMonthlyGroupPnL();

    void updateStats();

    void switchCurrency();

private:

    OperationHandlerQuery mOperationsList = OperationHandlerQuery(&Operations);
    FavoriteCategoryList mFavoriteCategories = FavoriteCategoryList(3);
    MinMaxLoss mMinMaxLoss;
    std::vector<std::pair<CategoryModel *, int>> mMonthlyGroupPnls;
    std::pair<std::string, float> mQuotes[2] {{"UAH", 1.f}, {"USD", 0.f}};
    DepositModel *mSelectedDeposit = nullptr;
    int mTotalEarn = 0;
    int mTotalDeposits = 0;
    int mTotalDebts = 0;
    int mTodayPnL = 0,
        mMonthlyPnL = 0,
        mYearPnL = 0;
    int mSelectedOperationId = 0;
    uint8_t mCurrentCurrencyId = 0;

public:

    int SelectedYear = 0, SelectedMonth = 0;
};

#endif // APPMODEL_HPP
