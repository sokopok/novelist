#include "fieldtype.h"
#include "storage.h"

#include <QJsonArray>

Field *FieldType::createField()
{
    if (Field *f = storage()->fieldStorage()->field()) {
        f->setNodeType(this);
        return f;
    }
    return nullptr;
}

bool FieldType::reload()
{
    return storage()->fieldTypeStorage()->reloadNode(this);
}

bool FieldType::save(bool newVersion)
{
    return storage()->fieldTypeStorage()->saveNode(this, newVersion);
}

bool FieldType::recycle()
{
    return storage()->fieldTypeStorage()->recycleNode(this);
}

void FieldType::setValueTypes(const QList<ValueType *> &valueTypes)
{
    if (mValueTypes == valueTypes)
        return;

    for (ValueType *t : std::as_const(mValueTypes))
        if (!valueTypes.contains(t)) {
            t->disconnect(this);
            disconnect(t);
        }

    mValueTypes = valueTypes;

    for (ValueType *t : std::as_const(mValueTypes)) {
        mValueTypesByName.insert(t->name(), t);
        t->addFieldType(this);
        if (!qobject_cast<FieldType *>(t->parent()))
            t->setParent(this);
    }
    if (!updateValueTypes())
        setModified(true);

    emit valueTypesChanged(QPrivateSignal{});
}

bool FieldType::insertValueType(int index, ValueType *valueType)
{
    if (!valueType)
        handleError(this, "insertValueType", "valueType is null");

    if (index < 0 || index > mValueTypes.size())
        handleError(this, "insertValueType", "index out of range");

    if (mValueTypes.contains(valueType))
        handleError(this, "insertValueType", "fieldtype already contains valuetype");

    mValueTypes.insert(index, valueType);
    mValueTypesByName.insert(valueType->name(), valueType);

    valueType->addFieldType(this);
    if (!qobject_cast<FieldType *>(valueType->parent()))
        valueType->setParent(this);

    if (!updateValueTypes())
        setModified(true);

    emit valueTypesAdded(index, index, QPrivateSignal{});
    emit valueTypesChanged(QPrivateSignal{});
    return true;
}

bool FieldType::removeValueTypeAt(int index)
{
    if (index < 0 || index >= mValueTypes.size())
        return handleError(this, "removeValueTypeAt", "index out of range"), false;

    ValueType *valueType = mValueTypes[index];

    mValueTypes.removeAt(index);
    mValueTypesByName.remove(valueType->name());

    valueType->removeFieldType(this);
    if (valueType->parent() == this)
        valueType->recycle();

    if (!updateValueTypes())
        setModified(true);

    emit valueTypesRemoved(index, index, QPrivateSignal{});
    emit valueTypesChanged(QPrivateSignal{});
    return true;
}

ValueTypeListModel *FieldType::valueTypeListModel()
{
    if (!mValueTypeListModel) {
        mValueTypeListModel = new ValueTypeListModel{this, this};
    }
    return mValueTypeListModel;
}

bool FieldType::readJson(const QJsonObject &json, QStringList *errors)
{
    if (!NodeType::readJson(json, errors))
        return false;

    if (const auto v = json.value(QStringLiteral("valueTypes")); v.isArray()) {
        const auto a = v.toArray();
        int index = -1;
        for (const auto &i : a) {
            ++index;
            const auto v = i.toObject();
            if (ValueType *V = valueType(index)) {
                if (!V->readJson(v, errors))
                    return false;
                continue;
            }
            // create field
        }
    }

    return true;

    Q_UNUSED(errors);
}

bool FieldType::writeJson(QJsonObject &json, QStringList *errors) const
{
    if (!NodeType::writeJson(json, errors))
        return false;

    if (mMinOccurs >= 0)
        json.insert(QStringLiteral("minOccurs"), mMinOccurs);

    if (mMaxOccurs >= 0)
        json.insert(QStringLiteral("maxOccurs"), mMaxOccurs);

    if (!mAllowedTypes.isEmpty())
        json.insert(QStringLiteral("allowedTypes"), allowedTypeNames().join('\n'));

    QJsonArray values;
    for (ValueType *value : std::as_const(mValueTypes))
        values.append(value->toJson(errors));

    if (!values.isEmpty())
        json.insert(QStringLiteral("valueTypes"), values);

    return true;

    Q_UNUSED(errors);
}

bool FieldType::updateValueTypes()
{
    if (rowid() <= 0 || isLoading() || isSaving())
        return false;
    return storage()->fieldTypeStorage()->updateValueTypes(this);
}

bool FieldType::updateAllowedTypes()
{
    if (rowid() <= 0 || isLoading() || isSaving())
        return false;
    return storage()->fieldTypeStorage()->updateAllowedTypes(this);
}

bool FieldType::updateMinOccurs()
{
    if (rowid() <= 0 || isLoading() || isSaving())
        return false;
    return storage()->fieldTypeStorage()->updateMinOccurs(this);
}

bool FieldType::updateMaxOccurs()
{
    if (rowid() <= 0 || isLoading() || isSaving())
        return false;
    return storage()->fieldTypeStorage()->updateMaxOccurs(this);
}
