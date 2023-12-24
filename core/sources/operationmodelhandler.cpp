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
        [&](QJsonValueConstRef var) {
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
    for(Query::iterator it = begin(); it != end(); )
        it = ((*it)->deposit() != deposit) ? erase(it) : ++it;
    return *this;
}

OperationModelHandler::Query &OperationModelHandler::Query::filterByCategoryName(const std::string &name)
{
    for(Query::iterator it = begin(); it != end(); )
        it = ((*it)->category() != name) ? erase(it) : ++it;
    return *this;
}

OperationModelHandler::Query &OperationModelHandler::Query::filterByCategoryType(CategoryModelHandler &handler, const std::string &type)
{
    for(Query::iterator it = begin(); it != end(); )
        it = ((*it)->rawCategory(handler).type() != type) ? erase(it) : ++it;
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
    for(Query::iterator it = begin(); it != end(); )
        it = (QDateTime().fromString((*it)->date().c_str(), "yyyy-MM-dd").date().year() != year) ? erase(it) : ++it;
    return *this;
}

OperationModelHandler::Query &OperationModelHandler::Query::filterByMonth(const int month)
{
    for(Query::iterator it = begin(); it != end(); )
        it = (QDateTime().fromString((*it)->date().c_str(), "yyyy-MM-dd").date().month() != month) ? erase(it) : ++it;
    return *this;
}

OperationModelHandler::Query &OperationModelHandler::Query::filterByDay(const int day)
{
    for(Query::iterator it = begin(); it != end(); )
        it = (QDateTime().fromString((*it)->date().c_str(), "yyyy-MM-dd").date().day() != day) ? erase(it) : ++it;
    return *this;
}

OperationModel *OperationModelHandler::Query::at(size_t index)
{
    auto it = begin();
    for(size_t i = 0; i != index; ++i, ++it);
    return *it;
}

int OperationModelHandler::Query::sum() const
{
    int result = 0;
    for(Query::const_iterator it = begin(); it != end(); ++it)
        result += (*it)->amount();
    return result;
}
