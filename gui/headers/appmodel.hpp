#ifndef APPMODEL_HPP
#define APPMODEL_HPP

#include "headers/depositmodelhandler.hpp"
#include "headers/debtmodelhandler.hpp"
#include "headers/categorymodelhandler.hpp"
#include "headers/operationmodelhandler.hpp"

class AppModel
{
public:

    DepositModelHandler Deposits;
    DebtModelHandler Debts;
    CategoryModelHandler Categories;
    OperationModelHandler Operations;

    AppModel();

    inline const OperationModel &selectedOperation() const { return *Operations.selectedOperation(); }

    inline const std::pair<std::string, float> &currentCurrency() const { return mQuotes[mCurrentCurrencyId]; }

    inline const std::vector<std::pair<CategoryModel *, int>> &monthlyPnlsByCategories() const { return mMonthlyGroupPnls; }

    inline int totalEarn() const { return mTotalEarn; }

    inline int totalDeposits() const { return mTotalDeposits; }

    inline int totalDebts() const { return mTotalDebts; }

    inline int totalPnL() const { return mTotalDeposits - mTotalEarn; }

    inline int todayPnL() const { return float(mTodayPnL) / mQuotes[mCurrentCurrencyId].second; }

    inline int todayProfit() const { return float(mTodayProfit) / mQuotes[mCurrentCurrencyId].second; }

    inline int todayLoss() const { return float(mTodayLoss) / mQuotes[mCurrentCurrencyId].second; }

    inline int monthlyPnL() const { return float(mMonthlyPnL) / mQuotes[mCurrentCurrencyId].second; }

    inline int monthlyProfit() const { return float(mMonthlyProfit) / mQuotes[mCurrentCurrencyId].second; }

    inline int monthlyLoss() const { return float(mMonthlyLoss) / mQuotes[mCurrentCurrencyId].second; }

    inline int yearPnL() const { return float(mYearPnL) / mQuotes[mCurrentCurrencyId].second; }

    inline int yearProfit() const { return float(mYearProfit) / mQuotes[mCurrentCurrencyId].second; }

    inline int yearLoss() const { return float(mYearLoss) / mQuotes[mCurrentCurrencyId].second; }

    void addNewOperation(const std::string &date, int amount, const std::string &category);

    void deleteOperation(int id);

    void selectOperationsList();

    void selectOperation(int id);

    void selectedOperationChangeDate(const std::string &date);

    void selectedOperationChangeDeposit(const std::string &deposit);

    void selectedOperationChangeAmount(int amount);

    void selectedOperationChangeCategory(const std::string &category);

    void addOrChangeDebt(const std::string &name, int amount, const std::string &lendOrRepay);

    int calcTotalEarn();

    int calcTotalDeposits();

    int calcTotalDebts();

    void calcPnLs();

    void calcMonthlyGroupPnL();

    void updateStats();

    void switchCurrency();

private:

    std::vector<std::pair<CategoryModel *, int>> mMonthlyGroupPnls;
    std::pair<std::string, float> mQuotes[2] {{"UAH", 1.f}, {"USD", 1.f}};
    int mTotalEarn = 0;
    int mTotalDeposits = 0;
    int mTotalDebts = 0;
    int mTodayProfit = 0,
        mTodayLoss = 0;
    int mMonthlyProfit = 0,
        mMonthlyLoss = 0;
    int mYearProfit = 0,
        mYearLoss = 0;
    int mTodayPnL = 0,
        mMonthlyPnL = 0,
        mYearPnL = 0;
    int mSelectedOperationId = 0;
    uint8_t mCurrentCurrencyId = 0;

public:

    int SelectedYear = 0, SelectedMonth = 0;
};

#endif // APPMODEL_HPP
