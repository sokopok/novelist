#include "nodetype.h"
#include "element.h"
#include "field.h"

namespace novelist {

NodeType::NodeType(QObject *parent)
    : QObject{parent}
{}

void NodeType::setTable(const QString &table)
{
    if (mTable == table)
        return;
    mTable = table;
    emit tableChanged();
}

Node *NodeType::create(QObject *parent)
{
    if (isElementType())
        return new Element{parent};

    if (isFieldType())
        return new Field{parent};

    return nullptr;
}

void NodeType::setType(int type)
{
    if (mType == type)
        return;
    mType = type;
    emit typeChanged();
}

} // namespace novelist
