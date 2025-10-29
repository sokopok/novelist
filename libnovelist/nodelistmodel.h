#ifndef LIBNOVELIST_NODELISTMODEL_H
#define LIBNOVELIST_NODELISTMODEL_H

#include <QAbstractListModel>
#include <qqmlintegration.h>

class Node;

class NodeListModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum Role { NodeRole = Qt::UserRole, NameRole, LabelRole, InfoRole, IconRole, UserRole };
    Q_ENUM(Role)

    explicit NodeListModel(QObject *parent = nullptr)
        : QAbstractListModel(parent)
    {}
    explicit NodeListModel(const QList<Node *> &nodes, QObject *parent = nullptr)
        : QAbstractListModel(parent)
    {
        setNodes(nodes);
    }
    explicit NodeListModel(Node *node, QObject *parent = nullptr)
        : QAbstractListModel(parent)
    {
        setNode(node);
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override
    {
        return parent.isValid() ? 0 : mNodes.size();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roleNames = QAbstractListModel::roleNames();
        roleNames[NodeRole] = "node";
        roleNames[NameRole] = "name";
        roleNames[LabelRole] = "label";
        roleNames[InfoRole] = "info";
        roleNames[IconRole] = "iconSource";
        return roleNames;
    }

    [[nodiscard]] QList<Node *> nodes() const { return mNodes; }
    [[nodiscard]] Node *node(int index) const { return mNodes.value(index); }
    void setNodes(const QList<Node *> &nodes);

    [[nodiscard]] Node *node() const { return mNode; }
    void setNode(Node *node);

signals:
    void nodesChanged(QPrivateSignal);
    void nodeChanged(QPrivateSignal);

private:
    QList<Node *> mNodes;
    Node *mNode = nullptr;

    Q_PROPERTY(QList<Node *> nodes READ nodes WRITE setNodes NOTIFY nodesChanged FINAL)
    Q_PROPERTY(Node *node READ node WRITE setNode NOTIFY nodeChanged FINAL)
};

#endif // LIBNOVELIST_NODELISTMODEL_H
