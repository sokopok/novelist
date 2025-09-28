#include "field.h"
#include "project.h"

namespace novelist {

Field *Field::load(int type, int id)
{
    if (auto *store = Project::staticProjectStore(); !store)
        return nullptr;

    else if (Node *node = store->load(type, id); !node)
        return nullptr;

    else if (Field *field = qobject_cast<Field *>(node); !field) {
        store->recycle(field);
        return nullptr;
    }

    else
        return field;
}

} // namespace novelist
