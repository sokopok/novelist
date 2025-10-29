#include "fieldstorage.h"
#include "storage.h"
#include "value.h"

void FieldStorage::setDatabase(const QSqlDatabase &database)
{
    mDatabase = database;

    if (mDatabase.isOpen()) {
        executeQuery("CREATE TABLE IF NOT EXISTS `Field` (\n"
                     "  `id`	      INTEGER NOT NULL UNIQUE,\n"
                     "  `minOccurs` INTEGER NOT NULL,\n"
                     "  `maxOccurs` INTEGER NOT NULL,\n"
                     "  PRIMARY KEY(`id`),\n"
                     "  FOREIGN KEY(`id`) REFERENCES Storable(`id`) ON DELETE CASCADE\n"
                     ")");
        executeQuery("CREATE TABLE IF NOT EXISTS `Field_values` (\n"
                     "  `id`	        INTEGER NOT NULL UNIQUE,\n"
                     "  `index`	    INTEGER NOT NULL,\n"
                     "  `field`       INTEGER NOT NULL,\n"
                     "  `value`       INTEGER NOT NULL,\n"
                     "  PRIMARY KEY(`id` AUTOINCREMENT)\n"
                     ")");
        executeQuery("CREATE INDEX IF NOT EXISTS idx_Field_values_field ON Field_values(field)");
        executeQuery("CREATE INDEX IF NOT EXISTS idx_Field_values_value ON Field_values(value)");
        executeQuery("CREATE TABLE IF NOT EXISTS `Field_allowedTypes` (\n"
                     "  `id`	        INTEGER NOT NULL UNIQUE,\n"
                     "  `index`	    INTEGER NOT NULL,\n"
                     "  `field`       INTEGER NOT NULL,\n"
                     "  `type`        INTEGER NOT NULL,\n"
                     "  PRIMARY KEY(`id` AUTOINCREMENT)\n"
                     ")");
        executeQuery(
            "CREATE INDEX IF NOT EXISTS idx_Field_allowedTypes_field ON Field_allowedTypes(field)");
        executeQuery(
            "CREATE INDEX IF NOT EXISTS idx_Field_allowedTypes_type ON Field_allowedTypes(type)");

        mReloadQuery = createQuery("SELECT * FROM `Field` WHERE `id`=:id");
        mInsertQuery = createQuery("INSERT INTO `Field` (`id`,`minOccurs`,`maxOccurs`) VALUES "
                                   "(:id,:minOccurs,:maxOccurs)");
        mUpdateQuery = createQuery(
            "UPDATE `Field` SET `minOccurs`=:minOccurs,`maxOccurs`=:maxOccurs WHERE `id`=:id");

        mReloadElementsQuery = createQuery(
            "SELECT * FROM `Element_fields` WHERE `field`=:field ORDER BY `index`");

        mReloadValuesQuery = createQuery(
            "SELECT * FROM `Field_values` WHERE `field`=:field ORDER BY `index`");
        mInsertValuesQuery = createQuery(
            "INSERT INTO `Field_values` (`index`,`field`,`value`) VALUES "
            "(:index,:field,:value)");
        mRemoveValuesQuery = createQuery("DELETE FROM `Field_values` WHERE `field`=:field");

        mReloadAllowedTypesQuery = createQuery(
            "SELECT * FROM `Field_allowedTypes` WHERE `field`=:field ORDER BY `index`");
        mInsertAllowedTypesQuery = createQuery(
            "INSERT INTO `Field_allowedTypes` (`index`,`field`,`type`) VALUES "
            "(:index,:field,:type)");
        mRemoveAllowedTypesQuery = createQuery(
            "DELETE FROM `Field_allowedTypes` WHERE `field`=:field");
    }

    emitDatabaseChanged();
}

Node *FieldStorage::createNode()
{
    mNodes.append(new Field{storage(), storage()});
    return mNodes.last();
}

bool FieldStorage::insertNode(Node *node)
{
    Transaction tx{Transaction::WriteModified, node, storage()};

    if (!storage()->nodeStorage()->insertNode(node))
        return false;

    Field *field = static_cast<Field *>(node);

    for (Value *v : field->values())
        if (!v->save(true))
            return handleError(this, "insertNode", "value could not be saved"), false;

    if (!executeQuery(mInsertQuery,
                      QVariantMap{{":id", field->rowid()},
                                  {":minOccurs", field->mMinOccurs},
                                  {":maxOccurs", field->mMaxOccurs}}))
        return handleError(this, "insertNode", mInsertQuery), false;

    updateValues(field);
    updateAllowedTypes(field);

    tx.commit();

    return true;
}

bool FieldStorage::updateNode(Node *node)
{
    Transaction tx{Transaction::WriteModified, node, storage()};

    if (!storage()->nodeStorage()->insertNode(node))
        return false;

    Field *field = static_cast<Field *>(node);

    if (!executeQuery(mUpdateQuery,
                      QVariantMap{{":minOccurs", field->mMinOccurs},
                                  {":maxOccurs", field->mMaxOccurs},
                                  {":id", field->rowid()}}))
        return handleError(this, "updateNode", mUpdateQuery), false;

    updateValues(field);
    updateAllowedTypes(field);

    tx.commit();

    return true;
}

