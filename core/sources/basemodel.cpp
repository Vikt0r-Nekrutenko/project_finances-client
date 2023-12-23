#include <QJsonObject>
#include "basemodel.hpp"

BaseModel::BaseModel(int version, bool isDeleted)
    : mIsDeleted{isDeleted}
{
    mVersion = version;
}

QJsonObject &BaseModel::completeJsonObject(QJsonObject &object)
{
    object["version"] = mVersion;
    object["is_deleted"] = int(mIsDeleted);
    return object;
}

void BaseModel::load(std::ifstream &file)
{
    file >> mVersion >> mIsDeleted;
    LocalModel::load(file);
}

void BaseModel::save(std::ofstream &file)
{
    file << " " << mVersion
         << " " << mIsDeleted;
    LocalModel::save(file);
}

void BaseModel::syncAndSave(std::ofstream &file, int version, const char *endlSym)
{
    if(mIsForCreate && mIsForDelete)
        return;
    if(mIsDeleted && mIsForDelete == false)
        return;

    if(mIsForCreate) {
        mVersion = version;
        create();
        mIsForUpdate = false;
    } else if (mIsForDelete) {
        mVersion = version;
        remove();
        mIsForUpdate = false;
    } else if (mIsForUpdate) {
        mVersion = version;
        update();
    }
    save(file);
    file << endlSym;
}
