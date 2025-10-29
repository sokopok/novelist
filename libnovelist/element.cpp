#include "element.h"

#include "fieldlistmodel.h"
#include "storage.h"

#include <QJsonArray>

bool Element::reload()
{
    return storage()->elementStorage()->reloadNode(this);
}

bool Element::save(bool newVersion)
{
    return storage()->elementStorage()->saveNode(this, newVersion);
}

bool Element::recycle()
{
    return storage()->elementStorage()->recycleNode(this);
}

void Element::setNodeType(NodeType *nodeType, bool emitSignals)
{
    if (this->nodeType() == nodeType)
        return;

    ElementType *et = qobject_cast<ElementType *>(nodeType);
    if (!et)
        return;

    NodeType *oldNodeType = this->nodeType();

    Node::setNodeType(nodeType, false);

    for (Field *f : std::as_const(mFields))
        f->recycle();
    mFields.clear();

    mPerformUpdateFields = false;
    for (FieldType *ft : et->fieldTypes())
        appendField(ft->createField());
    mPerformUpdateFields = true;

    updateFields();

    if (emitSignals)
        emitNodeTypeChanged(this->nodeType(), oldNodeType);
}

bool Element::updateFields()
{
    if (rowid() <= 0 || isLoading() || isSaving())
        return false;
    return storage()->elementStorage()->updateFields(this);
}

void Element::setFields(const QList<Field *> &fields)
{
    if (mFields == fields)
        return;

    for (Field *f : std::as_const(mFields))
        if (!fields.contains(f)) {
            f->disconnect(this);
            disconnect(f);
        }

    mFields = fields;

    mFieldsByName.clear();
    for (Field *f : std::as_const(mFields)) {
        mFieldsByName.insert(f->name(), f);
        f->addElement(this);
        if (!qobject_cast<Element *>(f->parent()))
            f->setParent(this);
    }

    if (!updateFields())
        setModified(true);

    emit fieldsChanged(QPrivateSignal{});
}

bool Element::insertField(int index, Field *field)
{
    if (!field)
        return handleError(this, "insertField", "field is null"), false;

    if (index < 0 || index > mFields.size())
        return handleError(this, "insertField", "index out of range"), false;

    if (field->name().isEmpty())
        return handleError(this, "insertField", "field name is empty"), false;

    if (mFields.contains(field))
        return handleError(
                   this,
                   "insertField",
                   QStringLiteral("element already contains field with name '%1'").arg(field->name())),
               false;

    mFields.insert(index, field);
    mFieldsByName.insert(field->name(), field);

    field->addElement(this);
    if (!qobject_cast<Element *>(field->parent()))
        field->setParent(this);

    if (!updateFields())
        setModified(true);

    emit fieldsAdded(index, index, QPrivateSignal{});
    emit fieldsChanged(QPrivateSignal{});
    return true;
}

bool Element::removeFieldAt(int index)
{
    if (index < 0 || index >= mFields.size())
        return handleError(this, "removeFieldAt", "index out of range"), false;

    Field *field = mFields[index];

    mFields.removeAt(index);
    mFieldsByName.remove(field->name());

    field->removeElement(this);
    if (field->parent() == this)
        field->recycle();

    field->disconnect(this);
    disconnect(field);

    if (!updateFields())
        setModified(true);

    emit fieldsRemoved(index, index, QPrivateSignal{});
    emit fieldsChanged(QPrivateSignal{});
    return true;
}

FieldListModel *Element::fieldListModel()
{
    if (!mFieldListModel)
        mFieldListModel = new FieldListModel{this, this};
    return mFieldListModel;
}

bool Element::readJson(const QJsonObject &json, QStringList *errors)
{
    if (!Node::readJson(json, errors))
        return false;

    if (const auto v = json.value(QStringLiteral("fields")); v.isArray()) {
        const auto a = v.toArray();
        for (const auto &v : a) {
            const auto f = v.toObject();
            if (const auto n = f.value(QStringLiteral("name")).toString(); !n.isEmpty()) {
                if (Field *F = field(n)) {
                    if (!F->readJson(f, errors))
                        return false;
                    continue;
                }
                // create field
            }
        }
    }

    return true;

    Q_UNUSED(errors);
}

bool Element::writeJson(QJsonObject &json, QStringList *errors) const
{
    if (!Node::writeJson(json, errors))
        return false;

    QJsonArray fields;
    for (Field *field : std::as_const(mFields))
        fields.append(field->toJson(errors));

    if (!fields.isEmpty())
        json.insert(QStringLiteral("fields"), fields);

    return true;

    Q_UNUSED(errors);
}
