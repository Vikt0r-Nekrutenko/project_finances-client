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
