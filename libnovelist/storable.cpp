#include "storable.h"
#include "storage.h"

// bool Storable::reload()
// {
//     return mStorage->reload<Storable>(this, mRowid);
// }

// bool Storable::save(bool newVersion = true)
// {
//     return mStorage->save<Storable>(this, newVersion);
// }

// bool Storable::recycle()
// {
//     return mStorage->recycle<Storable>(this);
// }

Storable::Storable(int type, Storage *storage, QObject *parent)
    : QObject{parent ? parent : storage}
    , mStorage{storage}
    , mType{type}
{}

Storage *Storable::storage() const
{
    if (Storage *storage = qobject_cast<Storage *>(parent()))
        return storage;
    if (Storable *storable = qobject_cast<Storable *>(parent()))
        return storable->storage();
    return nullptr;
}
