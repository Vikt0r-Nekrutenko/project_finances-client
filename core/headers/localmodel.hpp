#ifndef LOCALMODEL_HPP
#define LOCALMODEL_HPP

#include <fstream>
#include "core_global.h"

const std::string LocalPath = "local/";

class CORE_EXPORT LocalModel
{
public:

    virtual void save(std::ofstream &file);

    virtual void load(std::ifstream &file);

    inline bool isForCreate() const { return mIsForCreate; }

    inline bool isForUpdate() const { return mIsForUpdate; }

    inline bool isForDelete() const { return mIsForDelete; }

protected:

    bool mIsForCreate = false;
    bool mIsForUpdate = false;
    bool mIsForDelete = false;
};

#endif // LOCALMODEL_HPP
