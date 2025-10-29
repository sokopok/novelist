#ifndef LIBNOVELIST_NODETYPE_H
#define LIBNOVELIST_NODETYPE_H

#include "node.h"

class NodeType : public Node
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("NodeType is a base class")

public:
    explicit NodeType(Storage* storage, QObject* parent = nullptr)
        : NodeType{Type_NodeType, storage, parent}
    {}
    NodeType(int type, Storage* storage, QObject* parent = nullptr)
        : Node{type, storage, parent}
    {}

    // bool reload() override;
    // bool save(bool newVersion = true) override;
    // bool recycle() override;
};

#endif // LIBNOVELIST_NODETYPE_H
