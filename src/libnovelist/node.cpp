#include "node.h"
#include "project.h"
#include "projectstore.h"

namespace novelist {

bool Node::reload()
{
    if (auto *store = projectStore(); !store) {
        throwError(NoProjectStoreError, __FILE__, __LINE__);
        return false;
    }

    else if (!store->reload(this)) {
        throwError(ProjectStoreLoadError, __FILE__, __LINE__);
        return false;
    }

    emit loaded();

    return true;
}

bool Node::save()
{
    if (auto *store = projectStore(); !store) {
        throwError(NoProjectStoreError, __FILE__, __LINE__);
        return false;
    }

    else if (!store->save(this)) {
        throwError(ProjectStoreSaveError, __FILE__, __LINE__);
        return false;
    }

    emit saved();

    return true;
}

void Node::recycle()
{
    if (auto *store = projectStore())
        store->recycle(this);
    else
        deleteLater();
}

ProjectStore *Node::projectStore() const
{
    return project()->projectStore();
}

Project *Node::project() const
{
    if (Node *node = qobject_cast<Node *>(parent())) {
        return node->project();
    }
    return nullptr;
}

} // namespace novelist
