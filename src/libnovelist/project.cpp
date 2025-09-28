#include "project.h"
#include "projectstore.h"

namespace novelist {

Project::Project(QObject *parent)
    : Node{parent}
    , mSelf{this}
{
    if (!staticProjectStore())
        resetStaticProjectStore();
}

void Project::resetStaticProjectStore()
{
    setStaticProjectStore(new ProjectStore);
}

bool Project::reload()
{
    return projectStore()->reloadProject(this);
}

bool Project::save()
{
    return projectStore()->saveProject(this);
}

bool Project::saveAs(const QString &filename)
{
    return projectStore()->saveProjectAs(this, filename);
}

Project *Project::load(const QString &filename)
{
    staticProjectStore()->setFilename(filename);
    return staticProjectStore()->loadProject("project", "");
}

} // namespace novelist
