#include "fieldlistmodel.h"
#include "element.h"
#include "field.h"
#include "valuelistmodel.h"

QVariant FieldListModel::data(const QModelIndex &index, int role) const
{
    if (Field *field = mFields.value(index.row())) {
        switch (role) {
        case FieldRole:
        case Qt::EditRole:
            return QVariant::fromValue(field);
        case NameRole:
            return field->name();
        case LabelRole:
        case Qt::DisplayRole:
            return field->label();
        case InfoRole:
            return field->info();
        case IconRole:
            return field->icon();
        case MinOccursRole:
            return field->minOccurs();
        case MaxOccursRole:
            return field->maxOccurs();
        case AllowesTypesRole:
            return field->allowedTypeNames();
        case ValuesRole:
            return QVariant::fromValue(field->valueListModel());
        }
    }
    return {};
}

void FieldListModel::setFields(const QList<Field *> &fields)
{
    if (mFields == fields)
        return;
    beginResetModel();
    for (Field *field : std::as_const(mFields))
        field->disconnect(this);
    mFields = fields;
    for (Field *field : std::as_const(mFields)) {
        connect(field, &Node::nameChanged, this, [this, field]() {
            const auto idx = index(mFields.indexOf(field), 0);
            emit dataChanged(idx, idx, {NameRole});
        });
        connect(field, &Node::labelChanged, this, [this, field]() {
            const auto idx = index(mFields.indexOf(field), 0);
            emit dataChanged(idx, idx, {LabelRole});
        });
        connect(field, &Node::infoChanged, this, [this, field]() {
            const auto idx = index(mFields.indexOf(field), 0);
            emit dataChanged(idx, idx, {InfoRole});
        });
        connect(field, &Node::iconChanged, this, [this, field]() {
            const auto idx = index(mFields.indexOf(field), 0);
            emit dataChanged(idx, idx, {IconRole});
        });
        connect(field, &Field::minOccursChanged, this, [this, field]() {
            const auto idx = index(mFields.indexOf(field), 0);
            emit dataChanged(idx, idx, {MinOccursRole});
        });
        connect(field, &Field::maxOccursChanged, this, [this, field]() {
            const auto idx = index(mFields.indexOf(field), 0);
            emit dataChanged(idx, idx, {MaxOccursRole});
        });
        connect(field, &Field::allowedTypesChanged, this, [this, field]() {
            const auto idx = index(mFields.indexOf(field), 0);
            emit dataChanged(idx, idx, {AllowesTypesRole});
        });
    }
    endResetModel();
    emit fieldsChanged(QPrivateSignal{});
}

void FieldListModel::setElement(Element *element)
{
    if (mElement == element)
        return;
    if (mElement)
        mElement->disconnect(this);
    mElement = element;
    if (mElement) {
        setFields(element->fields());
        connect(mElement, &Element::fieldsChanged, this, [this]() {
            setFields(mElement->fields());
        });
    } else
        setFields({});
    emit elementChanged(QPrivateSignal{});
}
