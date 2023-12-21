#ifndef MODELHANDLER_HPP
#define MODELHANDLER_HPP

#include "datamodel.hpp"

class BaseModel;

class DataModelHandler : public DataModel
{
public:

    virtual ~DataModelHandler() = default;
    RemoteStatus get(const std::string &additionalPath);
    inline std::vector<size_t> &listOfChanges() { return mListOfChanges; }

protected:

    void applyChanges(BaseModel *changeModel);

    virtual void parseJsonArray(const QJsonArray &array) = 0;
    void addNewChange(const size_t index);

    std::vector<size_t> mListOfChanges;
};

class CORE_EXPORT MonoBankDataHandler
{
public:

    struct Currency
    {
        int code;
        float buy;
        float sell;
    };

    MonoBankDataHandler();
    const std::vector<Currency> &quotes() const;
    std::vector<Currency>::const_iterator usd() const;

private:

    std::vector<Currency> mQuotes;
};

#endif // MODELHANDLER_HPP
