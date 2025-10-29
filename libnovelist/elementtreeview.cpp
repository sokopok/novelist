#include "elementtreeview.h"
#include "element.h"
#include "field.h"

ElementTreeView::ElementTreeView(QObject *parent)
    : QAbstractItemModel(parent)
{}

QModelIndex ElementTreeView::index(int row, int /*column*/, const QModelIndex &parent) const
{
    if (Element *e = static_cast<Element *>(parent.internalPointer())) {
        if (row >= 0 && row < e->fields().size())
            return createIndex(row, 0, e->field(row));
    } else if (Field *f = static_cast<Field *>(parent.internalPointer())) {
        if (row >= 0 && row < f->values().size())
            return createIndex(row, 0, f->value(row));
    }
    if (row >= 0 && row < mRoot->fields().size())
        return createIndex(row, 0, mRoot->field(row));
    return {};
}

QModelIndex ElementTreeView::parent(const QModelIndex &index) const
{
    if (Field *f = static_cast<Field *>(index.internalPointer())) {
        if (row >= 0 && row < f->values().size())
            return createIndex(row, 0, f->value(row));
    }
}

int ElementTreeView::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int ElementTreeView::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant ElementTreeView::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
