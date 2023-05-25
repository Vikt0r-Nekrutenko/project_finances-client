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

    bool isCreated() const;

    bool isChanched() const;

    bool isDeleted() const;

protected:

    bool mIsCreated = false;
    bool mIsChanched = false;
    bool mIsDeleted = false;
};

#endif // LOCALMODEL_HPP
