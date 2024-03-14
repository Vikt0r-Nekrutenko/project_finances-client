#ifndef CATEGORYMODELHANDLER_HPP
#define CATEGORYMODELHANDLER_HPP

#include "categorymodel.hpp"
#include "modelhandler.hpp"

class CORE_EXPORT CategoryModelHandler : public DataModelHandler
{
    friend class CategoryHandlerQuery;

public:

    class CORE_EXPORT Query : public std::vector<CategoryModel *>
    {
    public:

        Query(CategoryModelHandler *handler);
        const Query &select();
        std::vector<CategoryModel *>::const_iterator findByName(const std::string &name) const;

    private:

        CategoryModelHandler *mHandler { nullptr };

    } query {this};

    std::thread *asyncConstruct() final;
    std::thread *asyncDestruct() final;

    void addNewCategory(const std::string &name, const std::string &type);
    void updateCategoryType(int index, const std::string &type);
    void deleteCategory(int index);

protected:

    void parseJsonArray(const QJsonArray &replyJsonArray) override;

private:

    std::vector<CategoryModel> mCategories;
};

#endif // CATEGORYMODELHANDLER_HPP
