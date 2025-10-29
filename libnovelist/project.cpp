#include "project.h"
#include "storage.h"

bool Project::reload()
{
    return storage()->projectStorage()->reloadNode(this);
}

bool Project::save(bool newVersion)
{
    return storage()->projectStorage()->saveNode(this, newVersion);
}

bool Project::recycle()
{
    return storage()->projectStorage()->recycleNode(this);
}

void Project::setStorage(Storage *storage)
{
    if (this->storage() == storage)
        return;

    if (this->storage()) {
        this->storage()->disconnect(this);
    }

    Element::setStorage(storage);

    if (this->storage()) {
        connect(this->storage(), &Storage::databaseNameChanged, this, &Project::databaseNameChanged);
    }

    emit storageChanged();
}

QString Project::databaseName() const
{
    return storage() ? storage()->databaseName() : "";
}

void Project::setDatabaseName(const QString &databaseName)
{
    if (!storage())
        return;
    storage()->setDatabaseName(databaseName);
}

QList<ElementType *> Project::elementTypes() const
{
    return storage() ? storage()->elementTypeStorage()->allElementTypes() : QList<ElementType *>{};
}

ElementType *Project::elementType(const QString &name) const
{
    return storage() ? storage()->elementTypeStorage()->elementType(name) : nullptr;
}

ElementType *Project::addElementType(const QString &name,
                                     const QString &label,
                                     const QString &info,
                                     const QString &icon)
{
    return storage() ? storage()->elementTypeStorage()->createElementType(name, label, info, icon)
                     : nullptr;
}

QList<FieldType *> Project::fieldTypes() const
{
    return storage() ? storage()->fieldTypeStorage()->allFieldTypes() : QList<FieldType *>{};
}

FieldType *Project::fieldType(const QString &name) const
{
    return storage() ? storage()->fieldTypeStorage()->fieldType(name) : nullptr;
}

FieldType *Project::addFieldType(const QString &name,
                                 const QString &label,
                                 const QString &info,
                                 const QString &icon)
{
    return storage() ? storage()->fieldTypeStorage()->createFieldType(name, label, info, icon)
                     : nullptr;
}

QList<ValueType *> Project::valueTypes() const
{
    return storage() ? storage()->valueTypeStorage()->allValueTypes() : QList<ValueType *>{};
}

ValueType *Project::valueType(const QString &name) const
{
    return storage() ? storage()->valueTypeStorage()->valueType(name) : nullptr;
}

ValueType *Project::addValueType(const QString &name,
                                 const QString &label,
                                 const QString &info,
                                 const QString &icon)
{
    return storage() ? storage()->valueTypeStorage()->createValueType(name, label, info, icon)
                     : nullptr;
}

Element *Project::elementFromStorage(int rowid) const
{
    return storage() ? storage()->elementStorage()->element(rowid) : nullptr;
}

Element *Project::addElement(ElementType *elementType,
                             const QString &label,
                             const QString &info,
                             const QString &icon)
{
    return storage() ? storage()->elementStorage()->createElement(elementType, label, info, icon)
                     : nullptr;
}

Field *Project::fieldFromStorage(int rowid) const
{
    return storage() ? storage()->fieldStorage()->field(rowid) : nullptr;
}

Field *Project::addField(FieldType *fieldType,
                         const QString &label,
                         const QString &info,
                         const QString &icon)
{
    return storage() ? storage()->fieldStorage()->createField(fieldType, label, info, icon)
                     : nullptr;
}

Value *Project::valueFromStorage(int rowid) const
{
    return storage() ? storage()->valueStorage()->value(rowid) : nullptr;
}

Value *Project::addValue(ValueType *valueType,
                         const QString &label,
                         const QString &info,
                         const QString &icon)
{
    return storage() ? storage()->valueStorage()->createValue(valueType, label, info, icon)
                     : nullptr;
}
