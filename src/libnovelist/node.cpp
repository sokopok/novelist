#include "node.h"
#include "project.h"
#include "projectstore.h"

namespace novelist {

// ProjectStore *Node::mProjectStore = new ProjectStore;

bool Node::reload()
{
    if (auto *store = projectStore(); !store) {
        setError({ai::Error::InternalErrorType, ai::Error::InternalError, "reload"});
        return false;
    }

    else if (!store->reload(this)) {
        setError({ai::Error::InternalErrorType, ai::Error::InternalError, "reload"});
        return false;
    }

    emit loaded(QPrivateSignal{});

    return true;
}

bool Node::save()
{
    if (auto *store = projectStore(); !store) {
        setError({ai::Error::InternalErrorType, ai::Error::InternalError, "save"});
        return false;
    }

    else if (!store->save(this)) {
        setError({ai::Error::InternalErrorType, ai::Error::InternalError, "save"});
        return false;
    }

    emit saved(QPrivateSignal{});

    return true;
}

void Node::recycle()
{
    if (auto *store = projectStore())
        store->recycle(this);
    else
        deleteLater();
}

void Node::reuse(const QVariantMap &values) {}

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

void Node::setError(const ai::Error &error)
{
    mError = error;
    if (mError.code() != ai::Error::NoError) {
        // qCWarning(LOGAI)
        //     << "ERROR!"
        //     << mError.type()
        //     << mError.code()
        //     << mError.message()
        //     << mError.param();
        emit errorOccurred(mError, QPrivateSignal{});
    }
    emit errorChanged(QPrivateSignal{});
}

void Node::setNodeType(NodeType *nodeType)
{
    if (mNodeType == nodeType)
        return;
    mNodeType = nodeType;
    emit nodeTypeChanged();
}

void Node::setName(const QString &name, ExplicitHandling e)
{
    setExplicit(NameTag, e);

    if (mName == name)
        return;
    mName = name;
    emit nameChanged(QPrivateSignal{});
}

void Node::setLabel(const QString &label, ExplicitHandling e)
{
    setExplicit(LabelTag, e);

    if (mLabel == label)
        return;
    mLabel = label;
    emit labelChanged(QPrivateSignal{});
}

void Node::setDescription(const QString &description, ExplicitHandling e)
{
    setExplicit(DescriptionTag, e);

    if (mDescription == description)
        return;
    mDescription = description;
    emit descriptionChanged(QPrivateSignal{});
}

void Node::setIcon(const QString &icon, ExplicitHandling e)
{
    setExplicit(IconTag, e);

    if (mIcon == icon)
        return;
    mIcon = icon;
    emit iconChanged(QPrivateSignal{});
}

void Node::setSaveStrategry(const SaveStrategry &saveStrategry)
{
    if (mSaveStrategry == saveStrategry)
        return;
    mSaveStrategry = saveStrategry;
    emit saveStrategryChanged(QPrivateSignal{});
}

} // namespace novelist
