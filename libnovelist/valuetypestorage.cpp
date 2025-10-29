#include "valuetypestorage.h"
#include "fieldtypestorage.h"
#include "storage.h"

void ValueTypeStorage::setDatabase(const QSqlDatabase &database)
{
    mDatabase = database;

    if (mDatabase.isOpen()) {
        executeQuery("CREATE TABLE IF NOT EXISTS `ValueType` (\n"
                     "  `id` INTEGER NOT NULL UNIQUE,\n"
                     "  PRIMARY KEY(`id`),\n"
                     "  FOREIGN KEY(`id`) REFERENCES Storable(`id`) ON DELETE CASCADE\n"
                     ")");

        mReloadQuery = createQuery("SELECT * FROM `ValueType` WHERE `id`=:id");
        mReloadFieldTypesQuery = createQuery(
            "SELECT * FROM `FieldType_valueTypes` WHERE `valueType`=:valueType ORDER BY `index`");
        mInsertQuery = createQuery("INSERT INTO `ValueType` (`id`) VALUES (:id)");
        mUpdateQuery = createQuery("UPDATE `ValueType` SET `id`=:id WHERE `id`=:id");
    }

    emitDatabaseChanged();
}

Node *ValueTypeStorage::createNode()
{
    mNodes.append(new ValueType{storage(), storage()});
    return mNodes.last();
}

bool ValueTypeStorage::insertNode(Node *node)
{
    Transaction tx{Transaction::WriteModified, node, storage()};

    if (!storage()->nodeTypeStorage()->insertNode(node))
        return false;

    ValueType *valueType = static_cast<ValueType *>(node);

    if (!executeQuery(mInsertQuery, QVariantMap{{":id", valueType->rowid()}}))
        return handleError(this, "insertNode", mInsertQuery), false;

    tx.commit();

    return true;
}

bool ValueTypeStorage::updateNode(Node *node)
{
    Transaction tx{Transaction::WriteModified, node, storage()};

    if (!storage()->nodeTypeStorage()->updateNode(node))
        return false;

    // ValueType *valueType = static_cast<ValueType *>(node);

    // if (!executeQuery(mUpdateQuery, QVariantMap{{":id", vt->rowid()}})) {
    //     handleError("");
    //     return false;
    // }

    tx.commit();

    return true;
}

bool ValueTypeStorage::reloadNode(Node *node)
{
    Transaction tx{Transaction::ReadModified, node, storage()};

    if (!storage()->nodeTypeStorage()->reloadNode(node))
        return false;

    ValueType *valueType = static_cast<ValueType *>(node);

    if (!executeQuery(mReloadQuery, {valueType->rowid()}))
        return handleError(this, "reloadNode", mReloadQuery), false;

    if (!mReloadQuery.next())
        return handleError(this, "reloadNode", "result set is empty"), false;

    if (!executeQuery(mReloadFieldTypesQuery, QVariantMap{{":valueType", valueType->rowid()}}))
        return handleError(this, "reloadNode", mReloadFieldTypesQuery), false;

    QList<FieldType *> fts;
    while (mReloadFieldTypesQuery.next()) {
        const int rowid = mReloadFieldTypesQuery.value("fieldType").toInt();
        if (FieldType *ft = qobject_cast<FieldType *>(
                storage()->fieldTypeStorage()->fieldType(rowid)))
            fts.append(ft);
        else
            handleError(this, "reloadNode", "could not load fieldtype");
    }

    valueType->setFieldTypes(fts);

    tx.commit();

    return true;
}

bool ValueTypeStorage::removeNode(int rowid)
{
    if (rowid <= 0)
        return handleError(this, "removeNode", "rowid is invalid"), false;

    Transaction tx{Transaction::WriteModified, mNodesByRowid.value(rowid), storage()};

    if (!storage()->nodeTypeStorage()->removeNode(rowid))
        return false;

    tx.commit();

    return true;
}
