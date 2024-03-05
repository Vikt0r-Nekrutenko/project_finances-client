#include <QJsonArray>
#include <QJsonObject>

#include "operationmodelhandler.hpp"
#include "categorymodel.hpp"

OperationModelHandler::OperationModelHandler()
{
    syncAndLoad<OperationModel>("operations", mOperations);
    query.select();
}

OperationModelHandler::~OperationModelHandler()
{
    syncAndSave<OperationModel>("operations.txt", mOperations);
}

void OperationModelHandler::addNewOperation(const std::string &date, const std::string &deposit, int amount, const std::string &category)
{
    int id = mOperations.empty() ? 0 : mOperations.back().id() + 1;
    addNewItem<OperationModel, std::vector<OperationModel>::iterator>(
        {id, date, deposit, amount, category},
        mOperations,
        [&](const OperationModel &model) {
            return model.mId == id;
        },
        [&](OperationModel &model) {
            model.mDate = date;
            model.mDeposit = deposit;
            model.mAmount = amount;
            model.mCategory = category;
        });
    query.select();
}

void OperationModelHandler::updateOperation(int index, const std::string &date, const std::string &deposit, int amount, const std::string &category)
{
    ++mVersion;
    OperationModel *changingModel = query.at(index);
    changingModel->mDate = date;
    changingModel->mDeposit = deposit;
    changingModel->mAmount = amount;
    changingModel->mCategory = category;
    changingModel->mIsForUpdate = true;
}

void OperationModelHandler::deleteOperation(int index)
{
    deleteItem<OperationModel>(query.at(index));
    query.select();
}

void OperationModelHandler::selectOperation(int index)
{
    mSelectedOperation = query.at(index);
}

void OperationModelHandler::changeDate(const std::string &date)
{
    ++mVersion;
    mSelectedOperation->mDate = date;
    mSelectedOperation->mIsForUpdate = true;
}

void OperationModelHandler::changeDeposit(const std::string &deposit)
{
    ++mVersion;
    mSelectedOperation->mDeposit = deposit;
    mSelectedOperation->mIsForUpdate = true;
}

void OperationModelHandler::changeAmount(int amount)
{
    ++mVersion;
    mSelectedOperation->mAmount = amount;
    mSelectedOperation->mIsForUpdate = true;
}

void OperationModelHandler::changeCategory(const std::string &category)
{
    ++mVersion;
    mSelectedOperation->mCategory = category;
    mSelectedOperation->mIsForUpdate = true;
}

void OperationModelHandler::parseJsonArray(const QJsonArray &replyJsonArray)
{
    parseAndMerge<OperationModel, std::vector<OperationModel>::iterator>(
        "operations",
        replyJsonArray,
        mOperations,
        [&](const OperationModel &remoteModel, const OperationModel &localModel) {
            return remoteModel.mId == localModel.mId;
        },
        [&](const QJsonValue &var) {
            return OperationModel{
                var.toObject()["id"].toInt(),
                var.toObject()["date"].toString().toStdString(),
                var.toObject()["deposit"].toString().toStdString(),
                var.toObject()["amount"].toInt(),
                var.toObject()["category"].toString().toStdString(),
                var.toObject()["version"].toInt(),
                bool(var.toObject()["is_deleted"].toInt())
            };
        });
}

OperationModelHandler::Query::Query(OperationModelHandler *handler)
    : mHandler{handler} { }

OperationModelHandler::Query &OperationModelHandler::Query::select()
{
    clear();
    for(size_t i = 0; i < mHandler->mOperations.size(); ++i)
        if(mHandler->mOperations.at(i).mIsDeleted == false)
            push_back(&mHandler->mOperations.at(i));
    return *this;
}

OperationModelHandler::Query &OperationModelHandler::Query::filterByDeposit(const std::string &deposit)
{
    erase(std::remove_if(begin(), end(), [&](OperationModel *model) {
              return model->mDeposit != deposit; }), end());
    return *this;
}

OperationModelHandler::Query &OperationModelHandler::Query::filterByCategoryName(const std::string &category)
{
    erase(std::remove_if(begin(), end(), [&](OperationModel *model) {
        return model->category() != category; }), end());
    return *this;
}

OperationModelHandler::Query &OperationModelHandler::Query::filterByCategoryType(CategoryModelHandler &handler, const std::string &type)
{
    try {
        erase(std::remove_if(begin(), end(), [&](OperationModel *model) {
            return model->rawCategory(handler).type() != type; }), end());
    } catch(const std::invalid_argument &ex) {
        log().push_back(std::string{"OperationModelHandler -> filterByCategoryType() -> "} + ex.what());
    }
    return *this;
}

OperationModelHandler::Query &OperationModelHandler::Query::filterByCurrentMonth()
{
    const QDate &currentDate = QDate().currentDate();
    return filterByMonth(currentDate.month());
}

OperationModelHandler::Query &OperationModelHandler::Query::filterByCurrentYear()
{
    const QDate &currentDate = QDate().currentDate();
    return filterByYear(currentDate.year());
}

OperationModelHandler::Query &OperationModelHandler::Query::filterByCurrentDay()
{
    const QDate &currentDate = QDate().currentDate();
    return filterByDay(currentDate.day());
}

OperationModelHandler::Query &OperationModelHandler::Query::filterByYear(const int year)
{
    erase(std::remove_if(begin(), end(), [&](OperationModel *model) {
        int _year = std::stoi(model->mDate.substr(0, 4));
        return _year != year; }), end());
    return *this;
}

OperationModelHandler::Query &OperationModelHandler::Query::filterByMonth(const int month)
{
    erase(std::remove_if(begin(), end(), [&](OperationModel *model) {
        int _month = std::stoi(model->mDate.substr(5, 7));
        return _month != month; }), end());
    return *this;
}

OperationModelHandler::Query &OperationModelHandler::Query::filterByDay(const int day)
{
    erase(std::remove_if(begin(), end(), [&](OperationModel *model) {
        int _day = std::stoi(model->mDate.substr(8, 10));
        return _day != day; }), end());
    return *this;
}

int OperationModelHandler::Query::sum() const
{
    return std::accumulate(begin(), end(), 0, [](int accumulator, const OperationModel *model) { return accumulator + model->mAmount; });
}
