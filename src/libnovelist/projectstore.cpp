#include "projectstore.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "element.h"
#include "field.h"
#include "libnovelist/nodetype.h"
#include "node.h"
#include "project.h"

namespace novelist {

ProjectStore::ProjectStore(QObject* parent)
    : QObject{parent}
{}

Node *ProjectStore::load(const QString &type, int rowid, double version)
{
    NodeType *nodeType = loadType(type);

    if (!nodeType) {
        // setError({});
        return nullptr;
    }

    if (rowid <= 0) {
        // setError({});
        return nullptr;
    }

    QSqlQuery q;

    if (version == LastVersion) {
        q.prepare(
            QStringLiteral("SELECT * FROM `%1` WHERE `rowid`=? ORDER BY `version` DESC LIMIT 1")
                .arg(nodeType->table()));
        q.addBindValue(rowid);
    } else {
        q.prepare(QStringLiteral("SELECT * FROM `%1` WHERE `rowid`=? AND `version`=? LIMIT 1")
                      .arg(nodeType->table()));
        q.addBindValue(rowid);
        q.addBindValue(version);
    };

    if (!q.exec() || !q.next()) {
        // setError({});
        return nullptr;
    }

    if (Node *node = wakeupOrCreate(type)) {
        if (!reload(node)) {
            recycle(node);
            // setError({});
            return nullptr;
        }

        return node;
    }

    // setError({});
    return nullptr;
}

bool ProjectStore::reload(Node *node)
{
    if (!node) {
        // setError({});
        return false;
    }

    if (Element *e = qobject_cast<Element *>(node))
        return reloadElement(e);

    if (Field *f = qobject_cast<Field *>(node))
        return reloadField(f);

    // setError({});
    return false;
}

bool ProjectStore::save(Node *node)
{
    if (!node) {
        // setError({});
        return false;
    }

    if (Element *e = qobject_cast<Element *>(node))
        return saveElement(e);

    if (Field *f = qobject_cast<Field *>(node))
        return saveField(f);

    // setError({});
    return false;
}

bool ProjectStore::refresh(Node *node, const QSqlRecord &record)
{
    if (auto *e = qobject_cast<Element *>(node))
        return refreshElement(e, record);
    if (auto *f = qobject_cast<Field *>(node))
        return refreshField(f, record);
    return false;
}

bool ProjectStore::refreshElement(Element *element, const QSqlRecord &record)
{
    if (!element || record.isEmpty())
        return false;

    if (const auto v = record.value("label"); v.isValid())
        element->setLabel(v.toString());

    if (const auto v = record.value("description"); v.isValid())
        element->setDescription(v.toString());

    if (const auto v = record.value("icon"); v.isValid())
        element->setIcon(v.toString());

    element->setRowid(record.value("rowid").toInt());
    element->setVersion(record.value("version").toInt());

    return true;
}

bool ProjectStore::refreshField(Field *field, const QSqlRecord &record)
{
    if (!field || record.isEmpty())
        return false;

    if (const auto v = record.value("label"); v.isValid())
        field->setLabel(v.toString());

    if (const auto v = record.value("description"); v.isValid())
        field->setDescription(v.toString());

    if (const auto v = record.value("icon"); v.isValid())
        field->setIcon(v.toString());

    field->setDefaultValue(record.value("default"));
    field->setValue(record.value("value"));

    field->setRowid(record.value("rowid").toInt());
    field->setVersion(record.value("version").toInt());

    return true;
}

void ProjectStore::recycle(Node *node)
{
    if (node) {
        node->disconnect();
        mNodeCache[node->nodeType()->name()].append(node);
    }
    // setError({});
}

Node *ProjectStore::wakeup(const QString &type)
{
    if (mNodeCache.contains(type)) {
        QList<Node *> &nodes = mNodeCache[type];
        if (!nodes.isEmpty())
            return nodes.takeLast();
    }
    // setError({});
    return nullptr;
}

Node *ProjectStore::create(const QString &type)
{
    if (auto *nodeType = loadType(type)) {
        return nodeType->create(mProject);
    }
    // setError({});
    return nullptr;
}

NodeType *ProjectStore::loadType(const QString &type) const
{
    if (auto *nodetype = mNodeTypes.value(type))
        return nodetype;
    // setError({});
    return nullptr;
}

bool ProjectStore::reloadElement(Element *element)
{
    QSqlQuery q;
    q.prepare(
        QStringLiteral("SELECT * FROM `%1` WHERE `rowid`=?").arg(element->nodeType()->table()));
    q.addBindValue(element->rowid());

    if (!q.exec() || !q.next()) {
        // setError({});
        return false;
    }

    if (!refreshElement(element, q.record())) {
        // setError({});
        return false;
    }

    for (const auto fields = element->fields(); Field *field : fields) {
        field->setRowid(q.value(field->name()).toInt());

        if (!reloadField(field)) {
            // setError({});
            return false;
        }
    }

    return true;
}

bool ProjectStore::reloadField(Field *field)
{
    QSqlQuery q;
    q.prepare(QStringLiteral("SELECT * FROM `%1` WHERE `rowid`=?").arg(field->nodeType()->table()));
    q.addBindValue(field->rowid());

    if (!q.exec() || !q.next()) {
        // setError({});
        return false;
    }

    return refreshField(field, q.record());
}

bool ProjectStore::saveElement(Element *element)
{
    return false;
}

bool ProjectStore::saveField(Field *field)
{
    return false;
}

bool ProjectStore::createDatabase(const QString &databaseName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databaseName);
    if (!db.open()) {
        return false;
    }

    QSqlQuery("CREATE TABLE `nodetype` ("
              "`rowid`          INTEGER NOT NULL UNIQUE,"
              "`type`           TEXT NOT NULL UNIQUE,"
              "`table`          TEXT NOT NULL,"
              "`name`           TEXT NOT NULL,"
              "`label`          TEXT NOT NULL,"
              "`description`    TEXT NOT NULL,"
              "`icon`           TEXT NOT NULL,"
              "PRIMARY KEY(`rowid` AUTOINCREMENT)"
              ")");

    QSqlQuery("CREATE TABLE `elementtype` ("
              "`rowid`	INTEGER NOT NULL UNIQUE,"
              "`type`	TEXT NOT NULL UNIQUE,"
              "PRIMARY KEY(`rowid` AUTOINCREMENT)"
              ")");

    QSqlQuery("CREATE TABLE `fieldtype` ("
              "`rowid`	INTEGER NOT NULL UNIQUE,"
              "`type`	TEXT NOT NULL UNIQUE,"
              "PRIMARY KEY(`rowid` AUTOINCREMENT)"
              ")");

    return true;
}

void ProjectStore::setProject(Project *project)
{
    if (mProject == project)
        return;
    mProject = project;
    emit projectChanged();
}

} // namespace novelist
