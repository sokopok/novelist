#include "fieldtypestorage.h"
#include "storage.h"
#include "valuetypestorage.h"

void FieldTypeStorage::setDatabase(const QSqlDatabase &database)
{
    mDatabase = database;

    if (mDatabase.isOpen()) {
        executeQuery("CREATE TABLE IF NOT EXISTS `FieldType` (\n"
                     "  `id` INTEGER NOT NULL UNIQUE,\n"
                     "  `minOccurs` INTEGER NOT NULL,\n"
                     "  `maxOccurs` INTEGER NOT NULL,\n"
                     "  PRIMARY KEY(`id`),\n"
                     "  FOREIGN KEY(`id`) REFERENCES Storable(`id`) ON DELETE CASCADE\n"
                     ")");
        executeQuery("CREATE TABLE IF NOT EXISTS `FieldType_valueTypes` (\n"
                     "  `id`	        INTEGER NOT NULL UNIQUE,\n"
                     "  `index`	    INTEGER NOT NULL,\n"
                     "  `fieldType` INTEGER NOT NULL,\n"
                     "  `valueType`   INTEGER NOT NULL,\n"
                     "  PRIMARY KEY(`id` AUTOINCREMENT)\n"
                     ")");
        executeQuery("CREATE INDEX IF NOT EXISTS idx_FieldType_valueTypes_fieldType ON "
                     "FieldType_valueTypes(fieldType)");
        executeQuery("CREATE INDEX IF NOT EXISTS idx_FieldType_valueTypes_valueType ON "
                     "FieldType_valueTypes(valueType)");
        executeQuery("CREATE TABLE IF NOT EXISTS `FieldType_allowedTypes` (\n"
                     "  `id`	        INTEGER NOT NULL UNIQUE,\n"
                     "  `index`	    INTEGER NOT NULL,\n"
                     "  `fieldType`   INTEGER NOT NULL,\n"
                     "  `type`        INTEGER NOT NULL,\n"
                     "  PRIMARY KEY(`id` AUTOINCREMENT)\n"
                     ")");
        executeQuery("CREATE INDEX IF NOT EXISTS idx_FieldType_allowedTypes_field ON "
                     "FieldType_allowedTypes(fieldType)");
        executeQuery("CREATE INDEX IF NOT EXISTS idx_FieldType_allowedTypes_type ON "
                     "FieldType_allowedTypes(type)");

        mReloadQuery = createQuery("SELECT * FROM `FieldType` WHERE `id`=:id");
        mInsertQuery = createQuery("INSERT INTO `FieldType` (`id`,`minOccurs`,`maxOccurs`) "
                                   "VALUES (:id,:minOccurs,:maxOccurs)");
        mUpdateQuery = createQuery(
            "UPDATE `FieldType` SET `minOccurs`=:minOccurs,`maxOccurs`=:maxOccurs WHERE "
            "`id`=:id");

        mReloadElementTypesQuery = createQuery(
            "SELECT * FROM `ElementType_fieldTypes` WHERE `fieldType`=:fieldType ORDER BY `index`");

        mReloadValueTypesQuery = createQuery(
            "SELECT * FROM `FieldType_valueTypes` WHERE `fieldType`=:fieldType ORDER BY `index`");
        mInsertValueTypesQuery = createQuery(
            "INSERT INTO `FieldType_valueTypes` (`index`,`fieldType`,`valueType`) VALUES "
            "(:index,:fieldType,:valueType)");
        mRemoveValueTypesQuery = createQuery(
            "DELETE FROM `FieldType_valueTypes` WHERE `fieldType`=:fieldType");

        mReloadAllowedTypesQuery = createQuery(
            "SELECT * FROM `FieldType_allowedTypes` WHERE `fieldType`=:fieldType ORDER BY `index`");
        mInsertAllowedTypesQuery = createQuery(
            "INSERT INTO `FieldType_allowedTypes` (`index`,`fieldType`,`type`) VALUES "
            "(:index,:fieldType,:type)");
        mRemoveAllowedTypesQuery = createQuery(
            "DELETE FROM `FieldType_allowedTypes` WHERE `fieldType`=:fieldType");
    }

    emitDatabaseChanged();
}

Node *FieldTypeStorage::createNode()
{
    mNodes.append(new FieldType{storage(), storage()});
    return mNodes.last();
}

