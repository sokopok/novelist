#ifndef LIBNOVELIST_VALUETYPE_H
#define LIBNOVELIST_VALUETYPE_H

#include "nodetype.h"

class FieldType;
class Value;

class ValueType : public NodeType
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("")

public:
    explicit ValueType(Storage* storage, QObject* parent = nullptr)
        : ValueType{Type_ValueType, storage, parent}
    {}
    ValueType(int type, Storage* storage, QObject* parent = nullptr)
        : NodeType{type, storage, parent}
    {}

    [[nodiscard]] Value* createValue(const QVariant& value = {});

    bool reload() override;
    bool save(bool newVersion = true) override;
    bool recycle() override;

    [[nodiscard]] QList<FieldType*> fieldTypes() const { return mFieldTypes; }
    void setFieldTypes(const QList<FieldType*>& fieldTypes)
    {
        if (mFieldTypes == fieldTypes)
            return;
        mFieldTypes = fieldTypes;
        setModified(true);
        emit fieldTypesChanged(QPrivateSignal{});
    }

    bool addFieldType(FieldType* fieldType)
    {
        if (!fieldType)
            return false;
        if (mFieldTypes.contains(fieldType))
            return true;
        mFieldTypes.append(fieldType);
        setModified(true);
        emit fieldTypesChanged(QPrivateSignal{});
        return true;
    }
    bool removeFieldType(FieldType* fieldType)
    {
        if (!fieldType)
            return false;
        if (!mFieldTypes.removeOne(fieldType))
            return false;
        setModified(true);
        emit fieldTypesChanged(QPrivateSignal{});
        return true;
    }

signals:
    void fieldTypesChanged(QPrivateSignal);

protected:
    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override;
    bool writeJson(QJsonObject& json, QStringList* errors = nullptr) const override;

private:
    QList<FieldType*> mFieldTypes;

    friend class FieldType;

    Q_PROPERTY(QList<FieldType*> fieldTypes READ fieldTypes WRITE setFieldTypes NOTIFY
                   fieldTypesChanged FINAL)
};

#endif // LIBNOVELIST_VALUETYPE_H
