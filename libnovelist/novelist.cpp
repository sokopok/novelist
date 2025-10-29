#include "novelist.h"
#include "project.h"

void Novelist::setProject(Project *project)
{
    if (mProject == project)
        return;

    Storage *storage = mStorage;

    if (mProject) {
        disconnect(mProject);
        mProject->disconnect(this);
    }

    mProject = project;

    if (mProject) {
        connect(mProject, &Project::storageChanged, this, [this]() {
            mStorage = mProject->storage();
            emit storageChanged();
        });
        connect(this, &Novelist::projectChanged, mProject, [project = mProject]() {});
    }

    if (storage != mStorage)
        emit storageChanged();

    emit projectChanged();
}

void Novelist::setStorage(Storage *storage)
{
    if (!mProject) {
        if (mStorage == storage)
            return;
        mStorage = storage;
        emit storageChanged();
        return;
    }
    mProject->setStorage(storage);
}
