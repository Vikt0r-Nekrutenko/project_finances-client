#include "localmodel.hpp"


void LocalModel::save(std::ofstream &file)
{
    file << " "
         << mIsForCreate << " "
         << mIsChanched << " "
         << mIsDeleted << std::endl;
}

void LocalModel::load(std::ifstream &file)
{
    file >> mIsForCreate >> mIsChanched >> mIsDeleted;
}

bool LocalModel::isForCreate() const
{
    return mIsForCreate;
}

bool LocalModel::isChanched() const
{
    return mIsChanched;
}

bool LocalModel::isDeleted() const
{
    return mIsDeleted;
}
