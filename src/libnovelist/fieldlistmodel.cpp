#include "fieldlistmodel.h"
#include "element.h"
#include "field.h"

namespace novelist {

FieldListModel::FieldListModel(QObject *parent)
    : QAbstractListModel{parent}
{
    setElement(qobject_cast<Element *>(parent));

    connect(this, &FieldListModel::rowsInserted, this, [this]() { emit rowCountChanged(); });
    connect(this, &FieldListModel::rowsRemoved, this, [this]() { emit rowCountChanged(); });
}

int FieldListModel::rowCount(const QModelIndex &parent) const
{
    return !mElement || parent.isValid() ? 0 : mElement->fields().size();
}

QVariant FieldListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mElement)
        return {};

    if (Field *field = mElement->field(index.row())) {
        switch (role) {
        case LabelRole:
            return field->label();
        case ValueRole:
            return field->value();
        }
    }

    return {};
}

bool FieldListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || !mElement)
        return false;

    if (Field *field = mElement->field(index.row())) {
        switch (role) {
        case LabelRole:
            if (field->label() != value.toString()) {
                field->setLabel(value.toString());
                emit dataChanged(index, index, {role});
                return true;
            }
        case ValueRole:
            if (field->value() != value.toString()) {
                field->setValue(value.toString());
                emit dataChanged(index, index, {role});
                return true;
            }
        }
    }

    return false;
}

Qt::ItemFlags FieldListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void FieldListModel::setElement(Element *element)
{
    if (mElement == element)
        return;
    if (mElement)
        mElement->disconnect(this);
    beginResetModel();
    mElement = element;
    endResetModel();
    if (mElement)
        connect(mElement, &Element::fieldsChanged, this, [this]() {
            beginResetModel();
            endResetModel();
        });
    emit elementChanged();
}

} // namespace novelist
