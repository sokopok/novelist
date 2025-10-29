#include "projectstorage.h"
#include "storage.h"

void ProjectStorage::setDatabase(const QSqlDatabase &database)
{
    mDatabase = database;

    if (mDatabase.isOpen()) {
        executeQuery("CREATE TABLE IF NOT EXISTS `Project` (\n"
                     "  `id`	   INTEGER NOT NULL UNIQUE,\n"
                     "  PRIMARY KEY(`id`),\n"
                     "  FOREIGN KEY(`id`) REFERENCES Storable(`id`) ON DELETE CASCADE\n"
                     ")");

        mReloadQuery = createQuery("SELECT * FROM `Project` WHERE `id`=:id");
        mInsertQuery = createQuery("INSERT INTO `Project` (`id`) VALUES (:id)");
        mUpdateQuery = createQuery("UPDATE `Project` SET `id`=:id WHERE `id`=:id");
    }

    emitDatabaseChanged();
}

Project *ProjectStorage::createProject(const QString &type)
{
    if (ProjectType *projectType = storage()->projectTypeStorage()->projectType(type))
        return createProject(projectType);
    return nullptr;
}

Node *ProjectStorage::createNode()
{
    mNodes.append(new Project{storage(), storage()});
    return mNodes.last();
}

bool ProjectStorage::insertNode(Node *node)
{
    Transaction tx{Transaction::WriteModified, node, storage()};

    if (!storage()->elementStorage()->insertNode(node))
        return false;

    // Project *project = static_cast<Project *>(node);

    tx.commit();

    return true;
}

bool ProjectStorage::updateNode(Node *node)
{
    Transaction tx{Transaction::WriteModified, node, storage()};

    if (!storage()->elementStorage()->updateNode(node))
        return false;

    // Project *project = static_cast<Project *>(node);

    // if (!executeQuery(mUpdateQuery, QVariantMap{{":id", project->rowid()}})) {
    //     handleError("");
    //     return false;
    // }

    tx.commit();

    return true;
}

bool ProjectStorage::reloadNode(Node *node)
{
    Transaction tx{Transaction::ReadModified, node, storage()};

    if (!storage()->elementStorage()->reloadNode(node))
        return false;

    Project *project = static_cast<Project *>(node);

    if (!executeQuery(mReloadQuery, {project->rowid()}))
        return handleError(this, "reloadNode", mReloadQuery), false;

    if (!mReloadQuery.next())
        return handleError(this, "reloadNode", "result set is empty"), false;

    tx.commit();

    return true;
}

bool ProjectStorage::removeNode(int rowid)
{
    if (rowid <= 0)
        return handleError(this, "removeNode", "rowid is invalid"), false;

    Transaction tx{Transaction::WriteModified, mNodesByRowid.value(rowid), storage()};

    if (!storage()->nodeStorage()->removeNode(rowid))
        return false;

    tx.commit();

    return true;
}
