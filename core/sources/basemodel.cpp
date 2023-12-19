#include <QJsonObject>
#include "basemodel.hpp"

QJsonObject &BaseModel::completeJsonObject(QJsonObject &object)
{
    object["version"] = mVersion;
    object["is_deleted"] = int(mIsForDelete);
    return object;
}

void BaseModel::load(std::ifstream &file)
{
    file >> mVersion;
    LocalModel::load(file);
}

void BaseModel::save(std::ofstream &file)
{
    file << " " << mVersion;
    LocalModel::save(file);
}
