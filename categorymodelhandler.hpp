#ifndef CATEGORYMODELHANDLER_HPP
#define CATEGORYMODELHANDLER_HPP

#include "categorymodel.hpp"
#include "modelhandler.hpp"

class CategoryModelHandler : public DataModelHandler
{
public:

    CategoryModelHandler();

    void addNewCategory(const QString &name, const QString &type);
    void deleteCategory(int index);
    void parseJsonArray(const QJsonArray &replyJsonArray) override;

    const QVector<CategoryModel> &categories() const;
    QVector<CategoryModel> &categories();

    QList<CategoryModel>::iterator findByName(const QString &name);

private:

    QVector<CategoryModel> mCategories;
};

#endif // CATEGORYMODELHANDLER_HPP
