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
