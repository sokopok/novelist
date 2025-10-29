#ifndef LIBNOVELIST_FIELDTYPELISTMODEL_H
#define LIBNOVELIST_FIELDTYPELISTMODEL_H

#include <QAbstractListModel>
#include <qqmlintegration.h>

class ElementType;
class FieldType;

Q_MOC_INCLUDE("elementtype.h")
Q_MOC_INCLUDE("fieldtype.h")

class FieldTypeListModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum Role {
        FieldTypeRole = Qt::UserRole,
        NameRole,
        LabelRole,
        InfoRole,
        IconRole,
        MinOccursRole,
        MaxOccursRole,
        AllowesTypesRole,
        ValueTypesRole,
        UserRole
    };
    Q_ENUM(Role)

    explicit FieldTypeListModel(QObject *parent = nullptr)
        : QAbstractListModel(parent)
    {}
    explicit FieldTypeListModel(const QList<FieldType *> &fieldTypes, QObject *parent = nullptr)
        : QAbstractListModel(parent)
    {
        setFieldTypes(fieldTypes);
    }
    explicit FieldTypeListModel(ElementType *elementType, QObject *parent = nullptr)
        : QAbstractListModel(parent)
    {
        setElementType(elementType);
    }

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override
    {
        return parent.isValid() ? 0 : mFieldTypes.size();
    }

    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roleNames = QAbstractListModel::roleNames();
        roleNames[FieldTypeRole] = "fieldType";
        roleNames[NameRole] = "name";
        roleNames[LabelRole] = "label";
        roleNames[InfoRole] = "info";
        roleNames[IconRole] = "iconSource";
        roleNames[MinOccursRole] = "minOccurs";
        roleNames[MaxOccursRole] = "maxOccurs";
        roleNames[AllowesTypesRole] = "allowesTypes";
        roleNames[ValueTypesRole] = "valueTypes";
        return roleNames;
    }

    [[nodiscard]] QList<FieldType *> fieldTypes() const { return mFieldTypes; }
    [[nodiscard]] Q_INVOKABLE FieldType *fieldType(int index) const
    {
        return mFieldTypes.value(index);
    }
    void setFieldTypes(const QList<FieldType *> &fieldTypes);

    [[nodiscard]] ElementType *elementType() const { return mElementType; }
    void setElementType(ElementType *elementType);

signals:
    void fieldTypesChanged(QPrivateSignal);
    void elementTypeChanged(QPrivateSignal);

private:
    QList<FieldType *> mFieldTypes;
    ElementType *mElementType = nullptr;

    Q_PROPERTY(QList<FieldType *> fieldTypes READ fieldTypes WRITE setFieldTypes NOTIFY
                   fieldTypesChanged FINAL)
    Q_PROPERTY(ElementType *elementType READ elementType WRITE setElementType NOTIFY
                   elementTypeChanged FINAL)
    // Q_PROPERTY(int rowCount READ rowCount NOTIFY fieldTypesChanged FINAL)
};

#endif // LIBNOVELIST_FIELDTYPELISTMODEL_H
