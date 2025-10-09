#include "projectstore.h"
#include <QSqlQuery>
#include "element.h"
#include "field.h"
#include "libnovelist/nodetype.h"
#include "node.h"
#include "project.h"

namespace novelist {

ProjectStore::ProjectStore(QObject* parent)
    : QObject{parent}
{}

Node *ProjectStore::load(int type, int id, double version)
{
    NodeType *nodeType = loadType(type);

    if (!nodeType) {
        // setError({});
        return nullptr;
    }

    if (id <= 0) {
        // setError({});
        return nullptr;
    }

    QSqlQuery q;

    if (version == LastVersion) {
        q.prepare(QStringLiteral("SELECT * FROM `%1` WHERE `id`=? ORDER BY `version` DESC LIMIT 1")
                      .arg(nodeType->table()));
        q.addBindValue(id);
    } else {
        q.prepare(
            QStringLiteral("SELECT * FROM `%1` WHERE `id`=? AND `version`=? LIMIT 1").arg(nodeType->table()));
        q.addBindValue(id);
        q.addBindValue(version);
    };

    if (!q.exec() || !q.next()) {
        // setError({});
        return nullptr;
    }

    if (Node *node = wakeupOrCreate(type)) {
        if (!reload(node)) {
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

void ProjectStore::recycle(Node *node)
{
    if (node) {
        node->disconnect();
        mNodeCache[node->nodeType()->type()].append(node);
    }
    // setError({});
}

Node *ProjectStore::wakeup(int type)
{
    if (mNodeCache.contains(type)) {
        QList<Node *> &nodes = mNodeCache[type];
        if (!nodes.isEmpty())
            return nodes.takeLast();
    }
    // setError({});
    return nullptr;
}

Node *ProjectStore::create(int type)
{
    if (auto *nodeType = loadType(type)) {
        return nodeType->create(mProject);
    }
    // setError({});
    return nullptr;
}

NodeType *ProjectStore::loadType(int type) const
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

    field->setDefaultValue(q.value("default"));
    field->setValue(q.value("value"));
    field->setVersion(q.value("version").toInt());

    return true;
}

bool ProjectStore::saveElement(Element *element)
{
    return false;
}

bool ProjectStore::saveField(Field *field)
{
    return false;
}

void ProjectStore::setProject(Project *project)
{
    if (mProject == project)
        return;
    mProject = project;
    emit projectChanged();
}

} // namespace novelist
