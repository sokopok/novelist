#include "elementtype.h"
#include "fieldtype.h"
#include "storage.h"

#include <QJsonArray>

Element *ElementType::createElement()
{
    if (Element *e = storage()->elementStorage()->element()) {
        e->setNodeType(this);
        return e;
    }
    return nullptr;
}

Element *ElementType::element(int rowid)
{
    if (Element *e = storage()->elementStorage()->element(rowid)) {
        e->setNodeType(this);
        return e;
    }
    return nullptr;
}

bool ElementType::reload()
{
    return storage()->elementTypeStorage()->reloadNode(this);
}

bool ElementType::save(bool newVersion)
{
    return storage()->elementTypeStorage()->saveNode(this, newVersion);
}

bool ElementType::recycle()
{
    return storage()->elementTypeStorage()->recycleNode(this);
}

void ElementType::setFieldTypes(const QList<FieldType *> &fieldTypes)
{
    if (mFieldTypes == fieldTypes)
        return;

    for (FieldType *t : std::as_const(mFieldTypes))
        if (!fieldTypes.contains(t)) {
            t->disconnect(this);
            disconnect(t);
        }

    mFieldTypes = fieldTypes;

    mFieldTypesByName.clear();
    for (FieldType *t : std::as_const(mFieldTypes)) {
        mFieldTypesByName.insert(t->name(), t);
        t->addElementType(this);
        if (!qobject_cast<ElementType *>(t->parent()))
            t->setParent(this);
    }
    if (!updateFieldTypes())
        setModified(true);

    emit fieldTypesChanged(QPrivateSignal{});
}

bool ElementType::insertFieldType(int index, FieldType *fieldType)
{
    if (!fieldType)
        return handleError(this, "insertFieldType", "fieldtype is null"), false;

    if (index < 0 || index > mFieldTypes.size())
        return handleError(this, "insertField", "index out of range"), false;

    if (fieldType->name().isEmpty())
        return handleError(this, "insertField", "fieldtype name is empty"), false;

    if (mFieldTypes.contains(fieldType))
        return handleError(this,
                           "insertField",
                           QStringLiteral("elementtype already contains fieldtype with name '%1'")
                               .arg(fieldType->name())),
               false;

    mFieldTypes.insert(index, fieldType);
    mFieldTypesByName.insert(fieldType->name(), fieldType);

    fieldType->addElementType(this);
    if (!qobject_cast<ElementType *>(fieldType->parent()))
        fieldType->setParent(this);

    if (!updateFieldTypes())
        setModified(true);

    emit fieldTypesAdded(index, index, QPrivateSignal{});
    emit fieldTypesChanged(QPrivateSignal{});
    return true;
}

bool ElementType::removeFieldTypeAt(int index)
{
    if (index < 0 || index >= mFieldTypes.size())
        return handleError(this, "insertField", "index out of range"), false;

    FieldType *fieldType = mFieldTypes[index];

    mFieldTypes.removeAt(index);
    mFieldTypesByName.remove(fieldType->name());

    fieldType->removeElementType(this);
    if (fieldType->parent() == this)
        fieldType->recycle();

    if (!updateFieldTypes())
        setModified(true);

    emit fieldTypesRemoved(index, index, QPrivateSignal{});
    emit fieldTypesChanged(QPrivateSignal{});
    return true;
}

FieldTypeListModel *ElementType::fieldTypeListModel()
{
    if (!mFieldTypeListModel) {
        mFieldTypeListModel = new FieldTypeListModel{this, this};
    }
    return mFieldTypeListModel;
}

bool ElementType::readJson(const QJsonObject &json, QStringList *errors)
{
    if (!NodeType::readJson(json, errors))
        return false;

    if (const auto v = json.value(QStringLiteral("fieldTypes")); v.isArray()) {
        const auto a = v.toArray();
        for (const auto &v : a) {
            const auto f = v.toObject();
            if (const auto n = f.value(QStringLiteral("name")).toString(); !n.isEmpty()) {
                if (FieldType *F = fieldType(n)) {
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

bool ElementType::writeJson(QJsonObject &json, QStringList *errors) const
{
    if (!NodeType::writeJson(json, errors))
        return false;

    QJsonArray fields;
    for (FieldType *field : std::as_const(mFieldTypes))
        fields.append(field->toJson(errors));

    if (!fields.isEmpty())
        json.insert(QStringLiteral("fieldTypes"), fields);

    return true;

    Q_UNUSED(errors);
}

bool ElementType::updateFieldTypes()
{
    if (rowid() <= 0 || isLoading() || isSaving())
        return false;
    return storage()->elementTypeStorage()->updateFieldTypes(this);
}
