#include "elementtypelistmodel.h"
#include "elementtype.h"
#include "fieldtype.h"
#include "fieldtypelistmodel.h"

QVariant ElementTypeListModel::data(const QModelIndex &index, int role) const
{
    if (ElementType *elementType = mElementTypes.value(index.row())) {
        switch (role) {
        case ElementTypeRole:
        case Qt::EditRole:
            return QVariant::fromValue(elementType);
        case NameRole:
            return elementType->name();
        case LabelRole:
        case Qt::DisplayRole:
            return elementType->label();
        case InfoRole:
            return elementType->info();
        case IconRole:
            return elementType->icon();
        case FieldTypesRole:
            return QVariant::fromValue(elementType->fieldTypeListModel());
        }
    }
    return {};
}

void ElementTypeListModel::setElementTypes(const QList<ElementType *> &elementTypes)
{
    if (mElementTypes == elementTypes)
        return;
    beginResetModel();
    for (ElementType *elementType : std::as_const(mElementTypes))
        elementType->disconnect(this);
    mElementTypes = elementTypes;
    for (ElementType *elementType : std::as_const(mElementTypes)) {
        connect(elementType, &Node::nameChanged, this, [this, elementType]() {
            const auto idx = index(mElementTypes.indexOf(elementType), 0);
            emit dataChanged(idx, idx, {NameRole});
        });
        connect(elementType, &Node::labelChanged, this, [this, elementType]() {
            const auto idx = index(mElementTypes.indexOf(elementType), 0);
            emit dataChanged(idx, idx, {LabelRole});
        });
        connect(elementType, &Node::infoChanged, this, [this, elementType]() {
            const auto idx = index(mElementTypes.indexOf(elementType), 0);
            emit dataChanged(idx, idx, {InfoRole});
        });
        connect(elementType, &Node::iconChanged, this, [this, elementType]() {
            const auto idx = index(mElementTypes.indexOf(elementType), 0);
            emit dataChanged(idx, idx, {IconRole});
        });
        connect(elementType, &ElementType::fieldTypesChanged, this, [this, elementType]() {
            const auto idx = index(mElementTypes.indexOf(elementType), 0);
            emit dataChanged(idx, idx, {FieldTypesRole});
        });
    }
    endResetModel();
    emit elementTypesChanged(QPrivateSignal{});
}