bool FieldStorage::reloadNode(Node *node)
{
    Transaction tx{Transaction::ReadModified, node, storage()};

    if (!storage()->nodeStorage()->reloadNode(node))
        return false;

    Field *field = static_cast<Field *>(node);

    if (!executeQuery(mReloadQuery, {field->rowid()}))
        return handleError(this, "reloadNode", mReloadQuery), false;

    if (!mReloadQuery.next())
        return handleError(this, "reloadNode", "empty result set"), false;

    field->setMinOccurs(mReloadQuery.value("minOccurs").toInt());
    field->setMaxOccurs(mReloadQuery.value("maxOccurs").toInt());

    if (!executeQuery(mReloadElementsQuery, QVariantMap{{":field", field->rowid()}}))
        return handleError(this, "reloadNode", mReloadElementsQuery), false;

    QList<Element *> elements;
    while (mReloadElementsQuery.next()) {
        const int rowid = mReloadElementsQuery.value("element").toInt();
        if (Element *element = qobject_cast<Element *>(storage()->elementStorage()->element(rowid)))
            elements.append(element);
        else
            handleError(QStringLiteral("element with rowid '%1' could not be loaded").arg(rowid));
    }

    field->setElements(elements);

    if (!executeQuery(mReloadValuesQuery, QVariantMap{{":field", field->rowid()}})) {
        handleError(this, "reloadNode", mReloadValuesQuery);
        return false;
    }

    QList<Value *> vs;
    while (mReloadValuesQuery.next())
        if (Value *v = qobject_cast<Value *>(
                storage()->valueStorage()->value(mReloadValuesQuery.value("value").toInt())))
            vs.append(v);
        else
            handleError("!!!");

    field->setValues(vs);

    if (!executeQuery(mReloadAllowedTypesQuery, QVariantMap{{":field", field->rowid()}})) {
        handleError(this, "reloadNode", mReloadAllowedTypesQuery);
        return false;
    }

    QList<int> ts;
    while (mReloadAllowedTypesQuery.next()) {
        if (int t = mReloadAllowedTypesQuery.value("type").toInt(); t > 0)
            ts.append(t);
        else
            handleError(QStringLiteral("allowedtype '%1' is invalid").arg(t));
    }

    field->setAllowedTypes(ts);

    tx.commit();

    return true;
}

bool FieldStorage::removeNode(int rowid)
{
    if (rowid <= 0) {
        handleError(this, "removeNode", "rowid is invalid");
        return false;
    }

    Transaction tx{Transaction::WriteModified, mNodesByRowid.value(rowid), storage()};

    if (!storage()->nodeStorage()->removeNode(rowid))
        return false;

    if (!executeQuery(mRemoveValuesQuery, QVariantMap{{":field", rowid}})) {
        handleError(this, "removeNode", mRemoveValuesQuery);
        return false;
    }

    if (!executeQuery(mRemoveAllowedTypesQuery, QVariantMap{{":field", rowid}})) {
        handleError(this, "removeNode", mRemoveAllowedTypesQuery);
        return false;
    }

    tx.commit();

    return true;
}

bool FieldStorage::updateValues(Field *field)
{
    if (field->rowid() <= 0)
        return false;

    Transaction tx{Transaction::Write, field, storage()};

    if (!executeQuery(mRemoveValuesQuery, QVariantMap{{":field", field->rowid()}})) {
        handleError(this, "updateValues", mRemoveValuesQuery);
        return false;
    }

    int index = 0;
    for (Value *value : std::as_const(field->mValues)) {
        if (!value->save(true)) {
            handleError(this, "updateValues", "value could not be saved");
            return false;
        }
        if (!executeQuery(mInsertValuesQuery,
                          QVariantMap{{":index", index},
                                      {":field", field->rowid()},
                                      {":value", value->rowid()}})) {
            handleError(this, "updateValues", mInsertValuesQuery);
            return false;
        }
        ++index;
    }

    tx.commit();

    return true;
}

bool FieldStorage::updateAllowedTypes(Field *field)
{
    if (field->rowid() <= 0)
        return false;

    Transaction tx{Transaction::Write, field, storage()};

    if (!executeQuery(mRemoveAllowedTypesQuery, QVariantMap{{":field", field->rowid()}})) {
        handleError(this, "updateAllowedTypes", mRemoveAllowedTypesQuery);
        return false;
    }

    int index = 0;
    for (int t : std::as_const(field->mAllowedTypes)) {
        if (!executeQuery(mInsertAllowedTypesQuery,
                          QVariantMap{{":index", index}, {":field", field->rowid()}, {":type", t}})) {
            handleError(this, "updateAllowedTypes", mInsertAllowedTypesQuery);
            return false;
        }
        ++index;
    }

    tx.commit();

    return true;
}

bool FieldStorage::updateMinOccurs(Field *field)
{
    if (field->rowid() <= 0)
        return false;

    Transaction tx{Transaction::Write, field, storage()};

    QSqlQuery q = createQuery("UPDATE Field SET minOccurs=? WHERE id=?");
    if (!executeQuery(q, {field->mMinOccurs, field->rowid()})) {
        handleError(this, "updateMinOccurs", q);
        return false;
    }

    tx.commit();

    return true;
}

bool FieldStorage::updateMaxOccurs(Field *field)
{
    if (field->rowid() <= 0)
        return false;

    Transaction tx{Transaction::Write, field, storage()};

    QSqlQuery q = createQuery("UPDATE Field SET maxOccurs=? WHERE id=?");
    if (!executeQuery(q, {field->mMaxOccurs, field->rowid()})) {
        handleError(this, "updateMaxOccurs", q);
        return false;
    }

    tx.commit();

    return true;
}
