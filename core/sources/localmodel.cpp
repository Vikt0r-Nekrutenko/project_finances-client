#include "localmodel.hpp"


void LocalModel::save(std::ofstream &file)
{
    file << " "
         << mIsForCreate << " "
         << mIsForUpdate << " "
         << mIsForDelete << std::endl;
}

void LocalModel::load(std::ifstream &file)
{
    file >> mIsForCreate >> mIsForUpdate >> mIsForDelete;
}

bool LocalModel::isForCreate() const
{
    return mIsForCreate;
}

bool LocalModel::isForUpdate() const
{
    return mIsForUpdate;
}

bool LocalModel::isDeleted() const
{
    return mIsForDelete;
}
