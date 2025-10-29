#ifndef LIBNOVELIST_ELEMENTTYPE_H
#define LIBNOVELIST_ELEMENTTYPE_H

#include "fieldtypelistmodel.h"
#include "nodetype.h"

class FieldType;
class Element;

class ElementType : public NodeType
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("")

public:
    explicit ElementType(Storage* storage, QObject* parent = nullptr)
        : ElementType{Type_ElementType, storage, parent}
    {}
    ElementType(int type, Storage* storage, QObject* parent = nullptr)
        : NodeType{type, storage, parent}
    {}

    [[nodiscard]] Element* createElement();
    [[nodiscard]] Element* element(int rowid);

    bool reload() override;
    bool save(bool newVersion = true) override;
    bool recycle() override;

    [[nodiscard]] QList<FieldType*> fieldTypes() const { return mFieldTypes; }
    void setFieldTypes(const QList<FieldType*>& fieldTypes);

    [[nodiscard]] FieldType* fieldType(int index) const { return mFieldTypes.value(index); }
    [[nodiscard]] FieldType* fieldType(const QString& name) const
    {
        return mFieldTypesByName.value(name);
    }
    bool insertFieldType(int index, FieldType* fieldType);
    bool appendFieldType(FieldType* fieldType)
    {
        return insertFieldType(mFieldTypes.size(), fieldType);
    }
    bool prependFieldType(FieldType* fieldType) { return insertFieldType(0, fieldType); }
    bool removeFieldType(FieldType* fieldType)
    {
        if (!fieldType)
            return false;
        int index = mFieldTypes.indexOf(fieldType);
        while (index >= 0) {
            if (!removeFieldTypeAt(index))
                return false;
            index = mFieldTypes.indexOf(fieldType, index);
        }
        return true;
    }
    bool removeFieldTypeAt(int index);
    FieldType* takeFieldTypeAt(int index)
    {
        if (index < 0 || index >= mFieldTypes.size())
            return nullptr;
        FieldType* fieldType = mFieldTypes[index];
        if (!removeFieldTypeAt(index))
            return nullptr;
        return fieldType;
    }

    [[nodiscard]] FieldTypeListModel* fieldTypeListModel();

signals:
    void fieldTypesChanged(QPrivateSignal);
    void fieldTypesAdded(int first, int last, QPrivateSignal);
    void fieldTypesRemoved(int first, int last, QPrivateSignal);

protected:
    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override;
    bool writeJson(QJsonObject& json, QStringList* errors = nullptr) const override;

    bool updateFieldTypes();

private:
    QList<FieldType*> mFieldTypes;
    QMap<QString, FieldType*> mFieldTypesByName;
    FieldTypeListModel* mFieldTypeListModel = nullptr;

    Q_PROPERTY(QList<FieldType*> fieldTypes READ fieldTypes WRITE setFieldTypes NOTIFY
                   fieldTypesChanged FINAL)
    Q_PROPERTY(FieldTypeListModel* fieldTypeListModel READ fieldTypeListModel CONSTANT FINAL)
};

#endif // LIBNOVELIST_ELEMENTTYPE_H
