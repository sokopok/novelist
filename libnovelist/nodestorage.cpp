#include "nodestorage.h"
#include "storage.h"

NodeStorage::NodeStorage(Storage *parent)
    : BaseStorage{parent}
{}

void NodeStorage::setDatabase(const QSqlDatabase &database)
{
    mDatabase = database;

    if (mDatabase.isOpen()) {
        executeQuery("CREATE TABLE IF NOT EXISTS `Storable` (\n"
                     "  `id`	    INTEGER NOT NULL UNIQUE,\n"
                     "  `type`	    INTEGER NOT NULL,\n"
                     "  `typeName`  TEXT NOT NULL,\n"
                     "  `version`	INTEGER NOT NULL,\n"
                     "  `createdAt` INTEGER,\n"
                     "  `updatedAt` INTEGER,\n"
                     "  `createdBy` TEXT,\n"
                     "  `updatedBy` TEXT,\n"
                     "  PRIMARY KEY(`id` AUTOINCREMENT)\n"
                     ")");

        executeQuery("CREATE TABLE IF NOT EXISTS `Node` (\n"
                     "  `id`	     INTEGER NOT NULL UNIQUE,\n"
                     "  `nodeType` INTEGER NOT NULL,\n"
                     "  `name`     TEXT,\n"
                     "  `label`    TEXT,\n"
                     "  `info`     TEXT,\n"
                     "  `icon`     TEXT,\n"
                     "  PRIMARY KEY(`id`),\n"
                     "  FOREIGN KEY(`id`) REFERENCES Storable(`id`) ON DELETE CASCADE,\n"
                     "  FOREIGN KEY(`nodeType`) REFERENCES Storable(`id`) ON DELETE NO ACTION\n"
                     ")");

        mReloadQuery = createQuery(
            "SELECT "
            "s.`id` AS `id`,s.`type` AS `type`,s.`version` AS `version`,s.`createdAt` AS "
            "`createdAt`,s.`createdBy` AS `createdBy`,s.`updatedAt` AS "
            "`updatedAt`,s.`updatedBy` "
            "AS `updatedBy`,n.`nodeType` AS `nodeType`,n.`name` AS `name`,n.`label` AS "
            "`label`,n.`info` AS `info`,n.`icon` AS `icon` FROM `Storable` s JOIN `Node` n ON "
            "s.`id`=n.`id` WHERE s.`id`=:id");

        mInsertStorableQuery = createQuery(
            "INSERT INTO `Storable` (`type`,`typeName`,`version`,`createdAt`,`createdBy`) VALUES "
            "(:type,:typeName,:version,:createdAt,:createdBy)");
        mInsertNodeQuery = createQuery(
            "INSERT INTO `Node` (`id`,`nodeType`,`name`,`label`,`info`,`icon`) VALUES "
            "(:id,:nodeType,:name,:label,:info,:icon)");

        mUpdateStorableQuery = createQuery(
            "UPDATE `Storable` SET "
            "`type`=:type,`typeName`=:typeName,`version`=:version,`createdAt`=:createdAt,`"
            "createdBy`=:createdBy,`updatedAt`=:updatedAt,`"
            "updatedBy`=:updatedBy WHERE `id`=:id");
        mUpdateNodeQuery = createQuery("UPDATE `Node` SET "
                                       "`nodeType=:nodeType`,`name`=:name,`label`=:label,`info`=:"
                                       "info,`icon`=:icon WHERE `id`=:id");

        mRemoveStorableQuery = createQuery("DELETE FROM `Storable` WHERE `id`=:id");
        mRemoveNodeQuery = createQuery("DELETE FROM `Node` WHERE `id`=:id");
    }

    emitDatabaseChanged();
}

Node *NodeStorage::createNode()
{
    mNodes.append(new Node{storage(), storage()});
    return mNodes.last();
}

bool NodeStorage::insertNode(Node *node)
{
    if (!node) {
        handleError(this, "insertNode", "node is null");
        return false;
    }

    Transaction tx{Transaction::WriteModified, node, storage()};

    const QDateTime createdAt = QDateTime::currentDateTime();
    const QString createdBy = "tomas";
    const int version = node->version() + 1;

    if (!executeQuery(mInsertStorableQuery,
                      QVariantMap{{":type", node->type()},
                                  {":typeName", node->typeName()},
                                  {":version", version},
                                  {":createdAt", createdAt.toMSecsSinceEpoch()},
                                  {":createdBy", createdBy}})) {
        handleError(this,
                    "insertNode",
                    {mInsertStorableQuery.lastError().text(), mInsertStorableQuery.lastQuery()});
        return false;
    }

    if (!mInsertStorableQuery.lastInsertId().isValid()) {
        handleError(this,
                    "insertNode",
                    {"lastInsertId is invalid", mInsertStorableQuery.lastQuery()});
        return false;
    }

    const int rowid = mInsertStorableQuery.lastInsertId().toInt();

    if (!executeQuery(mInsertNodeQuery,
                      QVariantMap{{":id", rowid},
                                  {":nodeType", node->nodeType() ? node->nodeType()->rowid() : 0},
                                  {":name", node->name()},
                                  {":label", node->label()},
                                  {":info", node->info()},
                                  {":icon", node->icon()}})) {
        handleError(this,
                    "insertNode",
                    {mInsertNodeQuery.lastError().text(), mInsertNodeQuery.lastQuery()});
        return false;
    }

    node->setRowid(rowid);
    node->setCreatedAt(createdAt);
    node->setCreatedBy(createdBy);
    node->setVersion(version);

    tx.commit();

    return true;
}

