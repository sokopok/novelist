#include "element.h"
#include "field.h"
#include "fieldlistmodel.h"
#include "nodetype.h"

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

ElementType *Element::elementType() const
{
    return static_cast<ElementType *>(nodeType());
}

void Element::setNodeType(ElementType *nodeType)
{
    Node::setNodeType(nodeType);
}

void Element::setType(const QString &type)
{
    if (mType == type)
        return;

    mType = type;
    emit typeChanged(QPrivateSignal{});
}

int Element::insertField(int index, Field *field)
{
    if (field == nullptr || index < 0 || index > mFields.size())
        return -1;
    mFields.insert(index, field);
    mFieldMap[field->name()] = field;
    field->setElement(this);
    emit fieldsChanged(QPrivateSignal{});
    return index;
}

int Element::appendField(Field *field)
{
    return insertField(mFields.size(), field);
}

bool Element::removeField(int index)
{
    if (Field *f = mFields.takeAt(index)) {
        mFieldMap.remove(f->name());
        emit fieldsChanged(QPrivateSignal{});
        return true;
    }
    return false;
}

bool Element::removeField(Field *field)
{
    return removeField(mFields.indexOf(field));
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
    if (json.value("type").toString() != mType) {
        setError({ai::Error::InternalErrorType,
                  ai::Error::InternalError,
                  "Element::setJson",
                  json.value("type").toString()});
        return false;
    }

    if (!Node::setJson(json))
        return false;

    if (const auto v = json.value("fields"); v.isArray()) {
        const auto a = v.toArray();
        for (const auto v : a) {
            QJsonObject f = v.toObject();

            if (Field *F = field(f.value("name").toString()); !F)
                return false;

            else if (!F->setJson(f))
                return false;
        }
    }

    return true;
}

} // namespace novelist
