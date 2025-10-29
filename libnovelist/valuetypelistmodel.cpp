#include "valuetypelistmodel.h"
#include "fieldtype.h"
#include "valuetype.h"

QVariant ValueTypeListModel::data(const QModelIndex &index, int role) const
{
    if (ValueType *valueType = mValueTypes.value(index.row())) {
        switch (role) {
        case ValueTypeRole:
        case Qt::EditRole:
            return QVariant::fromValue(valueType);
        case NameRole:
            return valueType->name();
        case LabelRole:
        case Qt::DisplayRole:
            return valueType->label();
        case InfoRole:
            return valueType->info();
        case IconRole:
            return valueType->icon();
        }
    }
    return {};
}

void ValueTypeListModel::setValueTypes(const QList<ValueType *> &valueTypes)
{
    if (mValueTypes == valueTypes)
        return;
    beginResetModel();
    for (ValueType *valueType : std::as_const(mValueTypes))
        valueType->disconnect(this);
    mValueTypes = valueTypes;
    for (ValueType *valueType : std::as_const(mValueTypes)) {
        connect(valueType, &Node::nameChanged, this, [this, valueType]() {
            const auto idx = index(mValueTypes.indexOf(valueType), 0);
            emit dataChanged(idx, idx, {NameRole});
        });
        connect(valueType, &Node::labelChanged, this, [this, valueType]() {
            const auto idx = index(mValueTypes.indexOf(valueType), 0);
            emit dataChanged(idx, idx, {LabelRole});
        });
        connect(valueType, &Node::infoChanged, this, [this, valueType]() {
            const auto idx = index(mValueTypes.indexOf(valueType), 0);
            emit dataChanged(idx, idx, {InfoRole});
        });
        connect(valueType, &Node::iconChanged, this, [this, valueType]() {
            const auto idx = index(mValueTypes.indexOf(valueType), 0);
            emit dataChanged(idx, idx, {IconRole});
        });
    }
    endResetModel();
    emit valueTypesChanged(QPrivateSignal{});
}

void ValueTypeListModel::setFieldType(FieldType *fieldType)
{
    if (mFieldType == fieldType)
        return;
    if (mFieldType)
        mFieldType->disconnect(this);
    mFieldType = fieldType;
    if (mFieldType) {
        setValueTypes(fieldType->valueTypes());
        connect(mFieldType, &FieldType::valueTypesChanged, this, [this]() {
            setValueTypes(mFieldType->valueTypes());
        });
    } else
        setValueTypes({});
    emit fieldTypeChanged(QPrivateSignal{});
}
