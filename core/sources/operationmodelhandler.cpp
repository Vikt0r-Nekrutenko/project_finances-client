#include <QJsonArray>
#include <QJsonObject>

#include "operationmodelhandler.hpp"
#include "categorymodel.hpp"

OperationModelHandler::OperationModelHandler()
{
    std::ifstream file(LocalPath + "operations.txt");

    if(file.is_open()) {
        while(true) {
            OperationModel tmp(0, "", "", 0, "");
            tmp.load(file);
            if(tmp.version() > mVersion)
                mVersion = tmp.version();

            if(file.eof())
                break;

            mOperations.push_back(tmp);

            if(tmp.mIsForCreate) {
                mOperations.back().create();
            }
            if(tmp.mIsForUpdate) {
                mOperations.back().update();
            }
            if(tmp.mIsForDelete) {
                mOperations.back().remove();
            }
        }
        file.close();
    }
    // get("operations/");
}

OperationModelHandler::~OperationModelHandler()
{
    // std::ofstream file(LocalPath + "operations.txt");
    // for(auto &model : mOperations) {
    //     model.save(file);
    // }
    // file.close();
}

void OperationModelHandler::addNewOperation(const std::string &date, const std::string &deposit, int amount, const std::string &category)
{
    mOperations.push_back(OperationModel{
        0,
        date,
        deposit,
        amount,
        category,
        ++mVersion
    });
    mOperations.back().create();
}

void OperationModelHandler::updateOperation(int index, const std::string &date, const std::string &deposit, int amount, const std::string &category)
{
    mOperations[index].mDate = date;
    mOperations[index].mDeposit = deposit;
    mOperations[index].mAmount = amount;
    mOperations[index].mCategory = category;
    mOperations[index].mVersion = ++mVersion;
    mOperations[index].update();
}

void OperationModelHandler::deleteOperation(int index)
{
    mOperations[index].mVersion = ++mVersion;
    mOperations[index].mIsDeleted = true;
    mOperations[index].remove();
    mOperations[index].remove();
}

void OperationModelHandler::parseJsonArray(const QJsonArray &replyJsonArray)
{
    int count = 0;
    for (const auto &var : replyJsonArray) {
        mOperations.push_back(OperationModel{
            var.toObject()["id"].toInt(),
            var.toObject()["date"].toString().toStdString(),
            var.toObject()["deposit"].toString().toStdString(),
            var.toObject()["amount"].toInt(),
            var.toObject()["category"].toString().toStdString(),
            var.toObject()["version"].toInt(),
            bool(var.toObject()["is_deleted"].toInt())
        });
        if(mOperations.back().version() > mVersion)
            mVersion = mOperations.back().version();
        ++count;
    }
    log().push_back({"Operations received: " + std::to_string(count)});
}

std::vector<OperationModel>::iterator OperationModelHandler::at(int id)
{
    return std::find_if(mOperations.begin(), mOperations.end(), [&](const OperationModel &model){
        return model.id() == id;
    });
}

OperationModelHandler::Query::Query(OperationModelHandler *handler)
    : mHandler{handler} { }

OperationModelHandler::Query &OperationModelHandler::Query::select()
{
    clear();
    for(size_t i = 0; i < mHandler->mOperations.size(); ++i)
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

const OperationModel &OperationModelHandler::Query::at(size_t index) const
{
    auto it = begin();
    for(size_t i = 0; i != index; ++i, ++it);
    return *(*it);
}

int OperationModelHandler::Query::sum() const
{
    int result = 0;
    for(Query::const_iterator it = begin(); it != end(); ++it)
        result += (*it)->amount();
    return result;
}
