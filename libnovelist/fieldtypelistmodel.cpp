#include "fieldtypelistmodel.h"
#include "elementtype.h"
#include "fieldtype.h"
#include "valuetypelistmodel.h"

QVariant FieldTypeListModel::data(const QModelIndex &index, int role) const
{
    if (FieldType *fieldType = mFieldTypes.value(index.row())) {
        switch (role) {
        case FieldTypeRole:
        case Qt::EditRole:
            return QVariant::fromValue(fieldType);
        case NameRole:
            return fieldType->name();
        case LabelRole:
        case Qt::DisplayRole:
            return fieldType->label();
        case InfoRole:
            return fieldType->info();
        case IconRole:
            return fieldType->icon();
        case MinOccursRole:
            return fieldType->minOccurs();
        case MaxOccursRole:
            return fieldType->maxOccurs();
        case AllowesTypesRole:
            return fieldType->allowedTypeNames();
        case ValueTypesRole:
            return QVariant::fromValue(fieldType->valueTypeListModel());
        }
    }
    return {};
}

void FieldTypeListModel::setFieldTypes(const QList<FieldType *> &fieldTypes)
{
    if (mFieldTypes == fieldTypes)
        return;
    beginResetModel();
    for (FieldType *fieldType : std::as_const(mFieldTypes))
        fieldType->disconnect(this);
    mFieldTypes = fieldTypes;
    for (FieldType *fieldType : std::as_const(mFieldTypes)) {
        connect(fieldType, &Node::nameChanged, this, [this, fieldType]() {
            const auto idx = index(mFieldTypes.indexOf(fieldType), 0);
            emit dataChanged(idx, idx, {NameRole});
        });
        connect(fieldType, &Node::labelChanged, this, [this, fieldType]() {
            const auto idx = index(mFieldTypes.indexOf(fieldType), 0);
            emit dataChanged(idx, idx, {LabelRole});
        });
        connect(fieldType, &Node::infoChanged, this, [this, fieldType]() {
            const auto idx = index(mFieldTypes.indexOf(fieldType), 0);
            emit dataChanged(idx, idx, {InfoRole});
        });
        connect(fieldType, &Node::iconChanged, this, [this, fieldType]() {
            const auto idx = index(mFieldTypes.indexOf(fieldType), 0);
            emit dataChanged(idx, idx, {IconRole});
        });
        connect(fieldType, &FieldType::minOccursChanged, this, [this, fieldType]() {
            const auto idx = index(mFieldTypes.indexOf(fieldType), 0);
            emit dataChanged(idx, idx, {MinOccursRole});
        });
        connect(fieldType, &FieldType::maxOccursChanged, this, [this, fieldType]() {
            const auto idx = index(mFieldTypes.indexOf(fieldType), 0);
            emit dataChanged(idx, idx, {MaxOccursRole});
        });
        connect(fieldType, &FieldType::allowedTypesChanged, this, [this, fieldType]() {
            const auto idx = index(mFieldTypes.indexOf(fieldType), 0);
            emit dataChanged(idx, idx, {AllowesTypesRole});
        });
    }
    endResetModel();
    emit fieldTypesChanged(QPrivateSignal{});
}

void FieldTypeListModel::setElementType(ElementType *elementType)
{
    if (mElementType == elementType)
        return;
    if (mElementType)
        mElementType->disconnect(this);
    mElementType = elementType;
    if (mElementType) {
        setFieldTypes(elementType->fieldTypes());
        connect(mElementType, &ElementType::fieldTypesChanged, this, [this]() {
            setFieldTypes(mElementType->fieldTypes());
        });
    } else
        setFieldTypes({});
    emit elementTypeChanged(QPrivateSignal{});
}