bool FieldTypeStorage::insertNode(Node *node)
{
    Transaction tx{Transaction::WriteModified, node, storage()};

    if (!storage()->nodeTypeStorage()->insertNode(node))
        return false;

    FieldType *fieldType = static_cast<FieldType *>(node);

    if (!executeQuery(mInsertQuery,
                      QVariantMap{{":id", fieldType->rowid()},
                                  {":minOccurs", fieldType->mMinOccurs},
                                  {":maxOccurs", fieldType->mMaxOccurs}}))
        return handleError(this, "insertNode", mInsertQuery), false;

    int index = 0;
    for (ValueType *valueType : fieldType->valueTypes()) {
        if (!valueType->save(true))
            return handleError(this, "insertNode", "valuetype could not be saved"), false;

        if (!executeQuery(mInsertValueTypesQuery,
                          QVariantMap{{":index", index},
                                      {":fieldType", fieldType->rowid()},
                                      {":valueType", valueType->rowid()}}))
            return handleError(this, "insertNode", mInsertValueTypesQuery), false;

        ++index;
    }

    index = 0;
    for (int allowedType : fieldType->allowedTypes()) {
        if (!executeQuery(mInsertAllowedTypesQuery,
                          QVariantMap{{":index", index},
                                      {":fieldType", fieldType->rowid()},
                                      {":type", allowedType}}))
            return handleError(this, "insertNode", mInsertAllowedTypesQuery), false;

        ++index;
    }

    tx.commit();

    return true;
}

bool FieldTypeStorage::updateNode(Node *node)
{
    Transaction tx{Transaction::WriteModified, node, storage()};

    if (!storage()->nodeTypeStorage()->updateNode(node))
        return false;

    FieldType *fieldType = static_cast<FieldType *>(node);

    if (!executeQuery(mUpdateQuery,
                      QVariantMap{{":minOccurs", fieldType->mMinOccurs},
                                  {":maxOccurs", fieldType->mMaxOccurs},
                                  {":id", fieldType->rowid()}}))
        return handleError(this, "updateNode", mUpdateQuery), false;

    if (!executeQuery(mRemoveValueTypesQuery, QVariantMap{{":field", fieldType->rowid()}}))
        return handleError(this, "updateNode", mRemoveValueTypesQuery), false;

    int index = 0;
    for (ValueType *valueType : fieldType->valueTypes()) {
        if (!valueType->save(true))
            return handleError(this, "insertNode", "value could not be saved"), false;

        if (!executeQuery(mInsertValueTypesQuery,
                          QVariantMap{{":index", index},
                                      {":field", fieldType->rowid()},
                                      {":value", valueType->rowid()}}))
            return handleError(this, "updateNode", mInsertValueTypesQuery), false;

        ++index;
    }

    if (!executeQuery(mRemoveAllowedTypesQuery, QVariantMap{{":field", fieldType->rowid()}}))
        return handleError(this, "updateNode", mRemoveAllowedTypesQuery), false;

    index = 0;
    for (int allowedtype : std::as_const(fieldType->mAllowedTypes)) {
        if (!executeQuery(mInsertAllowedTypesQuery,
                          QVariantMap{{":index", index},
                                      {":field", fieldType->rowid()},
                                      {":type", allowedtype}}))
            return handleError(this, "updateNode", mInsertAllowedTypesQuery), false;

        ++index;
    }

    tx.commit();

    return true;
}

bool FieldTypeStorage::reloadNode(Node *node)
{
    Transaction tx{Transaction::ReadModified, node, storage()};

    if (!storage()->nodeTypeStorage()->reloadNode(node))
        return false;

    FieldType *fieldType = static_cast<FieldType *>(node);

    if (!executeQuery(mReloadQuery, {fieldType->rowid()}))
        return handleError(this, "reloadNode", mReloadQuery), false;

    if (!mReloadQuery.next())
        return handleError(this, "reloadNode", "result set is empty"), false;

    fieldType->setMinOccurs(mReloadQuery.value("minOccurs").toInt());
    fieldType->setMaxOccurs(mReloadQuery.value("maxOccurs").toInt());

    if (!executeQuery(mReloadElementTypesQuery, QVariantMap{{":fieldType", fieldType->rowid()}}))
        return handleError(this, "reloadNode", mReloadElementTypesQuery), false;

    QList<ElementType *> ets;
    while (mReloadElementTypesQuery.next()) {
        const int rowid = mReloadElementTypesQuery.value("elementType").toInt();
        if (ElementType *et = qobject_cast<ElementType *>(
                storage()->elementTypeStorage()->elementType(rowid)))
            ets.append(et);
        else
            handleError(this, "reloadNode", "could not load elementtype");
    }

    fieldType->setElementTypes(ets);

    if (!executeQuery(mReloadValueTypesQuery, QVariantMap{{":fieldType", fieldType->rowid()}}))
        return handleError(this, "reloadNode", mReloadValueTypesQuery), false;

    QList<ValueType *> valueTypes;
    while (mReloadValueTypesQuery.next()) {
        const int rowid = mReloadValueTypesQuery.value("valueType").toInt();
        if (ValueType *vt = qobject_cast<ValueType *>(
                storage()->valueTypeStorage()->valueType(rowid)))
            valueTypes.append(vt);
        else
            handleError(this, "reloadNode", "could not load valuetype");
    }

    fieldType->setValueTypes(valueTypes);

    if (!executeQuery(mReloadAllowedTypesQuery, QVariantMap{{":fieldType", fieldType->rowid()}}))
        return handleError(this, "reloadNode", mReloadAllowedTypesQuery), false;

    QList<int> allowedTypes;
    while (mReloadAllowedTypesQuery.next()) {
        if (int allowedType = mReloadAllowedTypesQuery.value("type").toInt(); allowedType > 0)
            allowedTypes.append(allowedType);
        else
            handleError(this,
                        "reloadNode",
                        QStringLiteral("invalid allowedtype: '%1'").arg(allowedType));
    }

    fieldType->setAllowedTypes(allowedTypes);

    tx.commit();

    return true;
}

