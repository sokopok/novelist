#ifndef LIBNOVELIST_VALUE_H
#define LIBNOVELIST_VALUE_H

#include <QVariant>
#include "node.h"
#include "valuetype.h"

class Field;

class Value : public Node
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("")

public:
    enum Type {
        Type_Unknown,
        Type_String,
        Type_Int,
        Type_Float,
        Type_Double,
        Type_Bool,
        Type_Date,
        Type_Time,
        Type_DateTime,
        Type_Node,
        Type_NodeList
    };
    Q_ENUM(Type)

    static int typeIdToType(int typeId) { return mTypeIdToType.value(typeId, Type_Unknown); }
    static int typeToTypeId(int type)
    {
        switch (type) {
        default:
        case Type_String:
            return qMetaTypeId<QString>();
        case Type_Int:
            return qMetaTypeId<int>();
        case Type_Float:
            return qMetaTypeId<float>();
        case Type_Double:
            return qMetaTypeId<double>();
        case Type_Bool:
            return qMetaTypeId<bool>();
        case Type_Date:
            return qMetaTypeId<QDate>();
        case Type_Time:
            return qMetaTypeId<QTime>();
        case Type_DateTime:
            return qMetaTypeId<QDateTime>();
        case Type_Node:
            return qMetaTypeId<Node *>();
        case Type_NodeList:
            return qMetaTypeId<NodeList>();
        }
    }
    static QString typeToString(int type) { return mTypeToString.value(type, "Unknown"); }
    static int stringToType(const QString &type) { return mTypeToString.key(type, Type_Unknown); }

    explicit Value(Storage *storage, QObject *parent = nullptr)
        : Value{Type_Value, storage, parent}
    {}
    Value(int type, Storage *storage, QObject *parent = nullptr)
        : Value{nullptr, type, storage, parent}
    {}
    Value(ValueType *valueType, Storage *storage, QObject *parent = nullptr)
        : Value{valueType, Type_Value, storage, parent}
    {}
    Value(ValueType *valueType, int type, Storage *storage, QObject *parent = nullptr)
        : Node{valueType, type, storage, parent}
    {}

    bool reload() override;
    bool save(bool newVersion = true) override;
    bool recycle() override;

    [[nodiscard]] QList<Field *> fields() const { return mFields; }
    void setFields(const QList<Field *> &fields)
    {
        if (mFields == fields)
            return;
        mFields = fields;
        // setModified(true);
        emit fieldsChanged(QPrivateSignal{});
    }

    bool addField(Field *field)
    {
        if (!field)
            return false;
        if (mFields.contains(field))
            return true;
        mFields.append(field);
        // setModified(true);
        emit fieldsChanged(QPrivateSignal{});
        return true;
    }
    bool removeField(Field *field)
    {
        if (!field)
            return false;
        if (!mFields.removeOne(field))
            return false;
        // setModified(true);
        emit fieldsChanged(QPrivateSignal{});
        return true;
    }

    [[nodiscard]] QVariant value() const { return mValue; }
    void setValue(const QVariant &value);

    [[nodiscard]] int valueType() const { return mValueType; }
    void setValueType(int valueType)
    {
        if (mValueType == valueType)
            return;

        mValueType = valueType;

        if (!updateValueType())
            setModified(true);

        emit valueTypeChanged(QPrivateSignal{});
    }

    [[nodiscard]] Q_INVOKABLE int indexIn(Field *field) const;

signals:
    void fieldsChanged(QPrivateSignal);
    void valueChanged(QPrivateSignal);
    void valueTypeChanged(QPrivateSignal);

protected:
    bool readJson(const QJsonObject &json, QStringList *errors = nullptr) override;
    bool writeJson(QJsonObject &json, QStringList *errors = nullptr) const override;

    bool updateValue();
    bool updateValueType();

private:
    QList<Field *> mFields;
    QVariant mValue;
    int mValueType = 0;

    inline static const QMap<int, int> mTypeIdToType = {{qMetaTypeId<QString>(), Type_String},
                                                        {qMetaTypeId<int>(), Type_Int},
                                                        {qMetaTypeId<double>(), Type_Double},
                                                        {qMetaTypeId<float>(), Type_Float},
                                                        {qMetaTypeId<bool>(), Type_Bool},
                                                        {qMetaTypeId<QDate>(), Type_Date},
                                                        {qMetaTypeId<QTime>(), Type_Time},
                                                        {qMetaTypeId<QDateTime>(), Type_DateTime},
                                                        {qMetaTypeId<Node *>(), Type_Node},
                                                        {qMetaTypeId<NodeList>(), Type_NodeList}};
    inline static const QMap<int, QString> mTypeToString = {{Type_String, "String"},
                                                            {Type_Int, "Int"},
                                                            {Type_Double, "Double"},
                                                            {Type_Float, "Float"},
                                                            {Type_Bool, "Bool"},
                                                            {Type_Date, "Date"},
                                                            {Type_Time, "Time"},
                                                            {Type_DateTime, "DateTime"},
                                                            {Type_Node, "Node"},
                                                            {Type_NodeList, "NodeList"}};

    friend class Field;

    Q_PROPERTY(QList<Field *> fields READ fields WRITE setFields NOTIFY fieldsChanged FINAL)
    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged FINAL)
    Q_PROPERTY(int valueType READ valueType WRITE setValueType NOTIFY valueTypeChanged FINAL)
};

#endif // LIBNOVELIST_VALUE_H
