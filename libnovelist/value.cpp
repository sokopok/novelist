#include "value.h"
#include "storage.h"

bool Value::reload()
{
    return storage()->valueStorage()->reloadNode(this);
}

bool Value::save(bool newVersion)
{
    return storage()->valueStorage()->saveNode(this, newVersion);
}

bool Value::recycle()
{
    return storage()->valueStorage()->recycleNode(this);
}

void Value::setValue(const QVariant &value)
{
    QVariant v = value;
    bool ok = false;
    if (!mValue.isValid() || !QMetaType::canConvert(v.metaType(), mValue.metaType())) {
        if (mFields.isEmpty())
            ok = true;
        else if (mFields.front()->allowedTypes().contains(typeIdToType(v.typeId()))) {
            ok = true;
        } else {
            for (auto t : mFields.front()->allowedTypes()) {
                if (QMetaType::canConvert(v.metaType(), QMetaType{typeToTypeId(t)})) {
                    v.convert(QMetaType{typeToTypeId(t)});
                    ok = true;
                    break;
                }
            }
        }
    } else {
        ok = true;
        v.convert(mValue.metaType());
    }

    if (!ok || mValue == v)
        return;

    mValue = v;

    setValueType(typeIdToType(mValue.typeId()));

    if (!updateValue())
        setModified(true);

    emit valueChanged(QPrivateSignal{});
}

int Value::indexIn(Field *field) const
{
    return field->values().indexOf(this);
}

bool Value::readJson(const QJsonObject &json, QStringList *errors)
{
    if (!Node::readJson(json, errors))
        return false;

    if (const auto v = json.value(QStringLiteral("valueType")); v.isDouble())
        setValueType(v.toInt());

    if (const auto v = json.value(QStringLiteral("value")); true)
        setValue(v.toVariant());

    return true;

    Q_UNUSED(errors);
}

bool Value::writeJson(QJsonObject &json, QStringList *errors) const
{
    if (!Node::writeJson(json, errors))
        return false;

    json.insert(QStringLiteral("valueType"), mValueType);
    json.insert(QStringLiteral("value"), QJsonValue::fromVariant(mValue));

    return true;

    Q_UNUSED(errors);
}

bool Value::updateValue()
{
    if (rowid() <= 0 || isLoading() || isSaving())
        return false;
    return storage()->valueStorage()->updateValue(this);
}

bool Value::updateValueType()
{
    if (rowid() <= 0 || isLoading() || isSaving())
        return false;
    return storage()->valueStorage()->updateValueType(this);
}
