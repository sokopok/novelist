#ifndef LIBNOVELIST_FIELD_H
#define LIBNOVELIST_FIELD_H

#include "fieldtype.h"
#include "node.h"

class Element;
class Value;
class ValueListModel;

Q_MOC_INCLUDE("element.h")
Q_MOC_INCLUDE("value.h")
Q_MOC_INCLUDE("valuelistmodel.h")

template<typename T, typename D>
class StorageImpl;

class Field : public Node
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("")

public:
    explicit Field(Storage *storage, QObject *parent = nullptr)
        : Field{Type_Field, storage, parent}
    {}
    Field(int type, Storage *storage, QObject *parent = nullptr)
        : Field{nullptr, type, storage, parent}
    {}
    Field(FieldType *fieldType, Storage *storage, QObject *parent = nullptr)
        : Field{fieldType, Type_Field, storage, parent}
    {}
    Field(FieldType *fieldType, int type, Storage *storage, QObject *parent = nullptr)
        : Node{fieldType, type, storage, parent}
    {}

    FieldType *fieldType() const { return static_cast<FieldType *>(nodeType()); }

    bool reload() override;
    bool save(bool newVersion = true) override;
    bool recycle() override;

    [[nodiscard]] QList<Element*> elements() const { return mElements; }
    void setElements(const QList<Element*>& elements)
    {
        if (mElements == elements)
            return;
        mElements = elements;
        setModified(true);
        emit elementsChanged(QPrivateSignal{});
    }

    bool addElement(Element* element)
    {
        if (!element)
            return handleError(this, "addElement", "element is null"), false;

        if (mElements.contains(element))
            return handleError(this, "addElement", "field already contains element"), true;

        mElements.append(element);

        emit elementsChanged(QPrivateSignal{});
        return true;
    }
    bool removeElement(Element* element)
    {
        if (!element)
            return handleError(this, "removeElement", "element is null"), false;

        if (!mElements.removeOne(element))
            return handleError(this, "removeElement", "element not found"), false;

        emit elementsChanged(QPrivateSignal{});
        return true;
    }

    [[nodiscard]] QList<Value*> values() const { return mValues; }
    void setValues(const QList<Value *> &values);

    [[nodiscard]] Value* value(int index) const { return mValues.value(index); }
    bool insertValue(int index, Value* value);
    bool appendValue(Value *value) { return insertValue(mValues.size(), value); }
    bool appendValue(int type, const QVariant &value);
    bool appendValue(const QString &type, const QVariant &value);
    bool prependValue(Value *value) { return insertValue(0, value); }
    bool removeValue(Value* value)
    {
        if (!value)
            return false;
        int index = mValues.indexOf(value);
        while (index >= 0) {
            if (!removeValueAt(index))
                return false;
            index = mValues.indexOf(value, index);
        }
        return true;
    }
    bool removeValueAt(int index);
    Value* takeValueAt(int index)
    {
        if (index < 0 || index >= mValues.size())
            return nullptr;
        Value* value = mValues[index];
        if (!removeValueAt(index))
            return nullptr;
        return value;
    }

    [[nodiscard]] QList<int> allowedTypes() const
    {
        return mAllowedTypes.isEmpty() ? fieldType()->allowedTypes() : mAllowedTypes;
    }
    void setAllowedTypes(const QList<int> &allowedTypes)
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
        const auto allowedTypes = mAllowedTypes.isEmpty() ? fieldType()->allowedTypes()
                                                          : mAllowedTypes;
        QStringList result;
        result.reserve(allowedTypes.size());
        for (const int t : allowedTypes)
            result.append(QMetaType{t}.name());
        return result;
    }
    void setAllowedTypeNames(const QStringList &allowedTypeNames)
    {
        QList<int> allowedTypes;
        allowedTypes.reserve(allowedTypeNames.size());
        for (const auto &t : allowedTypeNames)
            allowedTypes.append(QMetaType::fromName(t.toLocal8Bit()).id());
        setAllowedTypes(allowedTypes);
    }

    [[nodiscard]] int minOccurs() const
    {
        return mMinOccurs < 0 ? fieldType()->minOccurs() : mMinOccurs;
    }
    void setMinOccurs(int minOccurs)
    {
        if (mMinOccurs == minOccurs)
            return;

        mMinOccurs = minOccurs;

        if (!updateMinOccurs())
            setModified(true);

        emit minOccursChanged(QPrivateSignal{});
    }

    [[nodiscard]] int maxOccurs() const
    {
        return mMaxOccurs < 0 ? fieldType()->maxOccurs() : mMaxOccurs;
    }
    void setMaxOccurs(int maxOccurs)
    {
        if (mMaxOccurs == maxOccurs)
            return;

        mMaxOccurs = maxOccurs;

        if (!updateMaxOccurs())
            setModified(true);

        emit maxOccursChanged(QPrivateSignal{});
    }

    [[nodiscard]] Q_INVOKABLE int indexIn(Element *element) const;

    [[nodiscard]] ValueListModel *valueListModel();

signals:
    void elementsChanged(QPrivateSignal);
    void valuesChanged(QPrivateSignal);
    void valuesAdded(int first, int last, QPrivateSignal);
    void valuesRemoved(int first, int last, QPrivateSignal);
    void allowedTypesChanged(QPrivateSignal);
    void minOccursChanged(QPrivateSignal);
    void maxOccursChanged(QPrivateSignal);

protected:
    bool readJson(const QJsonObject &json, QStringList *errors = nullptr) override;
    bool writeJson(QJsonObject &json, QStringList *errors = nullptr) const override;

    bool updateValues();
    bool updateAllowedTypes();
    bool updateMinOccurs();
    bool updateMaxOccurs();

private:
    QList<Element*> mElements;
    QList<Value*> mValues;
    QList<int> mAllowedTypes;
    ValueListModel *mValueListModel = nullptr;
    int mMinOccurs = -1;
    int mMaxOccurs = -1;

    friend class Element;
    friend class FieldStorage;
    friend StorageImpl<Field, Storage>;

    Q_PROPERTY(QList<Element *> elements READ elements WRITE setElements NOTIFY elementsChanged FINAL)
    Q_PROPERTY(QList<Value*> values READ values WRITE setValues NOTIFY valuesChanged FINAL)
    Q_PROPERTY(QList<int> allowedTypes READ allowedTypes WRITE setAllowedTypes NOTIFY
                   allowedTypesChanged FINAL)
    Q_PROPERTY(QStringList allowedTypeNames READ allowedTypeNames WRITE setAllowedTypeNames NOTIFY
                   allowedTypesChanged FINAL)
    Q_PROPERTY(int minOccurs READ minOccurs WRITE setMinOccurs NOTIFY minOccursChanged FINAL)
    Q_PROPERTY(int maxOccurs READ maxOccurs WRITE setMaxOccurs NOTIFY maxOccursChanged FINAL)
    Q_PROPERTY(ValueListModel *valueListModel READ valueListModel CONSTANT FINAL)
};

#endif // LIBNOVELIST_FIELD_H
