#include <QJsonArray>
#include <QJsonObject>

#include "operationmodelhandler.hpp"

OperationModelHandler::OperationModelHandler()
{
    RemoteStatus status = get("operations/");
    std::ifstream file(LocalPath + "operations.txt");
    unsigned index = 0;

    if(file.is_open()) {
        while(true) {
            OperationModel tmp(0, "", "", 0, "");
            tmp.load(file);

            if(file.eof()){
                break;
            } else if(status == RemoteStatus::Failure) {
                mOperations.push_back(tmp);
            } else if(status == RemoteStatus::Success) {
                if(tmp.mIsCreated)
                    addNewOperation(tmp.mDate, tmp.mDeposit, tmp.mAmount, tmp.mCategory);
                if(tmp.mIsChanched)
                    updateOperation(index, tmp.mDate, tmp.mDeposit, tmp.mAmount, tmp.mCategory);
                if(tmp.mIsDeleted)
                    deleteOperation(index);
            }
            ++index;
        }
        file.close();
    }
}

OperationModelHandler::~OperationModelHandler()
{
    std::ofstream file(LocalPath + "operations.txt");
    for(auto &model : mOperations) {
        model.save(file);
    }
    file.close();
}

void OperationModelHandler::addNewOperation(const std::string &date, const std::string &deposit, int amount, const std::string &category)
{
    mOperations.push_back(OperationModel(
                              mOperations.empty() ? 0 : mOperations.back().mId + 1,
                              date,
                              deposit,
                              amount,
                              category));
    mOperations.back().create();
}

void OperationModelHandler::updateOperation(int index, const std::string &date, const std::string &deposit, int amount, const std::string &category)
{
    mOperations[index].mDate = date;
    mOperations[index].mDeposit = deposit;
    mOperations[index].mAmount = amount;
    mOperations[index].mCategory = category;
    mOperations[index].update();
}

void OperationModelHandler::deleteOperation(int index)
{
    mOperations[index].remove();
    mOperations.erase(mOperations.begin() + index);
}

void OperationModelHandler::parseJsonArray(const QJsonArray &replyJsonArray)
{
    mOperations.clear();
    for (const auto &var : replyJsonArray) {
        mOperations.push_back(OperationModel{
            var.toObject()["id"].toInt(),
            var.toObject()["date"].toString().toStdString(),
            var.toObject()["deposit"].toString().toStdString(),
            var.toObject()["amount"].toInt(),
            var.toObject()["category"].toString().toStdString()
        });
    }
}

const std::vector<OperationModel> &OperationModelHandler::operations() const
{
    return mOperations;
}

std::vector<OperationModel> &OperationModelHandler::operations()
{
    return mOperations;
}
