#ifndef LIBNOVELIST_VALUESTORAGE_H
#define LIBNOVELIST_VALUESTORAGE_H

#include "nodestorage.h"
#include "value.h"

class ValueStorage : public BaseStorage
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit ValueStorage(Storage* parent = nullptr)
        : BaseStorage{parent}
    {}

    void setDatabase(const QSqlDatabase& database) override;

    [[nodiscard]] Q_INVOKABLE Value* value() { return static_cast<Value*>(node()); }
    [[nodiscard]] Q_INVOKABLE Value* value(int rowid) { return static_cast<Value*>(node(rowid)); }
    [[nodiscard]] Q_INVOKABLE Value* createValue(ValueType* nodeType = nullptr,
                                                 const QString& label = {},
                                                 const QString& info = {},
                                                 const QString& icon = {})
    {
        if (Value* e = static_cast<Value*>(createNode())) {
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

    bool updateValue(Value* value)
    {
        if (!value || value->rowid() <= 0)
            return false;

        Transaction tx{Transaction::Write, value, storage()};

        QSqlQuery q = createQuery("UPDATE Value SET value=? WHERE id=?");
        if (!executeQuery(q, {value->value(), value->rowid()})) {
            handleError(this, "updateValue", q);
            return false;
        }

        tx.commit();

        return true;
    }
    bool updateValueType(Value* value)
    {
        if (!value || value->rowid() <= 0)
            return false;

        Transaction tx{Transaction::Write, value, storage()};

        QSqlQuery q = createQuery("UPDATE Value SET valueType=? WHERE id=?");
        if (!executeQuery(q, {value->valueType(), value->rowid()})) {
            handleError(this, "updateValueType", q);
            return false;
        }

        tx.commit();

        return true;
    }

    friend class Value;
    friend class Storage;

    QSqlQuery mReloadQuery;
    QSqlQuery mInsertQuery;
    QSqlQuery mUpdateQuery;
    QSqlQuery mReloadFieldsQuery;
    QSqlQuery mInsertFieldsQuery;
    QSqlQuery mUpdateFieldQuery;
};

#endif // LIBNOVELIST_VALUESTORAGE_H
