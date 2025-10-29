#ifndef LIBNOVELIST_FIELDTYPESTORAGE_H
#define LIBNOVELIST_FIELDTYPESTORAGE_H

#include "fieldtype.h"
#include "nodetypestorage.h"

class FieldTypeStorage : public BaseTypeStorage
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit FieldTypeStorage(Storage* parent = nullptr)
        : BaseTypeStorage{parent}
    {}

    void setDatabase(const QSqlDatabase& database) override;

    [[nodiscard]] Q_INVOKABLE FieldType* fieldType() { return static_cast<FieldType*>(node()); }
    [[nodiscard]] Q_INVOKABLE FieldType* fieldType(int rowid)
    {
        return static_cast<FieldType*>(node(rowid));
    }
    [[nodiscard]] Q_INVOKABLE FieldType* fieldType(const QString& name)
    {
        return static_cast<FieldType*>(nodeType(name));
    }
    [[nodiscard]] Q_INVOKABLE FieldType* createFieldType(const QString& name,
                                                         const QString& label = {},
                                                         const QString& info = {},
                                                         const QString& icon = {})
    {
        if (name.isEmpty())
            return handleError(this, "removeNode", "name is empty"), nullptr;

        if (mNodesByName.contains(name))
            return handleError(
                       this,
                       "removeNode",
                       QStringLiteral("storage already contains a type with name '%1'").arg(name)),
                   nullptr;

        if (FieldType* fieldType = static_cast<FieldType*>(createNode())) {
            mNodesByName.insert(name, fieldType);
            fieldType->setName(name);
            fieldType->setLabel(label);
            fieldType->setInfo(info);
            fieldType->setIcon(icon);
            return fieldType;
        }

        return nullptr;
    }

    QList<FieldType*> allFieldTypes() const { return toDerived<FieldType>(mNodes); }

protected:
    [[nodiscard]] Node* createNode() override;
    bool insertNode(Node* node) override;
    bool updateNode(Node* node) override;
    bool reloadNode(Node* node) override;
    bool removeNode(int rowid) override;

    bool updateValueTypes(FieldType* fieldType);
    bool updateAllowedTypes(FieldType* fieldType);
    bool updateMinOccurs(FieldType* fieldType);
    bool updateMaxOccurs(FieldType* fieldType);

    friend class FieldType;
    friend class Storage;

    QSqlQuery mReloadQuery;
    QSqlQuery mInsertQuery;
    QSqlQuery mUpdateQuery;
    QSqlQuery mReloadElementTypesQuery;
    QSqlQuery mInsertElementTypesQuery;
    QSqlQuery mReloadValueTypesQuery;
    QSqlQuery mInsertValueTypesQuery;
    QSqlQuery mRemoveValueTypesQuery;
    QSqlQuery mReloadAllowedTypesQuery;
    QSqlQuery mInsertAllowedTypesQuery;
    QSqlQuery mRemoveAllowedTypesQuery;
};

#endif // LIBNOVELIST_FIELDTYPESTORAGE_H
