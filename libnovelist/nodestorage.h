#ifndef NODESTORAGE_H
#define NODESTORAGE_H

#include <QHash>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "basestorage.h"
#include "node.h"

class Storage;

class NodeStorage : public BaseStorage
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit NodeStorage(Storage* parent = nullptr);

    void setDatabase(const QSqlDatabase& database) override;

    QList<Node*> allNodes() const { return mNodes; }

protected:
    [[nodiscard]] Node* createNode() override;
    bool insertNode(Node* node) override;
    bool updateNode(Node* node) override;
    bool reloadNode(Node* node) override;
    bool removeNode(int rowid) override;

    bool updateName(Node* node);
    bool updateLabel(Node* node);
    bool updateInfo(Node* node);
    bool updateIcon(Node* node);
    bool updateNodeType(Node* node);

    QSqlQuery mReloadQuery;
    QSqlQuery mReloadNodeQuery;
    QSqlQuery mInsertStorableQuery;
    QSqlQuery mInsertNodeQuery;
    QSqlQuery mUpdateStorableQuery;
    QSqlQuery mUpdateNodeQuery;
    QSqlQuery mRemoveStorableQuery;
    QSqlQuery mRemoveNodeQuery;

    friend class Node;
    friend class ElementStorage;
    friend class FieldStorage;
    friend class ValueStorage;
    friend class ProjectStorage;
    friend class NodeTypeStorage;
    friend class Storage;
};

#endif // NODESTORAGE_H
