#include "projectstore.h"
#include <QSqlQuery>
#include "node.h"

namespace novelist {

ProjectStore::ProjectStore(QObject* parent)
    : QObject{parent}
{}

Node *ProjectStore::load(int type, int id, double version)
{
    if (!loadType(type))
        return nullptr;

    if (id <= 0)
        return nullptr;

    QSqlQuery q;

    if (version != LastVersion) {
        q.prepare(QStringLiteral("SELECT * FROM `%1` WHERE `id`=? ORDER BY `version` DESC LIMIT 1")
                      .arg(""));
        q.addBindValue(id);
    } else {
        q.prepare(QStringLiteral("SELECT * FROM `%1` WHERE `id`=? AND `version`=? LIMIT 1").arg(""));
        q.addBindValue(id);
        q.addBindValue(version);
    }

    if (!q.exec() || !q.next())
        return nullptr;

    if (Node *node = wakeupOrCreate(type)) {
        return node;
    }

    return nullptr;
}

void ProjectStore::recycle(Node *node)
{
    if (node) {
        node->disconnect();
        mNodeCache[node->type()].append(node);
    }
}

} // namespace novelist
