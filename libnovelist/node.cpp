#include "node.h"
#include "nodelistmodel.h"
#include "nodetype.h"
#include "storage.h"

#include <QChildEvent>

bool Node::reload()
{
    return storage()->nodeStorage()->reloadNode(this);
}

bool Node::save(bool newVersion)
{
    return storage()->nodeStorage()->saveNode(this, newVersion);
}

bool Node::recycle()
{
    return storage()->nodeStorage()->recycleNode(this);
}

QString Node::label() const
{
    return mNodeType && mLabel.isEmpty() ? mNodeType->label() : mLabel;
}

QString Node::info() const
{
    return mNodeType && mInfo.isEmpty() ? mNodeType->info() : mInfo;
}

QString Node::icon() const
{
    return mNodeType && mIcon.isEmpty() ? mNodeType->icon() : mIcon;
}

void Node::setNodeType(NodeType *nodeType, bool emitSignals)
{
    if (mNodeType == nodeType)
        return;

    auto old = mNodeType;

    if (mNodeType)
        mNodeType->disconnect(this);

    mNodeType = nodeType;

    setName(mNodeType ? mNodeType->name() : QString{});
    setLabel({});
    setInfo({});
    setIcon({});

    if (mNodeType) {
        connect(mNodeType, &Node::labelChanged, this, [this]() {
            if (mLabel.isEmpty())
                emit nameChanged(mNodeType->label(), mLabel, QPrivateSignal{});
        });
        connect(mNodeType, &Node::infoChanged, this, [this]() {
            if (mInfo.isEmpty())
                emit nameChanged(mNodeType->info(), mInfo, QPrivateSignal{});
        });
        connect(mNodeType, &Node::iconChanged, this, [this]() {
            if (mIcon.isEmpty())
                emit nameChanged(mNodeType->icon(), mIcon, QPrivateSignal{});
        });
    }

    if (!updateNodeType())
        setModified(true);

    if (emitSignals)
        emitNodeTypeChanged(mNodeType, old);
}

bool Node::updateName()
{
    if (rowid() <= 0 || isLoading() || isSaving())
        return false;
    return storage()->nodeStorage()->updateName(this);
}

bool Node::updateLabel()
{
    if (rowid() <= 0 || isLoading() || isSaving())
        return false;
    return storage()->nodeStorage()->updateLabel(this);
}

bool Node::updateInfo()
{
    if (rowid() <= 0 || isLoading() || isSaving())
        return false;
    return storage()->nodeStorage()->updateInfo(this);
}

bool Node::updateIcon()
{
    if (rowid() <= 0 || isLoading() || isSaving())
        return false;
    return storage()->nodeStorage()->updateIcon(this);
}

bool Node::updateNodeType()
{
    if (rowid() <= 0 || isLoading() || isSaving())
        return false;
    return storage()->nodeStorage()->updateNodeType(this);
}

NodeListModel *Node::nodeListModel()
{
    if (!mNodeListModel) {
        mNodeListModel = new NodeListModel{this, this};
    }
    return mNodeListModel;
}

bool Node::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::ChildAdded:
        emit childNodeAdded(qobject_cast<Node *>(static_cast<QChildEvent *>(event)->child()),
                            QPrivateSignal{});
        break;
    case QEvent::ChildRemoved:
        emit childNodeRemoved(qobject_cast<Node *>(static_cast<QChildEvent *>(event)->child()),
                              QPrivateSignal{});
        break;
    default:
        break;
    }

    return Storable::event(event);
}

bool Node::writeJson(QJsonObject &json, QStringList *errors) const
{
    if (!Storable::writeJson(json, errors))
        return false;

    json.insert(QStringLiteral("name"), mName);

    if (!mLabel.isEmpty())
        json.insert(QStringLiteral("label"), mLabel);

    if (!mInfo.isEmpty())
        json.insert(QStringLiteral("info"), mInfo);

    if (!mIcon.isEmpty())
        json.insert(QStringLiteral("icon"), mIcon);

    if (mNodeType)
        json.insert(QStringLiteral("nodeType"), mNodeType->rowid());

    return true;

    Q_UNUSED(errors);
}
