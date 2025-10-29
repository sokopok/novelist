#include "valuetype.h"
#include "storage.h"

Value *ValueType::createValue(const QVariant &value)
{
    if (Value *v = storage()->valueStorage()->value()) {
        v->setNodeType(this);
        v->setValue(value);
        return v;
    }
    return nullptr;
}

bool ValueType::reload()
{
    return storage()->valueTypeStorage()->reloadNode(this);
}

bool ValueType::save(bool newVersion)
{
    return storage()->valueTypeStorage()->saveNode(this, newVersion);
}

bool ValueType::recycle()
{
    return storage()->valueTypeStorage()->recycleNode(this);
}

bool ValueType::readJson(const QJsonObject &json, QStringList *errors)
{
    if (!NodeType::readJson(json, errors))
        return false;

    return true;

    Q_UNUSED(errors);
}

bool ValueType::writeJson(QJsonObject &json, QStringList *errors) const
{
    if (!NodeType::writeJson(json, errors))
        return false;

    return true;

    Q_UNUSED(errors);
}
