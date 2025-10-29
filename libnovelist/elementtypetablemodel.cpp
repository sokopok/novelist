#include "elementtypetablemodel.h"
#include "elementtype.h"
#include "fieldtype.h"
#include "valuetype.h"

ElementTypeTableModel::ElementTypeTableModel(QObject *parent)
    : QAbstractItemModel(parent)
{}

// QVariant ElementTypeTableModel::headerData(int section, Qt::Orientation orientation, int role) const
// {
//     // FIXME: Implement me!
// }

QModelIndex ElementTypeTableModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!parent.isValid())
        return createIndex(row, column, mRows[row]->columns[column]);
    return {};
}

QModelIndex ElementTypeTableModel::parent(const QModelIndex & /*index*/) const
{
    return {};
}

int ElementTypeTableModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : mRows.size();
}

int ElementTypeTableModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() || mRows.isEmpty() ? 0 : mRows.front()->columns.size();
}

QVariant ElementTypeTableModel::data(const QModelIndex &index, int role) const
{
    if (Item *item = static_cast<Item *>(index.internalPointer())) {
        if (Node *node = item->node) {
            switch (index.column()) {
            case 0:
                switch (role) {
                case Qt::DisplayRole:
                case Qt::EditRole:
                    return node->label();
                }
                break;
            case 1:
                switch (role) {
                case Qt::DisplayRole:
                case Qt::EditRole:
                    break;
                }
                break;
            }
        }
    }
    return {};
}

void ElementTypeTableModel::setElementTypes(const QList<ElementType *> &elementTypes)
{
    if (mElementTypes == elementTypes)
        return;

    beginResetModel();

    qDeleteAll(mRows);
    mRows.clear();

    mElementTypes = elementTypes;

    for (ElementType *elementType : std::as_const(mElementTypes)) {
        appendRow(elementType, {new Item{elementType}, new Item{nullptr, Qt::NoItemFlags}});

        for (FieldType *fieldType : elementType->fieldTypes()) {
            appendRow(fieldType, {new Item{fieldType}});

            for (ValueType *valueType : fieldType->valueTypes()) {
                appendRow(valueType, {new Item, new Item{valueType}});
            }
        }
    }

    endResetModel();

    emit elementTypesChanged();
}
