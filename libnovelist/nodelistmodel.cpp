#include "nodelistmodel.h"
#include "node.h"

QVariant NodeListModel::data(const QModelIndex &index, int role) const
{
    if (Node *node = mNodes.value(index.row())) {
        switch (role) {
        case NodeRole:
        case Qt::EditRole:
            return QVariant::fromValue(node);
        case NameRole:
            return node->name();
        case LabelRole:
        case Qt::DisplayRole:
            return node->label();
        case InfoRole:
            return node->info();
        case IconRole:
            return node->icon();
        }
    }
    return {};
}

void NodeListModel::setNodes(const QList<Node *> &nodes)
{
    if (mNodes == nodes)
        return;
    beginResetModel();
    for (Node *node : std::as_const(nodes))
        node->disconnect(this);
    mNodes = nodes;
    for (Node *node : std::as_const(nodes)) {
        connect(node, &Node::nameChanged, this, [this, node]() {
            const auto idx = index(mNodes.indexOf(node), 0);
            emit dataChanged(idx, idx, {NameRole});
        });
        connect(node, &Node::labelChanged, this, [this, node]() {
            const auto idx = index(mNodes.indexOf(node), 0);
            emit dataChanged(idx, idx, {LabelRole});
        });
        connect(node, &Node::infoChanged, this, [this, node]() {
            const auto idx = index(mNodes.indexOf(node), 0);
            emit dataChanged(idx, idx, {InfoRole});
        });
        connect(node, &Node::iconChanged, this, [this, node]() {
            const auto idx = index(mNodes.indexOf(node), 0);
            emit dataChanged(idx, idx, {IconRole});
        });
    }
    endResetModel();
    emit nodesChanged(QPrivateSignal{});
}

void NodeListModel::setNode(Node *node)
{
    if (mNode == node)
        return;
    if (mNode)
        mNode->disconnect(this);
    mNode = node;
    if (mNode) {
        connect(mNode, &Node::childNodeAdded, this, [this]() {
            setNodes(mNode->findChildren<Node *>(Qt::FindDirectChildrenOnly));
        });
        connect(mNode, &Node::childNodeRemoved, this, [this]() {
            setNodes(mNode->findChildren<Node *>(Qt::FindDirectChildrenOnly));
        });
    }
    setNodes(mNode ? mNode->findChildren<Node *>(Qt::FindDirectChildrenOnly) : QList<Node *>{});

    emit nodeChanged(QPrivateSignal{});
}
