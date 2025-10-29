#ifndef LIBNOVELIST_VALUELISTMODEL_H
#define LIBNOVELIST_VALUELISTMODEL_H

#include <QAbstractListModel>

#include "field.h"
#include "value.h"

class ValueListModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum Role {
        ValueRole = Qt::UserRole,
        NameRole,
        LabelRole,
        InfoRole,
        IconRole,
        ValueTypeRole,
        ValueValueRole,
        UserRole
    };
    Q_ENUM(Role)

    explicit ValueListModel(QObject *parent = nullptr)
        : QAbstractListModel(parent)
    {}
    explicit ValueListModel(const QList<Value *> &values, QObject *parent = nullptr)
        : QAbstractListModel(parent)
    {
        setValues(values);
    }
    explicit ValueListModel(Field *field, QObject *parent = nullptr)
        : QAbstractListModel(parent)
    {
        setField(field);
    }

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override
    {
        return parent.isValid() ? 0 : mValues.size();
    }

    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
    {
        if (Value *value = mValues.value(index.row())) {
            switch (role) {
            case ValueRole:
            case Qt::EditRole:
                return QVariant::fromValue(value);
            case NameRole:
                return value->name();
            case LabelRole:
            case Qt::DisplayRole:
                return value->label();
            case InfoRole:
                return value->info();
            case IconRole:
                return value->icon();
            case ValueTypeRole:
                return value->valueType();
            case ValueValueRole:
                return value->value();
            }
        }
        return {};
    }

    QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roleNames = QAbstractListModel::roleNames();
        roleNames[ValueRole] = "value";
        roleNames[NameRole] = "name";
        roleNames[LabelRole] = "label";
        roleNames[InfoRole] = "info";
        roleNames[IconRole] = "iconSource";
        roleNames[ValueTypeRole] = "valueType";
        roleNames[ValueValueRole] = "valueValue";
        return roleNames;
    }

    [[nodiscard]] QList<Value *> values() const { return mValues; }
    [[nodiscard]] Q_INVOKABLE Value *value(int index) const { return mValues.value(index); }
    void setValues(const QList<Value *> &values)
    {
        if (mValues == values)
            return;
        beginResetModel();
        for (Value *value : std::as_const(mValues))
            value->disconnect(this);
        mValues = values;
        for (Value *value : std::as_const(mValues)) {
            connect(value, &Node::nameChanged, this, [this, value]() {
                const auto idx = index(mValues.indexOf(value), 0);
                emit dataChanged(idx, idx, {NameRole});
            });
            connect(value, &Node::labelChanged, this, [this, value]() {
                const auto idx = index(mValues.indexOf(value), 0);
                emit dataChanged(idx, idx, {LabelRole});
            });
            connect(value, &Node::infoChanged, this, [this, value]() {
                const auto idx = index(mValues.indexOf(value), 0);
                emit dataChanged(idx, idx, {InfoRole});
            });
            connect(value, &Node::iconChanged, this, [this, value]() {
                const auto idx = index(mValues.indexOf(value), 0);
                emit dataChanged(idx, idx, {IconRole});
            });
            connect(value, &Value::valueTypeChanged, this, [this, value]() {
                const auto idx = index(mValues.indexOf(value), 0);
                emit dataChanged(idx, idx, {ValueTypeRole});
            });
            connect(value, &Value::valueChanged, this, [this, value]() {
                const auto idx = index(mValues.indexOf(value), 0);
                emit dataChanged(idx, idx, {ValueValueRole});
            });
        }
        endResetModel();
        emit valuesChanged(QPrivateSignal{});
    }

    [[nodiscard]] Field *field() const { return mField; }
    void setField(Field *field)
    {
        if (mField == field)
            return;
        if (mField)
            mField->disconnect(this);
        mField = field;
        if (mField) {
            setValues(field->values());
            connect(mField, &Field::valuesChanged, this, [this]() { setValues(mField->values()); });
        } else
            setValues({});
        emit fieldChanged(QPrivateSignal{});
    }

signals:
    void valuesChanged(QPrivateSignal);
    void fieldChanged(QPrivateSignal);

private:
    QList<Value *> mValues;
    Field *mField = nullptr;

    Q_PROPERTY(QList<Value *> values READ values WRITE setValues NOTIFY valuesChanged FINAL)
    Q_PROPERTY(Field *field READ field WRITE setField NOTIFY fieldChanged FINAL)
};

#endif // LIBNOVELIST_VALUELISTMODEL_H
