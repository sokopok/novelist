#include "field.h"
#include "element.h"
#include "nodetype.h"
#include "validator.h"

namespace novelist {

// Field *Field::load(int type, int id)
// {
//     if (auto *store = Project::staticProjectStore(); !store)
//         return nullptr;

//     else if (Node *node = store->load(type, id); !node)
//         return nullptr;

//     else if (Field *field = qobject_cast<Field *>(node); !field) {
//         store->recycle(field);
//         return nullptr;
//     }

//     else
//         return field;
// }

FieldType *Field::fieldType() const
{
    return static_cast<FieldType *>(nodeType());
}

void Field::setNodeType(FieldType *nodeType)
{
    Node::setNodeType(nodeType);
}

void Field::setElement(Element *element)
{
    if (mElement == element)
        return;
    if (mElement)
        mElement->disconnect(this);
    mElement = element;
    setParent(mElement);
    if (mElement)
        ;
    emit elementChanged(QPrivateSignal{});
}

void Field::setValue(const QVariant &value, ExplicitHandling e)
{
    setExplicit(ValueTag, e);

    if (mValue == value)
        return;

    mValue = value;

    if (validate() || fixup()) {
        setEmpty(mValue.isNull() || !mValue.isValid());
        setValid(true);

        if (saveStrategry() == SaveImmediately)
            save();
    }

    else {
        setValid(false);
        setModified(true);
    }

    emit valueChanged(QPrivateSignal{});
}

void Field::setDefaultValue(const QVariant &defaultValue)
{
    if (mDefaultValue == defaultValue)
        return;
    mDefaultValue = defaultValue;
    explicits().setBit(DefaultTag);
    emit defaultValueChanged(QPrivateSignal{});
}

void Field::setTypes(const QStringList &types)
{
    if (mTypes == types)
        return;
    mTypes = types;
    emit typesChanged(QPrivateSignal{});
}

bool Field::setJson(const QJsonObject &json)
{
    if (const auto v = json.value("type");
        !v.isString() || v.toString().isEmpty() || !mTypes.contains(v.toString())) {
        setError({ai::Error::InternalErrorType,
                  ai::Error::InternalError,
                  "Field::setJson",
                  v.toString()});
        return false;
    }

    if (const auto v = json.value("name"); v.isString()
                                           && !v.toString().isEmpty()
                                           && v.toString() != name()
                                           && mElement->field(v.toString())) {
        setError({ai::Error::InternalErrorType,
                  ai::Error::InternalError,
                  "Field::setJson",
                  v.toString()});
        return false;
    }

    if (!Node::setJson(json))
        return false;

    setType(json.value("type").toString());

    if (const auto v = json.value("default"); !v.isUndefined())
        setDefaultValue(v.toVariant());

    if (const auto v = json.value("value"); !v.isUndefined())
        setValue(v.toVariant());

    return true;
}

bool Field::reload()
{
    if (auto *store = projectStore(); !store) {
        setError({ai::Error::InternalErrorType, ai::Error::InternalError, "Field::reload"});
        return false;
    }

    else if (!store->reload(this)) {
        setError({ai::Error::InternalErrorType, ai::Error::InternalError, "Field::reload"});
        return false;
    }

    setModified(false);
    return true;
}

bool Field::save()
{
    if (auto *store = projectStore(); !store) {
        setError({ai::Error::InternalErrorType, ai::Error::InternalError, "Field::save"});
        return false;
    }

    else if (!store->save(this)) {
        setError({ai::Error::InternalErrorType, ai::Error::InternalError, "Field::save"});
        return false;
    }

    setModified(false);
    return true;
}

// void Field::setVersion(int version)
// {
//     if (mVersion == version)
//         return;
//     mVersion = version;
//     // emit versionChanged();
// }

void Field::setType(const QString &type)
{
    if (!mTypes.contains(type))
        return;

    if (mType == type)
        return;

    mType = type;
    emit typeChanged(QPrivateSignal{});
}

bool Field::validate(const QVariant &value, QStringList *messages) const
{
    if (auto *validator = mValidators.value(mType)) {
        auto input = value;
        return validator->validate(input, messages);
    }
    return true;
}

QVariant Field::fixup(const QVariant &value, QStringList *messages) const
{
    if (auto *validator = mValidators.value(mType)) {
        auto input = value;
        if (validator->fixup(input, messages))
            return input;
    }
    return value;
}

QJsonObject Field::toSchema(bool *error) const
{
    bool e;
    QJsonObject json = Node::toSchema(&e);

    if (e) {
        if (error)
            *error = true;
        return json;
    }

    QJsonArray oneOf;
    for (const auto &type : mTypes) {
        if (auto *v = validator(type)) {
            oneOf.append(v->toSchema(&e));
            if (e) {
                if (error)
                    *error = true;
                return json;
            }
        }

        else
            oneOf.append(typeSchema(type));
    }
    json["oneOf"] = oneOf;

    if (error)
        *error = false;

    return json;
}

} // namespace novelist
