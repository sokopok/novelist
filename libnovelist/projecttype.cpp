#include "projecttype.h"
#include "storage.h"

bool ProjectType::reload()
{
    return storage()->projectTypeStorage()->reloadNode(this);
}

bool ProjectType::save(bool newVersion)
{
    return storage()->projectTypeStorage()->saveNode(this, newVersion);
}

bool ProjectType::recycle()
{
    return storage()->projectTypeStorage()->recycleNode(this);
}
