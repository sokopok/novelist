#include "projecttypestorage.h"
#include "projecttype.h"
#include "storage.h"

void ProjectTypeStorage::setDatabase(const QSqlDatabase &database)
{
    mDatabase = database;

    if (mDatabase.isOpen()) {
        executeQuery("CREATE TABLE IF NOT EXISTS `ProjectType` (\n"
                     "  `id`          INTEGER NOT NULL UNIQUE,\n"
                     "  PRIMARY KEY(`id`),\n"
                     "  FOREIGN KEY(`id`) REFERENCES Storable(`id`) ON DELETE CASCADE\n"
                     ")");

        mReloadQuery = createQuery("SELECT * FROM `ProjectType` WHERE `id`=:id");
        mInsertQuery = createQuery("INSERT INTO `ProjectType` (`id`) VALUES (:id)");
        mUpdateQuery = createQuery("UPDATE `ProjectType` SET `id`=:id WHERE `id`=:id");
    }

    emitDatabaseChanged();
}

Node *ProjectTypeStorage::createNode()
{
    mNodes.append(new ProjectType{storage(), storage()});
    return mNodes.last();
}

bool ProjectTypeStorage::insertNode(Node *node)
{
    Transaction tx{Transaction::WriteModified, node, storage()};

    if (!storage()->elementTypeStorage()->insertNode(node))
        return false;

    ProjectType *projectType = static_cast<ProjectType *>(node);

    if (!executeQuery(mInsertQuery, QVariantMap{{":id", projectType->rowid()}}))
        return handleError(this, "insertNode", mInsertQuery), false;

    tx.commit();

    return true;
}

bool ProjectTypeStorage::updateNode(Node *node)
{
    Transaction tx{Transaction::WriteModified, node, storage()};

    if (!storage()->elementTypeStorage()->updateNode(node))
        return false;

    // ProjectType *projectType = static_cast<ProjectType *>(node);

    // if (!executeQuery(mUpdateQuery, QVariantMap{{":id", e->rowid()}})) {
    //     handleError("");
    //     return false;
    // }

    tx.commit();

    return true;
}

bool ProjectTypeStorage::reloadNode(Node *node)
{
    Transaction tx{Transaction::WriteModified, node, storage()};

    if (!storage()->elementTypeStorage()->updateNode(node))
        return false;

    ProjectType *projectType = static_cast<ProjectType *>(node);

    if (!executeQuery(mReloadQuery, {projectType->rowid()}))
        return handleError(this, "reloadNode", mReloadQuery), false;

    if (!mReloadQuery.next())
        return handleError(this, "reloadNode", "result set is empty"), false;

    tx.commit();

    return true;
}

bool ProjectTypeStorage::removeNode(int rowid)
{
    if (rowid <= 0)
        return handleError(this, "removeNode", "rowid is invalid"), false;

    Transaction tx{Transaction::WriteModified, mNodesByRowid.value(rowid), storage()};

    if (!storage()->elementTypeStorage()->removeNode(rowid))
        return false;

    tx.commit();

    return true;
}