bool FieldTypeStorage::removeNode(int rowid)
{
    if (rowid <= 0)
        return handleError(this, "removeNode", "rowid is invalid"), false;

    Transaction tx{Transaction::WriteModified, mNodesByRowid.value(rowid), storage()};

    if (!storage()->nodeTypeStorage()->removeNode(rowid))
        return false;

    if (!executeQuery(mRemoveValueTypesQuery, QVariantMap{{":fieldType", rowid}}))
        return handleError(this, "removeNode", mRemoveValueTypesQuery), false;

    if (!executeQuery(mRemoveAllowedTypesQuery, QVariantMap{{":fieldType", rowid}}))
        return handleError(this, "removeNode", mRemoveAllowedTypesQuery), false;

    tx.commit();

    return true;
}

bool FieldTypeStorage::updateValueTypes(FieldType *fieldType)
{
    if (fieldType->rowid() <= 0)
        return false;

    Transaction tx{Transaction::Write, fieldType, storage()};

    if (!executeQuery(mRemoveValueTypesQuery, QVariantMap{{":fieldType", fieldType->rowid()}}))
        return handleError(this, "updateValueTypes", mRemoveValueTypesQuery), false;

    int index = 0;
    for (ValueType *valueType : std::as_const(fieldType->mValueTypes)) {
        if (!valueType->save(true))
            return handleError(this, "updateValueTypes", "value could not be saved"), false;

        if (!executeQuery(mInsertValueTypesQuery,
                          QVariantMap{{":index", index},
                                      {":fieldType", fieldType->rowid()},
                                      {":value", valueType->rowid()}}))
            return handleError(this, "updateValueTypes", mInsertValueTypesQuery), false;

        ++index;
    }

    tx.commit();

    return true;
}

bool FieldTypeStorage::updateAllowedTypes(FieldType *fieldType)
{
    if (fieldType->rowid() <= 0)
        return false;

    Transaction tx{Transaction::Write, fieldType, storage()};

    if (!executeQuery(mRemoveAllowedTypesQuery, QVariantMap{{":fieldType", fieldType->rowid()}}))
        return handleError(this, "updateNode", mRemoveAllowedTypesQuery), false;

    int index = 0;
    for (int allowedType : std::as_const(fieldType->mAllowedTypes)) {
        if (!executeQuery(mInsertAllowedTypesQuery,
                          QVariantMap{{":index", index},
                                      {":fieldType", fieldType->rowid()},
                                      {":type", allowedType}}))
            return handleError(this, "insertNode", mInsertAllowedTypesQuery), false;

        ++index;
    }

    tx.commit();

    return true;
}

bool FieldTypeStorage::updateMinOccurs(FieldType *fieldType)
{
    if (fieldType->rowid() <= 0)
        return false;

    Transaction tx{Transaction::Write, fieldType, storage()};

    QSqlQuery q = createQuery("UPDATE FieldType SET minOccurs=? WHERE id=?");
    if (!executeQuery(q, {fieldType->mMinOccurs, fieldType->rowid()}))
        return handleError(this, "updateMinOccurs", q), false;

    tx.commit();

    return true;
}

bool FieldTypeStorage::updateMaxOccurs(FieldType *fieldType)
{
    if (fieldType->rowid() <= 0)
        return false;

    Transaction tx{Transaction::Write, fieldType, storage()};

    QSqlQuery q = createQuery("UPDATE FieldType SET maxOccurs=? WHERE id=?");
    if (!executeQuery(q, {fieldType->mMaxOccurs, fieldType->rowid()}))
        return handleError(this, "updateMaxOccurs", q), false;

    tx.commit();

    return true;
}
