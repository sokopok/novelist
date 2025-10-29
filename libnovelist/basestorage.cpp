#include "basestorage.h"
#include "storage.h"

BaseStorage::BaseStorage(Storage *parent)
    : QObject{parent}
{}

Storage *BaseStorage::storage() const
{
    return qobject_cast<Storage *>(parent());
}

Transaction::Transaction(Mode mode, Node *node, Storage *storage)
    : db(storage->database())
    , node(node)
    , depth(storage->transactionDepth())
    , owner(depth++ == 0)
    , mode(mode)
{
    if (owner) {
        if (mode & Write)
            db.transaction();
        if (node) {
            (mode & Read) ? node->setLoading(true) : node->setSaving(true);
        }
    }
}

void Transaction::commit()
{
    if (owner && !done) {
        if (mode & Write)
            db.commit();
        done = true;
        depth = 0;
    }
    if (done && node) {
        (mode & Read) ? node->setLoading(false) : node->setSaving(false);
        if (mode & Modified)
            node->setModified(false);
    }
}
