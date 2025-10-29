#ifndef LIBNOVELIST_FIELDTYPE_H
#define LIBNOVELIST_FIELDTYPE_H

#include "nodetype.h"
#include "valuetypelistmodel.h"

class ElementType;
class ValueType;
class Field;

class FieldType : public NodeType
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("")

public:
    explicit FieldType(Storage* storage, QObject* parent = nullptr)
        : FieldType{Type_FieldType, storage, parent}
    {}
    FieldType(int type, Storage* storage, QObject* parent = nullptr)
        : NodeType{type, storage, parent}
    {}

    [[nodiscard]] Field* createField();

    bool reload() override;
    bool save(bool newVersion = true) override;
    bool recycle() override;

    [[nodiscard]] QList<ElementType*> elementTypes() const { return mElementTypes; }
    void setElementTypes(const QList<ElementType*>& elementTypes)
    {
        if (mElementTypes == elementTypes)
            return;

        mElementTypes = elementTypes;

        // setModified(true);
        emit elementTypesChanged(QPrivateSignal{});
    }

    bool addElementType(ElementType* elementType)
    {
        if (!elementType)
            return handleError(this, "removeValueTypeAt", "elementType is null"), false;

        if (mElementTypes.contains(elementType))
            return handleError(this, "removeValueTypeAt", "elementtype not found"), true;

        mElementTypes.append(elementType);

        // setModified(true);
        emit elementTypesChanged(QPrivateSignal{});
        return true;
    }
    bool removeElementType(ElementType* elementType)
    {
        if (!elementType)
            return handleError(this, "removeValueTypeAt", "elementType is null"), false;

        if (!mElementTypes.removeOne(elementType))
            return true;

        // setModified(true);
        emit elementTypesChanged(QPrivateSignal{});
        return true;
    }

    [[nodiscard]] QList<ValueType*> valueTypes() const { return mValueTypes; }
    void setValueTypes(const QList<ValueType*>& valueTypes);

    [[nodiscard]] ValueType* valueType(int index) const { return mValueTypes.value(index); }
    [[nodiscard]] ValueType* valueType(const QString& name) const
    {
        return mValueTypesByName.value(name);
    }
    bool insertValueType(int index, ValueType* valueType);
    bool appendValueType(ValueType* valueType)
    {
        return insertValueType(mValueTypes.size(), valueType);
    }
    bool prependValueType(ValueType* valueType) { return insertValueType(0, valueType); }
    bool removeValueType(ValueType* valueType)
    {
        if (!valueType)
            return false;
        int index = mValueTypes.indexOf(valueType);
        while (index >= 0) {
            if (!removeValueTypeAt(index))
                return false;
            index = mValueTypes.indexOf(valueType, index);
        }
        return true;
    }
    bool removeValueTypeAt(int index);
    ValueType* takeValueTypeAt(int index)
    {
        if (index < 0 || index >= mValueTypes.size())
            return nullptr;
        ValueType* valueType = mValueTypes[index];
        if (!removeValueTypeAt(index))
            return nullptr;
        return valueType;
    }

    [[nodiscard]] QList<int> allowedTypes() const { return mAllowedTypes; }
    void setAllowedTypes(const QList<int>& allowedTypes)
    {
        if (mAllowedTypes == allowedTypes)
            return;

        mAllowedTypes = allowedTypes;

        if (!updateAllowedTypes())
            setModified(true);

        emit allowedTypesChanged(QPrivateSignal{});
    }

    [[nodiscard]] QStringList allowedTypeNames() const
    {
        QStringList result;
        result.reserve(mAllowedTypes.size());
        for (const int t : std::as_const(mAllowedTypes))
            result.append(QMetaType{t}.name());
        return result;
    }
    void setAllowedTypeNames(const QStringList& allowedTypeNames)
    {
        QList<int> allowedTypes;
        allowedTypes.reserve(allowedTypeNames.size());
        for (const auto& t : allowedTypeNames)
            allowedTypes.append(QMetaType::fromName(t.toLocal8Bit()).id());
        setAllowedTypes(allowedTypes);
    }

    [[nodiscard]] int minOccurs() const { return mMinOccurs; }
    void setMinOccurs(int minOccurs)
    {
        if (mMinOccurs == minOccurs)
            return;

        mMinOccurs = minOccurs;

        if (!updateMinOccurs())
            setModified(true);

        emit minOccursChanged(QPrivateSignal{});
    }

    [[nodiscard]] int maxOccurs() const { return mMaxOccurs; }
    void setMaxOccurs(int maxOccurs)
    {
        if (mMaxOccurs == maxOccurs)
            return;

        mMaxOccurs = maxOccurs;

        if (!updateMaxOccurs())
            setModified(true);

        emit maxOccursChanged(QPrivateSignal{});
    }

    [[nodiscard]] ValueTypeListModel* valueTypeListModel();

signals:
    void elementTypesChanged(QPrivateSignal);
    void valueTypesChanged(QPrivateSignal);
    void valueTypesAdded(int first, int last, QPrivateSignal);
    void valueTypesRemoved(int first, int last, QPrivateSignal);
    void allowedTypesChanged(QPrivateSignal);
    void minOccursChanged(QPrivateSignal);
    void maxOccursChanged(QPrivateSignal);

protected:
    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override;
    bool writeJson(QJsonObject& json, QStringList* errors = nullptr) const override;

    bool updateValueTypes();
    bool updateAllowedTypes();
    bool updateMinOccurs();
    bool updateMaxOccurs();

private:
    QList<ElementType*> mElementTypes;
    QList<ValueType*> mValueTypes;
    QMap<QString, ValueType*> mValueTypesByName;
    QList<int> mAllowedTypes;
    ValueTypeListModel* mValueTypeListModel = nullptr;
    int mMinOccurs = 0;
    int mMaxOccurs = 0;

    friend class ElementType;
    friend class FieldTypeStorage;

    Q_PROPERTY(QList<ElementType*> elementTypes READ elementTypes WRITE setElementTypes NOTIFY
                   elementTypesChanged)
    Q_PROPERTY(
        QList<ValueType*> valueTypes READ valueTypes WRITE setValueTypes NOTIFY valueTypesChanged)
    Q_PROPERTY(
        QList<int> allowedTypes READ allowedTypes WRITE setAllowedTypes NOTIFY allowedTypesChanged)
    Q_PROPERTY(QStringList allowedTypeNames READ allowedTypeNames WRITE setAllowedTypeNames NOTIFY
                   allowedTypesChanged)
    Q_PROPERTY(int minOccurs READ minOccurs WRITE setMinOccurs NOTIFY minOccursChanged)
    Q_PROPERTY(int maxOccurs READ maxOccurs WRITE setMaxOccurs NOTIFY maxOccursChanged)
    Q_PROPERTY(ValueTypeListModel* valueTypeListModel READ valueTypeListModel CONSTANT FINAL)
};

#endif // LIBNOVELIST_FIELDTYPE_H
