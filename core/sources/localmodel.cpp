#include "localmodel.hpp"


void LocalModel::save(std::ofstream &file)
{
    file << " "
         << mIsForCreate << " "
         << mIsForUpdate << " "
         << mIsForDelete;
}

void LocalModel::load(std::ifstream &file)
{
    file >> mIsForCreate >> mIsForUpdate >> mIsForDelete;
}
