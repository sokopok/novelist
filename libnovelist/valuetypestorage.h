#ifndef LIBNOVELIST_VALUETYPESTORAGE_H
#define LIBNOVELIST_VALUETYPESTORAGE_H

#include "nodetypestorage.h"
#include "valuetype.h"

class ValueTypeStorage : public BaseTypeStorage
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit ValueTypeStorage(Storage* parent = nullptr)
        : BaseTypeStorage{parent}
    {}

    void setDatabase(const QSqlDatabase& database) override;

    [[nodiscard]] Q_INVOKABLE ValueType* valueType() { return static_cast<ValueType*>(node()); }
    [[nodiscard]] Q_INVOKABLE ValueType* valueType(int rowid)
    {
        return static_cast<ValueType*>(node(rowid));
    }
    [[nodiscard]] Q_INVOKABLE ValueType* valueType(const QString& name)
    {
        return static_cast<ValueType*>(nodeType(name));
    }
    [[nodiscard]] Q_INVOKABLE ValueType* createValueType(const QString& name,
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

        if (ValueType* valueType = static_cast<ValueType*>(createNode())) {
            mNodesByName.insert(name, valueType);
            valueType->setName(name);
            valueType->setLabel(label);
            valueType->setInfo(info);
            valueType->setIcon(icon);
            return valueType;
        }

        return nullptr;
    }

    QList<ValueType*> allValueTypes() const { return toDerived<ValueType>(mNodes); }

protected:
    [[nodiscard]] Node* createNode() override;
    bool insertNode(Node* node) override;
    bool updateNode(Node* node) override;
    bool reloadNode(Node* node) override;
    bool removeNode(int rowid) override;

    friend class ValueType;
    friend class Storage;

    QSqlQuery mReloadQuery;
    QSqlQuery mInsertQuery;
    QSqlQuery mUpdateQuery;
    QSqlQuery mReloadFieldTypesQuery;
    QSqlQuery mInsertFieldTypesQuery;
};

#endif // LIBNOVELIST_VALUETYPESTORAGE_H
