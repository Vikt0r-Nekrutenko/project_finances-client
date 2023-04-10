#ifndef APPMODEL_HPP
#define APPMODEL_HPP

#include "categorymodelhandler.hpp"
#include "debtmodelhandler.hpp"
#include "depositmodelhandler.hpp"
#include "operationmodelhandler.hpp"
#include <smv/imodel.hpp>

class AppModel : public stf::smv::BaseModel
{
public:
    const std::vector<DepositModel> &deposits() const;
    const std::vector<OperationModel> &operations() const;
    const std::vector<CategoryModel> &categories() const;
    const std::vector<CategoryModel> &favCategories() const;
    const std::vector<std::pair<std::string, int> > &sumByFavCategories() const;
    const std::pair<std::pair<int, std::string>, std::pair<int, std::string>> &minMaxLosses() const;
    const std::vector<OperationModel> &operationsByMonth() const;
    const std::vector<DebtModel> &debts() const;

    int sumOfAllEarnOperations() const;
    int sumOfAllDeposits() const;
    int sumOfAllDebts() const;
    int totalPnL() const;
    int todayPnL() const;
    int weekPnL() const;
    int monthPnL() const;
    int yearPnL() const;

    void updateStats();
    void updateAllHandlers();
    void getOperationsByCurrentMonth();
    void getOperationsByMonth(int year, int month);
    void selectFavCategories(int index1, int index2, int index3);

    void deleteDeposit(int index);
    void addNewDeposit(const char *name, int balance);
    void changeBalance(int index, int balance);

    void addNewLendOperation(const char *date, const char *deposit, int amount, const char *name);
    void addNewRepayOperation(const char *date, const char *deposit, int amount, const char *name);

    void addNewOperation(const char *date, const char *deposit, int amount, const char *category);
    void changeOperation(int index, const char *date, const char *deposit, int amount, const char *category);
    void deleteOperation(int index);

    void deleteCategory(int index);
    void addNewCategory(const char *name, const char *type);

    void addNewDebt(const char *name, int amount);
    void changeDebt(int index, const char *name, int amount);
    void deleteDebt(int index);


private:

    int getSum30DaysOfOperationsByCategory(const CategoryModel &category) const;
    int getSumOfAllEarnOperations() const;
    int getSumOfAllDeposits() const;
    int getSumOfAllDebts() const;
    int getTodayPnL() const;
    int getWeekPnL() const;
    int getMonthPnL() const;
    int getYearPnl() const;

    void addOrChangeDebtByName(const char *name, const int amount, const char *lendOrRepay);
    int getPnLByDays(int days) const;
    int getSumOfOperationsByCategoryType(const std::vector<const OperationModel *> &operations, const std::string &categoryType) const;
    void updateDepositBalanceByCategoryType(std::vector<CategoryModel>::iterator &category, std::vector<DepositModel>::iterator &deposit, int amount);
    void getMinMaxLossesBy30Days();

    OperationModelHandler mOperationHandler;
    DebtModelHandler mDebtHandler;
    DepositModelHandler mDepositHandler;
    CategoryModelHandler mCategoryHandler;

    std::pair<std::pair<int, std::string>, std::pair<int, std::string>> mMinMaxLosses;
    std::vector<std::pair<std::string, int>> mSumByFavCategories;
    std::vector<CategoryModel> mFavCategories;
    std::vector<OperationModel> mOperationsByMonth;

    int mSumOfAllEarnOperations = 0,
        mSumOfAllDeposits = 0,
        mSumOfAllDebts = 0,
        mTotalPnL = 0,
        mTodayPnL = 0,
        mWeekPnL = 0,
        mMonthPnL = 0,
        mYearPnL = 0;
};

#endif // APPMODEL_HPP
