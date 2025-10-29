#include "field.h"

#include "storage.h"
#include "valuelistmodel.h"

#include <QJsonArray>

bool Field::reload()
{
    return storage()->fieldStorage()->reloadNode(this);
}

bool Field::save(bool newVersion)
{
    return storage()->fieldStorage()->saveNode(this, newVersion);
}

bool Field::recycle()
{
    return storage()->fieldStorage()->recycleNode(this);
}

void Field::setValues(const QList<Value *> &values)
{
    if (mValues == values)
        return;

    for (Value *v : std::as_const(mValues))
        if (!values.contains(v)) {
            v->disconnect(this);
            disconnect(v);
        }

    mValues = values;

    for (Value *v : std::as_const(mValues)) {
        v->addField(this);
        if (!qobject_cast<Field *>(v->parent()))
            v->setParent(this);
    }

    if (!updateValues())
        setModified(true);

    emit valuesChanged(QPrivateSignal{});
}

bool Field::insertValue(int index, Value *value)
{
    if (!value)
        return handleError(this, "insertValue", "value is null"), false;

    if (index < 0 || index > mValues.size())
        return handleError(this, "insertValue", "index out of range"), false;

    if (mValues.contains(value))
        return handleError(this, "insertValue", "field already contains value"), false;

    mValues.insert(index, value);

    value->addField(this);
    if (!qobject_cast<Field *>(value->parent()))
        value->setParent(this);

    if (!updateValues())
        setModified(true);

    emit valuesAdded(index, index, QPrivateSignal{});
    emit valuesChanged(QPrivateSignal{});
    return true;
}

bool Field::appendValue(int type, const QVariant &value)
{
    if (ValueType *valueType = storage()->valueTypeStorage()->valueType(Value::typeToString(type)))
        return appendValue(valueType->createValue(value));
    return false;
}

bool Field::appendValue(const QString &type, const QVariant &value)
{
    if (ValueType *valueType = storage()->valueTypeStorage()->valueType(type))
        return appendValue(valueType->createValue(value));
    return false;
}

bool Field::removeValueAt(int index)
{
    if (index < 0 || index >= mValues.size())
        return handleError(this, "removeValueAt", "index out of range"), false;

    Value *value = mValues[index];

    mValues.removeAt(index);

    value->removeField(this);
    if (value->parent() == this)
        value->recycle();

    if (!updateValues())
        setModified(true);

    emit valuesRemoved(index, index, QPrivateSignal{});
    emit valuesChanged(QPrivateSignal{});
    return true;
}

int Field::indexIn(Element *element) const
{
    return element->fields().indexOf(this);
}

ValueListModel *Field::valueListModel()
{
    if (!mValueListModel) {
        mValueListModel = new ValueListModel{this, this};
    }
    return mValueListModel;
}

bool Field::readJson(const QJsonObject &json, QStringList *errors)
{
    if (!Node::readJson(json, errors))
        return false;

    if (const auto v = json.value(QStringLiteral("values")); v.isArray()) {
        const auto a = v.toArray();
        int index = -1;
        for (const auto &i : a) {
            ++index;
            const auto v = i.toObject();
            if (Value *V = value(index)) {
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

bool Field::writeJson(QJsonObject &json, QStringList *errors) const
{
    if (!Node::writeJson(json, errors))
        return false;

    // json.insert(QStringLiteral("index"), indexIn());

    if (mMinOccurs >= 0)
        json.insert(QStringLiteral("minOccurs"), mMinOccurs);

    if (mMaxOccurs >= 0)
        json.insert(QStringLiteral("maxOccurs"), mMaxOccurs);

    if (!mAllowedTypes.isEmpty())
        json.insert(QStringLiteral("allowedTypes"), allowedTypeNames().join('\n'));

    QJsonArray values;
    for (Value *value : std::as_const(mValues))
        values.append(value->toJson(errors));

    if (!values.isEmpty())
        json.insert(QStringLiteral("values"), values);

    return true;

    Q_UNUSED(errors);
}

bool Field::updateValues()
{
    if (rowid() <= 0 || isLoading() || isSaving())
        return false;
    return storage()->fieldStorage()->updateValues(this);
}

bool Field::updateAllowedTypes()
{
    if (rowid() <= 0 || isLoading() || isSaving())
        return false;
    return storage()->fieldStorage()->updateAllowedTypes(this);
}

bool Field::updateMinOccurs()
{
    if (rowid() <= 0 || isLoading() || isSaving())
        return false;
    return storage()->fieldStorage()->updateMinOccurs(this);
}

bool Field::updateMaxOccurs()
{
    if (rowid() <= 0 || isLoading() || isSaving())
        return false;
    return storage()->fieldStorage()->updateMaxOccurs(this);
}
