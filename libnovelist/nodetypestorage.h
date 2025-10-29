#ifndef LIBNOVELIST_NODETYPESTORAGE_H
#define LIBNOVELIST_NODETYPESTORAGE_H

#include "nodestorage.h"
#include "nodetype.h"

class NodeTypeStorage : public BaseTypeStorage
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit NodeTypeStorage(Storage* parent = nullptr)
        : BaseTypeStorage{parent}
    {}

    void setDatabase(const QSqlDatabase& database) override;

    [[nodiscard]] NodeType* nodeType() { return static_cast<NodeType*>(node()); }
    [[nodiscard]] NodeType* nodeType(int rowid) { return static_cast<NodeType*>(node(rowid)); }
    [[nodiscard]] NodeType* nodeType(const QString& name) { return mNodesByName.value(name); }
    [[nodiscard]] NodeType* createNodeType(const QString& name)
    {
        if (name.isEmpty())
            return handleError(this, "removeNode", "name is empty"), nullptr;

        if (mNodesByName.contains(name))
            return handleError(
                       this,
                       "removeNode",
                       QStringLiteral("storage already contains a type with name '%1'").arg(name)),
                   nullptr;

        if (NodeType* nodeType = static_cast<NodeType*>(createNode())) {
            mNodesByName.insert(name, nodeType);
            return nodeType;
        }

        return nullptr;
    }

    QList<NodeType*> allNodeTypes() const { return toDerived<NodeType>(mNodes); }

protected:
    [[nodiscard]] Node* createNode() override;
    bool insertNode(Node* node) override;
    bool updateNode(Node* node) override;
    bool reloadNode(Node* node) override;
    bool removeNode(int rowid) override;

protected:
    friend class NodeType;
    friend class ElementTypeStorage;
    friend class FieldTypeStorage;
    friend class ValueTypeStorage;
    friend class ProjectTypeStorage;
    friend class Storage;

    QSqlQuery mReloadQuery;
    QSqlQuery mInsertQuery;
    QSqlQuery mUpdateQuery;
};

#endif // LIBNOVELIST_NODETYPESTORAGE_H
