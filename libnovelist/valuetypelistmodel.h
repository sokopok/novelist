#ifndef LIBNOVELIST_VALUETYPELISTMODE_H
#define LIBNOVELIST_VALUETYPELISTMODE_H

#include <QAbstractListModel>
#include <qqmlintegration.h>

class FieldType;
class ValueType;

Q_MOC_INCLUDE("fieldtype.h")
Q_MOC_INCLUDE("valuetype.h")

class ValueTypeListModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum Role { ValueTypeRole = Qt::UserRole, NameRole, LabelRole, InfoRole, IconRole, UserRole };
    Q_ENUM(Role)

    explicit ValueTypeListModel(QObject *parent = nullptr)
        : QAbstractListModel(parent)
    {}
    explicit ValueTypeListModel(const QList<ValueType *> &valueTypes, QObject *parent = nullptr)
        : QAbstractListModel(parent)
    {
        setValueTypes(valueTypes);
    }
    explicit ValueTypeListModel(FieldType *fieldType, QObject *parent = nullptr)
        : QAbstractListModel(parent)
    {
        setFieldType(fieldType);
    }

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override
    {
        return parent.isValid() ? 0 : mValueTypes.size();
    }

    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roleNames = QAbstractListModel::roleNames();
        roleNames[ValueTypeRole] = "valueType";
        roleNames[NameRole] = "name";
        roleNames[LabelRole] = "label";
        roleNames[InfoRole] = "info";
        roleNames[IconRole] = "iconSource";
        return roleNames;
    }

    [[nodiscard]] QList<ValueType *> valueTypes() const { return mValueTypes; }
    [[nodiscard]] Q_INVOKABLE ValueType *valueType(int index) const
    {
        return mValueTypes.value(index);
    }
    void setValueTypes(const QList<ValueType *> &valueTypes);

    [[nodiscard]] FieldType *fieldType() const { return mFieldType; }
    void setFieldType(FieldType *fieldType);

signals:
    void valueTypesChanged(QPrivateSignal);
    void fieldTypeChanged(QPrivateSignal);

private:
    QList<ValueType *> mValueTypes;
    FieldType *mFieldType = nullptr;

    Q_PROPERTY(QList<ValueType *> valueTypes READ valueTypes WRITE setValueTypes NOTIFY
                   valueTypesChanged FINAL)
    Q_PROPERTY(FieldType *fieldType READ fieldType WRITE setFieldType NOTIFY fieldTypeChanged FINAL)
};

#endif // LIBNOVELIST_VALUETYPELISTMODE_H
