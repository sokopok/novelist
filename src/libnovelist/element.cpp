#include "element.h"
#include "field.h"
#include "fieldlistmodel.h"
#include "project.h"

namespace novelist {

// Element *Element::load(int type, int id)
// {
//     if (auto *store = Project::staticProjectStore(); !store)
//         return nullptr;

//     else if (Node *node = store->load(type, id); !node)
//         return nullptr;

//     else if (Element *element = qobject_cast<Element *>(node); !element) {
//         store->recycle(element);
//         return nullptr;
//     }

//     else
//         return element;
// }

Element::Element(const QString &type, QObject *parent)
    : Node{parent}
    , mType{type}
    , mFieldListModel{new FieldListModel{this}}
{}

void Element::setType(const QString &type)
{
    if (mType == type)
        return;

    mType = type;
    emit typeChanged(QPrivateSignal{});
}

Field *Element::appendField(Field *field)
{
    mFields.append(field);
    mFieldMap[field->name()] = field;
    field->setElement(this);
    emit fieldsChanged(QPrivateSignal{});
    return field;
}

QJsonObject Element::toJson(bool *error) const
{
    QJsonObject json = Node::toJson(error);

    if (error && *error)
        return json;

    json["type"] = mType;

    QJsonArray fields;
    for (Field *field : mFields) {
        fields.append(field->toJson(error));
        if (error && *error)
            return json;
    }
    json["fields"] = fields;

    if (error)
        *error = false;

    return json;
}

bool Element::setJson(const QJsonObject &json)
{
    if (json["type"].toString() != mType) {
        setError({ai::Error::InternalErrorType,
                  ai::Error::InternalError,
                  "Element::setJson",
                  json["type"].toString()});
        return false;
    }

    if (!Node::setJson(json))
        return false;

    if (const auto v = json["fields"]; v.isArray()) {
        const auto a = v.toArray();
        for (const auto v : a) {
            QJsonObject f = v.toObject();

            if (f["type"].toString() != "field")
                return false;

            else if (Field *F = field(f.value("name").toString()); !F)
                return false;

            else if (!F->setJson(f))
                return false;
        }
    }

    return true;
}

} // namespace novelist
