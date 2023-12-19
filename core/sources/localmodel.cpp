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
