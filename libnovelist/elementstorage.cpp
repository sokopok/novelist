#include "elementstorage.h"
#include "storage.h"

void ElementStorage::setDatabase(const QSqlDatabase &database)
{
    mDatabase = database;

    if (mDatabase.isOpen()) {
        executeQuery("CREATE TABLE IF NOT EXISTS `Element` (\n"
                     "  `id`	   INTEGER NOT NULL UNIQUE,\n"
                     "  PRIMARY KEY(`id`),\n"
                     "  FOREIGN KEY(`id`) REFERENCES Storable(`id`) ON DELETE CASCADE\n"
                     ")");
        executeQuery("CREATE TABLE IF NOT EXISTS `Element_fields` (\n"
                     "  `id`	        INTEGER NOT NULL UNIQUE,\n"
                     "  `index`	    INTEGER NOT NULL,\n"
                     "  `element`     INTEGER NOT NULL,\n"
                     "  `field`       INTEGER NOT NULL,\n"
                     "  PRIMARY KEY(`id` AUTOINCREMENT)\n"
                     ")");
        executeQuery(
            "CREATE INDEX IF NOT EXISTS idx_Element_fields_element ON Element_fields(element)");
        executeQuery(
            "CREATE INDEX IF NOT EXISTS idx_Element_fields_field ON Element_fields(field)");

        mReloadQuery = createQuery("SELECT * FROM `Element` WHERE `id`=:id");
        mInsertQuery = createQuery("INSERT INTO `Element` (`id`) VALUES (:id)");
        mUpdateQuery = createQuery("UPDATE `Element` SET `id`=:id WHERE `id`=:id");

        mReloadFieldsQuery = createQuery(
            "SELECT * FROM `Element_fields` WHERE `element`=:element ORDER BY `index`");
        mInsertFieldsQuery = createQuery(
            "INSERT INTO `Element_fields` (`index`,`element`,`field`) VALUES "
            "(:index,:element,:field)");
        mRemoveFieldsQuery = createQuery("DELETE FROM `Element_fields` WHERE `element`=:element");
    }

    emitDatabaseChanged();
}

Node *ElementStorage::createNode()
{
    mNodes.append(new Element{storage(), storage()});
    return mNodes.last();
}

bool ElementStorage::insertNode(Node *node)
{
    Transaction tx{Transaction::WriteModified, node, storage()};

    if (!storage()->nodeStorage()->insertNode(node))
        return false;

    Element *e = static_cast<Element *>(node);

    if (!executeQuery(mInsertQuery, QVariantMap{{":id", e->rowid()}}))
        return handleError(this, "insertNode", mInsertQuery), false;

    updateFields(e);

    tx.commit();

    return true;
}

bool ElementStorage::updateNode(Node *node)
{
    Transaction tx{Transaction::WriteModified, node, storage()};

    if (!storage()->nodeStorage()->updateNode(node))
        return false;

    Element *e = static_cast<Element *>(node);

    // if (!executeQuery(mUpdateQuery, QVariantMap{{":id", e->rowid()}})) {
    //     handleError("");
    //     return false;
    // }

    updateFields(e);

    tx.commit();

    return true;
}

bool ElementStorage::reloadNode(Node *node)
{
    Transaction tx{Transaction::ReadModified, node, storage()};

    if (!storage()->nodeStorage()->reloadNode(node))
        return false;

    Element *e = static_cast<Element *>(node);

    if (!executeQuery(mReloadQuery, {e->rowid()}))
        return handleError(this, "reloadNode", mReloadQuery), false;

    if (!mReloadQuery.next())
        return handleError(this, "reloadNode", "result set is empty"), false;

    if (!executeQuery(mReloadFieldsQuery, QVariantMap{{":element", e->rowid()}}))
        return handleError(this, "reloadNode", mReloadFieldsQuery), false;

    QList<Field *> fs;
    while (mReloadFieldsQuery.next())
        if (Field *f = qobject_cast<Field *>(
                storage()->fieldStorage()->field(mReloadFieldsQuery.value("field").toInt())))
            fs.append(f);
        else
            handleError(this, "updateNode", "could not load field");

    e->setFields(fs);

    tx.commit();

    return true;
}

bool ElementStorage::removeNode(int rowid)
{
    if (rowid <= 0) {
        handleError(this, "removeNode", "rowid is invalid");
        return false;
    }

    Transaction tx{Transaction::WriteModified, mNodesByRowid.value(rowid), storage()};

    if (!storage()->nodeStorage()->removeNode(rowid))
        return false;

    if (!executeQuery(mRemoveFieldsQuery, QVariantMap{{":element", rowid}})) {
        handleError(this, "removeNode", mRemoveFieldsQuery);
        return false;
    }

    tx.commit();

    return true;
}

bool ElementStorage::updateFields(Element *element)
{
    if (element->rowid() <= 0)
        return false;

    Transaction tx{Transaction::Write, element, storage()};

    if (!executeQuery(mRemoveFieldsQuery, QVariantMap{{":element", element->rowid()}}))
        return handleError(this, "updateNode", mRemoveFieldsQuery), false;

    int index = 0;
    for (Field *field : element->fields()) {
        if (!field->save(true)) {
            handleError(this, "updateNode", "field could not be saved");
            return false;
        }

        if (!executeQuery(mInsertFieldsQuery,
                          QVariantMap{{":index", index},
                                      {":element", element->rowid()},
                                      {":field", field->rowid()}}))
            return handleError(this, "updateNode", mInsertFieldsQuery), false;

        ++index;
    }

    tx.commit();

    return true;
}
