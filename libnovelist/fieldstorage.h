#ifndef LIBNOVELIST_FIELDSTORAGE_H
#define LIBNOVELIST_FIELDSTORAGE_H

#include "field.h"
#include "nodestorage.h"

class FieldStorage : public BaseStorage
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit FieldStorage(Storage* parent = nullptr)
        : BaseStorage{parent}
    {}

    void setDatabase(const QSqlDatabase& database) override;

    [[nodiscard]] Q_INVOKABLE Field* field() { return static_cast<Field*>(node()); }
    [[nodiscard]] Q_INVOKABLE Field* field(int rowid) { return static_cast<Field*>(node(rowid)); }
    [[nodiscard]] Q_INVOKABLE Field* createField(FieldType* nodeType = nullptr,
                                                 const QString& label = {},
                                                 const QString& info = {},
                                                 const QString& icon = {})
    {
        if (Field* e = static_cast<Field*>(createNode())) {
            e->setNodeType(nodeType);
            e->setLabel(label);
            e->setInfo(info);
            e->setIcon(icon);
            return e;
        }
        return nullptr;
    }

protected:
    [[nodiscard]] Node* createNode() override;
    bool insertNode(Node* node) override;
    bool updateNode(Node* node) override;
    bool reloadNode(Node* node) override;
    bool removeNode(int rowid) override;

    bool updateValues(Field* field);
    bool updateAllowedTypes(Field* field);
    bool updateMinOccurs(Field* field);
    bool updateMaxOccurs(Field* field);

    friend class Field;
    friend class Storage;

    QSqlQuery mReloadQuery;
    QSqlQuery mInsertQuery;
    QSqlQuery mUpdateQuery;
    QSqlQuery mReloadElementsQuery;
    QSqlQuery mInsertElementsQuery;
    QSqlQuery mReloadValuesQuery;
    QSqlQuery mInsertValuesQuery;
    QSqlQuery mRemoveValuesQuery;
    QSqlQuery mReloadAllowedTypesQuery;
    QSqlQuery mInsertAllowedTypesQuery;
    QSqlQuery mRemoveAllowedTypesQuery;
};

#endif // LIBNOVELIST_FIELDSTORAGE_H
