#include "elementtypestorage.h"
#include "fieldtype.h"
#include "storage.h"

void ElementTypeStorage::setDatabase(const QSqlDatabase &database)
{
    mDatabase = database;

    if (mDatabase.isOpen()) {
        executeQuery("CREATE TABLE IF NOT EXISTS `ElementType` (\n"
                     "  `id`          INTEGER NOT NULL UNIQUE,\n"
                     "  PRIMARY KEY(`id`),\n"
                     "  FOREIGN KEY(`id`) REFERENCES Storable(`id`) ON DELETE CASCADE\n"
                     ")");
        executeQuery("CREATE TABLE IF NOT EXISTS `ElementType_fieldTypes` (\n"
                     "  `id`	        INTEGER NOT NULL UNIQUE,\n"
                     "  `index`	    INTEGER NOT NULL,\n"
                     "  `elementType` INTEGER NOT NULL,\n"
                     "  `fieldType`   INTEGER NOT NULL,\n"
                     "  PRIMARY KEY(`id` AUTOINCREMENT)\n"
                     ")");
        executeQuery("CREATE INDEX IF NOT EXISTS idx_ElementType_fieldTypes_elementType ON "
                     "ElementType_fieldTypes(elementType)");
        executeQuery("CREATE INDEX IF NOT EXISTS idx_ElementType_fieldTypes_fieldType ON "
                     "ElementType_fieldTypes(fieldType)");

        mReloadQuery = createQuery("SELECT * FROM `ElementType` WHERE `id`=:id");
        mInsertQuery = createQuery("INSERT INTO `ElementType` (`id`) VALUES (:id)");
        mUpdateQuery = createQuery("UPDATE `ElementType` SET `id`=:id WHERE `id`=:id");

        mReloadFieldTypesQuery = createQuery("SELECT * FROM `ElementType_fieldTypes` WHERE "
                                             "`elementType`=:elementType ORDER BY `index`");
        mInsertFieldTypesQuery = createQuery(
            "INSERT INTO `ElementType_fieldTypes` (`index`,`elementType`,`fieldType`) VALUES "
            "(:index,:elementType,:fieldType)");
        mUpdateFieldTypesQuery = createQuery(
            "UPDATE `ElementType_fieldTypes` SET "
            "`index`=:index,`elementType`=:elementType,`fieldType`=:fieldType WHERE `id`=:id");
        mRemoveFieldTypesQuery = createQuery(
            "DELETE FROM `ElementType_fieldTypes` WHERE `elementType`=:elementType");
    }
}

Node *ElementTypeStorage::createNode()
{
    mNodes.append(new ElementType{storage(), storage()});
    return mNodes.last();
}

bool ElementTypeStorage::insertNode(Node *node)
{
    Transaction tx{Transaction::WriteModified, node, storage()};

    if (!storage()->nodeTypeStorage()->insertNode(node))
        return false;

    ElementType *elementType = static_cast<ElementType *>(node);

    for (FieldType *f : elementType->fieldTypes())
        if (!f->save(true))
            return handleError(this, "insertNode", "field could not be saved"), false;

    if (!executeQuery(mInsertQuery, QVariantMap{{":id", elementType->rowid()}}))
        return handleError(this, "insertNode", mInsertQuery), false;

    updateFieldTypes(elementType);

    tx.commit();

    return true;
}

bool ElementTypeStorage::updateNode(Node *node)
{
    Transaction tx{Transaction::WriteModified, node, storage()};

    if (!storage()->nodeTypeStorage()->updateNode(node))
        return false;

    ElementType *elementType = static_cast<ElementType *>(node);

    // if (!executeQuery(mUpdateQuery, QVariantMap{{":id", e->rowid()}})) {
    //     handleError("");
    //     return false;
    // }

    updateFieldTypes(elementType);

    tx.commit();

    return true;
}

bool ElementTypeStorage::reloadNode(Node *node)
{
    Transaction tx{Transaction::ReadModified, node, storage()};

    if (!storage()->nodeTypeStorage()->reloadNode(node))
        return false;

    ElementType *elementType = static_cast<ElementType *>(node);

    if (!executeQuery(mReloadQuery, {elementType->rowid()}))
        return handleError(this, "reloadNode", mReloadQuery), false;

    if (!mReloadQuery.next())
        return handleError(this, "reloadNode", "result set is empty"), false;

    if (!executeQuery(mReloadFieldTypesQuery, QVariantMap{{":elementType", elementType->rowid()}}))
        return handleError(this, "reloadNode", mReloadFieldTypesQuery), false;

    QList<FieldType *> fieldTypes;
    while (mReloadFieldTypesQuery.next()) {
        const int rowid = mReloadFieldTypesQuery.value("fieldType").toInt();
        if (FieldType *fieldType = qobject_cast<FieldType *>(
                storage()->fieldTypeStorage()->fieldType(rowid)))
            fieldTypes.append(fieldType);
        else
            handleError(this, "reloadNode", "could not load fieldType");
    }
    elementType->setFieldTypes(fieldTypes);

    tx.commit();

    return true;
}

bool ElementTypeStorage::removeNode(int rowid)
{
    if (rowid <= 0) {
        handleError(this, "removeNode", "rowid is invalid");
        return false;
    }

    Transaction tx{Transaction::WriteModified, mNodesByRowid.value(rowid), storage()};

    if (!storage()->nodeTypeStorage()->removeNode(rowid))
        return false;

    if (!executeQuery(mRemoveFieldTypesQuery, QVariantMap{{":elementType", rowid}}))
        return handleError(this, "removeNode", mRemoveFieldTypesQuery), false;

    tx.commit();

    return true;
}

bool ElementTypeStorage::updateFieldTypes(ElementType *elementType)
{
    if (elementType->rowid() <= 0)
        return false;

    Transaction tx{Transaction::Write, elementType, storage()};

    if (!executeQuery(mRemoveFieldTypesQuery, QVariantMap{{":elementType", elementType->rowid()}})) {
        handleError(this, "updateNode", mRemoveFieldTypesQuery);
        return false;
    }

    int index = 0;
    for (FieldType *fieldType : elementType->fieldTypes()) {
        if (!fieldType->save(true)) {
            handleError(this, "updateNode", "fieldType could not be saved");
            return false;
        }

        if (!executeQuery(mInsertFieldTypesQuery,
                          QVariantMap{{":index", index},
                                      {":elementType", elementType->rowid()},
                                      {":fieldType", fieldType->rowid()}})) {
            handleError(this, "updateNode", mInsertFieldTypesQuery);
            return false;
        }
        ++index;
    }

    tx.commit();

    return true;
}
