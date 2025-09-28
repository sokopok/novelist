#include "element.h"
#include "project.h"

namespace novelist {

Element *Element::load(int type, int id)
{
    if (auto *store = Project::staticProjectStore(); !store)
        return nullptr;

    else if (Node *node = store->load(type, id); !node)
        return nullptr;

    else if (Element *element = qobject_cast<Element *>(node); !element) {
        store->recycle(element);
        return nullptr;
    }

    else
        return element;
}

} // namespace novelist
