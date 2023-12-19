#include "localmodel.hpp"


void LocalModel::save(std::ofstream &file)
{
    file << " "
         << mIsForCreate << " "
         << mIsForUpdate << " "
         << mIsDeleted << std::endl;
}

void LocalModel::load(std::ifstream &file)
{
    file >> mIsForCreate >> mIsForUpdate >> mIsDeleted;
}

bool LocalModel::isForCreate() const
{
    return mIsForCreate;
}

bool LocalModel::isChanched() const
{
    return mIsForUpdate;
}

bool LocalModel::isDeleted() const
{
    return mIsDeleted;
}
