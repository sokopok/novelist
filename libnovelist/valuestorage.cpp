#include "valuestorage.h"
#include "storage.h"

void ValueStorage::setDatabase(const QSqlDatabase &database)
{
    mDatabase = database;

    if (mDatabase.isOpen()) {
        executeQuery("CREATE TABLE IF NOT EXISTS `Value` (\n"
                     "  `id`	      INTEGER NOT NULL UNIQUE,\n"
                     "  `valueType` INTEGER NOT NULL,\n"
                     "  `value`     TEXT,\n"
                     "  PRIMARY KEY(`id`),\n"
                     "  FOREIGN KEY(`id`) REFERENCES Storable(`id`) ON DELETE CASCADE\n"
                     ")");

        mReloadQuery = createQuery("SELECT * FROM `Value` WHERE `id`=:id");
        mInsertQuery = createQuery(
            "INSERT INTO `Value` (`id`,`valueType`,`value`) VALUES (:id,:valueType,:value)");
        mUpdateQuery = createQuery(
            "UPDATE `Value` SET `valueType`=:valueType,`value`=:value WHERE `id`=:id");

        mReloadFieldsQuery = createQuery(
            "SELECT * FROM `Field_values` WHERE `value`=:value ORDER BY `index`");
        mUpdateFieldQuery = createQuery(
            "UPDATE `Field_values` SET `value`=:newValue,`index`=:index "
            "WHERE `field`=:field AND `value`=:oldValue");
    }

    emitDatabaseChanged();
}

Node *ValueStorage::createNode()
{
    mNodes.append(new Value{storage(), storage()});
    return mNodes.last();
}

bool ValueStorage::insertNode(Node *node)
{
    Transaction tx{Transaction::WriteModified, node, storage()};

    const int oldRowid = node->rowid();

    if (!storage()->nodeStorage()->insertNode(node))
        return false;

    Value *value = static_cast<Value *>(node);

    QVariant valueValue = value->value();
    if (Node *node = valueValue.value<Node *>())
        valueValue = node->rowid();

    if (!executeQuery(mInsertQuery,
                      QVariantMap{{":id", value->rowid()},
                                  {":value", valueValue},
                                  {":valueType", value->valueType()}}))
        return handleError(this, "insertNode", mInsertQuery), false;

    for (Field *field : value->fields()) {
        if (!executeQuery(mUpdateFieldQuery,
                          QVariantMap{{":oldValue", oldRowid},
                                      {":newValue", value->rowid()},
                                      {":index", value->indexIn(field)},
                                      {":field", field->rowid()}}))
            return handleError(this, "insertNode", mUpdateFieldQuery), false;
    }

    tx.commit();

    return true;
}

bool ValueStorage::updateNode(Node *node)
{
    Transaction tx{Transaction::WriteModified, node, storage()};

    if (!storage()->nodeStorage()->updateNode(node))
        return false;

    Value *v = static_cast<Value *>(node);

    if (!executeQuery(mUpdateQuery,
                      QVariantMap{{":value", v->value()},
                                  {":id", v->rowid()},
                                  {":valueType", v->valueType()}}))
        return handleError(this, "updateNode", mUpdateQuery), false;

    tx.commit();

    return true;
}

bool ValueStorage::reloadNode(Node *node)
{
    Transaction tx{Transaction::ReadModified, node, storage()};

    if (!storage()->nodeStorage()->reloadNode(node))
        return false;

    Value *value = static_cast<Value *>(node);

    if (!executeQuery(mReloadQuery, {value->rowid()}))
        return handleError(this, "reloadNode", mReloadQuery), false;

    if (!mReloadQuery.next())
        return handleError(this, "reloadNode", "result set is empty"), false;

    value->setValue(mReloadQuery.value("value"));
    value->setValueType(mReloadQuery.value("valueType").toInt());

    if (!executeQuery(mReloadFieldsQuery, QVariantMap{{":value", value->rowid()}}))
        return handleError(this, "reloadNode", mReloadFieldsQuery), false;

    QList<Field *> fields;
    while (mReloadFieldsQuery.next()) {
        const int rowid = mReloadFieldsQuery.value("field").toInt();
        if (Field *field = qobject_cast<Field *>(storage()->fieldStorage()->field(rowid)))
            fields.append(field);
        else
            handleError(this, "reloadNode", "could not load field");
    }

    value->setFields(fields);

    tx.commit();

    return true;
}

bool ValueStorage::removeNode(int rowid)
{
    if (rowid <= 0)
        return handleError(this, "removeNode", "rowid is invalid"), false;

    Transaction tx{Transaction::WriteModified, mNodesByRowid.value(rowid), storage()};

    if (!storage()->nodeStorage()->removeNode(rowid))
        return false;

    tx.commit();

    return true;
}
