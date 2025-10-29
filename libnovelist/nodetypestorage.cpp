#include "nodetypestorage.h"
#include "storage.h"

void NodeTypeStorage::setDatabase(const QSqlDatabase &database)
{
    mDatabase = database;

    if (mDatabase.isOpen()) {
        executeQuery("CREATE TABLE IF NOT EXISTS `NodeType` (\n"
                     "  `id`	   INTEGER NOT NULL UNIQUE,\n"
                     "  PRIMARY KEY(`id`),\n"
                     "  FOREIGN KEY(`id`) REFERENCES Storable(`id`) ON DELETE CASCADE\n"
                     ")");

        mReloadQuery = createQuery("SELECT * FROM `NodeType` WHERE `id`=:id");
        mInsertQuery = createQuery("INSERT INTO `NodeType` (`id`) VALUES (:id)");
        mUpdateQuery = createQuery("UPDATE `NodeType` SET `id`=:id WHERE `id`=:id");
    }

    emitDatabaseChanged();
}

Node *NodeTypeStorage::createNode()
{
    mNodes.append(new NodeType{storage(), storage()});
    return mNodes.last();
}

bool NodeTypeStorage::insertNode(Node *node)
{
    Transaction tx{Transaction::WriteModified, node, storage()};

    if (!storage()->nodeStorage()->insertNode(node))
        return false;

    NodeType *nodeType = static_cast<NodeType *>(node);

    if (!executeQuery(mInsertQuery, QVariantMap{{":id", nodeType->rowid()}}))
        return handleError(this, "insertNode", mInsertQuery), false;

    tx.commit();

    return true;
}

bool NodeTypeStorage::updateNode(Node *node)
{
    Transaction tx{Transaction::WriteModified, node, storage()};

    if (!storage()->nodeStorage()->updateNode(node))
        return false;

    // NodeType *nodeType = static_cast<NodeType *>(node);

    // if (!executeQuery(mUpdateQuery, QVariantMap{{":id", nodeType->rowid()}}))
    //     return handleError(this, "updateNode", mUpdateQuery), false;

    tx.commit();

    return true;
}

bool NodeTypeStorage::reloadNode(Node *node)
{
    Transaction tx{Transaction::ReadModified, node, storage()};

    if (!storage()->nodeStorage()->reloadNode(node))
        return false;

    NodeType *nodeType = static_cast<NodeType *>(node);

    if (!executeQuery(mReloadQuery, {nodeType->rowid()}))
        return handleError(this, "reloadNode", mReloadQuery), false;

    if (!mReloadQuery.next())
        return handleError(this, "reloadNode", "result set is empty"), false;

    tx.commit();

    return true;
}

bool NodeTypeStorage::removeNode(int rowid)
{
    if (rowid <= 0) {
        handleError(this, "removeNode", "rowid is invalid");
        return false;
    }

    Transaction tx{Transaction::WriteModified, mNodesByRowid.value(rowid), storage()};

    if (!storage()->nodeStorage()->removeNode(rowid))
        return false;

    tx.commit();

    return true;
}
