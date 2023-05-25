#include "localmodel.hpp"


void LocalModel::save(std::ofstream &file)
{
    file << " "
         << mIsCreated << " "
         << mIsChanched << " "
         << mIsDeleted << std::endl;
}

void LocalModel::load(std::ifstream &file)
{
    file >> mIsCreated >> mIsChanched >> mIsDeleted;
}

bool LocalModel::isCreated() const
{
    return mIsCreated;
}

bool LocalModel::isChanched() const
{
    return mIsChanched;
}

bool LocalModel::isDeleted() const
{
    return mIsDeleted;
}