bool NodeStorage::updateNode(Node *node)
{
    if (!node) {
        handleError(this, "updateNode", "node is null");
        return false;
    }

    Transaction tx{Transaction::WriteModified, node, storage()};

    const QDateTime updatedAt = QDateTime::currentDateTime();
    const int version = node->version();

    if (!executeQuery(mUpdateStorableQuery,
                      QVariantMap{{":type", node->type()},
                                  {":typeName", node->typeName()},
                                  {":version", version},
                                  {":createdAt", node->createdAt().toMSecsSinceEpoch()},
                                  {":updatedAt", updatedAt.toMSecsSinceEpoch()},
                                  {":createdBy", node->createdBy()},
                                  {":updatedBy", node->updatedBy()},
                                  {":id", node->rowid()}})) {
        handleError(this,
                    "updateNode",
                    {mUpdateStorableQuery.lastError().text(), mUpdateStorableQuery.lastQuery()});
        return false;
    }

    if (!executeQuery(mUpdateNodeQuery,
                      QVariantMap{{":nodeType", node->nodeType() ? node->nodeType()->rowid() : 0},
                                  {":name", node->name()},
                                  {":label", node->label()},
                                  {":info", node->info()},
                                  {":icon", node->icon()},
                                  {":id", node->rowid()}})) {
        handleError(this,
                    "updateNode",
                    {mUpdateNodeQuery.lastError().text(), mUpdateNodeQuery.lastQuery()});
        return false;
    }

    node->setUpdatedAt(updatedAt);
    node->setVersion(version);

    tx.commit();

    return true;
}

bool NodeStorage::reloadNode(Node *node)
{
    if (!node)
        return handleError(this, "reloadNode", "node is null"), false;

    if (node->rowid() <= 0)
        return handleError(this, "reloadNode", "rowid is invalid"), false;

    Transaction tx{Transaction ::ReadModified, node, storage()};

    if (!executeQuery(mReloadQuery, QVariantMap{{":id", node->rowid()}}))
        return handleError(this, "reloadNode", mReloadQuery), false;

    if (!mReloadQuery.next())
        return handleError(this, "reloadNode", "result set is empty"), false;

    node->setRowid(mReloadQuery.value("id").toInt());
    node->setType(mReloadQuery.value("type").toInt());
    node->setVersion(mReloadQuery.value("version").toInt());
    node->setCreatedAt(
        QDateTime::fromMSecsSinceEpoch(mReloadQuery.value("createdAt").value<qint64>()));
    node->setUpdatedAt(
        QDateTime::fromMSecsSinceEpoch(mReloadQuery.value("updatedAt").value<qint64>()));
    node->setCreatedBy(mReloadQuery.value("createdBy").toString());
    node->setUpdatedBy(mReloadQuery.value("updatedBy").toString());

    // node->setNodeType(qobject_cast<NodeType*>(storage().nodeType(node->type(), "")));
    node->setName(mReloadQuery.value("name").toString());
    node->setLabel(mReloadQuery.value("label").toString());
    node->setInfo(mReloadQuery.value("info").toString());
    node->setIcon(mReloadQuery.value("icon").toString());

    mNodesByRowid.insert(node->rowid(), node);

    tx.commit();

    return true;
}

bool NodeStorage::removeNode(int rowid)
{
    if (rowid <= 0) {
        handleError(this, "removeNode", "rowid is invalid");
        return false;
    }

    Transaction tx{Transaction::WriteModified, mNodesByRowid.value(rowid), storage()};

    if (!executeQuery(mRemoveStorableQuery, QVariantMap{{":id", rowid}})) {
        handleError(this,
                    "removeNode",
                    {mRemoveStorableQuery.lastError().text(), mRemoveStorableQuery.lastQuery()});
        return false;
    }

    if (!executeQuery(mRemoveNodeQuery, QVariantMap{{":id", rowid}})) {
        handleError(this,
                    "removeNode",
                    {mRemoveNodeQuery.lastError().text(), mRemoveNodeQuery.lastQuery()});
        return false;
    }

    tx.commit();

    return true;
}

bool NodeStorage::updateName(Node *node)
{
    if (node->rowid() <= 0)
        return false;

    QSqlQuery q = createQuery("UPDATE Node SET name=? WHERE id=?");
    if (!executeQuery(q, {node->mName, node->rowid()})) {
        handleError(this, "updateValue", q);
        return false;
    }

    return true;
}

bool NodeStorage::updateLabel(Node *node)
{
    if (node->rowid() <= 0)
        return false;

    QSqlQuery q = createQuery("UPDATE Node SET label=? WHERE id=?");
    if (!executeQuery(q, {node->mLabel, node->rowid()})) {
        handleError(this, "updateValue", q);
        return false;
    }

    return true;
}

bool NodeStorage::updateInfo(Node *node)
{
    if (node->rowid() <= 0)
        return false;

    QSqlQuery q = createQuery("UPDATE Node SET info=? WHERE id=?");
    if (!executeQuery(q, {node->mInfo, node->rowid()})) {
        handleError(this, "updateValue", q);
        return false;
    }

    return true;
}

bool NodeStorage::updateIcon(Node *node)
{
    if (node->rowid() <= 0)
        return false;

    QSqlQuery q = createQuery("UPDATE Node SET icon=? WHERE id=?");
    if (!executeQuery(q, {node->mIcon, node->rowid()})) {
        handleError(this, "updateValue", q);
        return false;
    }

    return true;
}

bool NodeStorage::updateNodeType(Node *node)
{
    if (node->rowid() <= 0)
        return false;

    QSqlQuery q = createQuery("UPDATE Node SET nodetype=? WHERE id=?");
    if (!executeQuery(q, {node->mNodeType ? node->mNodeType->rowid() : 0, node->rowid()})) {
        handleError(this, "updateValue", q);
        return false;
    }

    return true;
}
