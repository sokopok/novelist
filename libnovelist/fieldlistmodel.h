#ifndef LIBNOVELIST_FIELDLISTMODEL_H
#define LIBNOVELIST_FIELDLISTMODEL_H

#include <QAbstractListModel>
#include <qqmlintegration.h>

class Element;
class Field;

Q_MOC_INCLUDE("element.h")
Q_MOC_INCLUDE("field.h")

class FieldListModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum Role {
        FieldRole = Qt::UserRole,
        NameRole,
        LabelRole,
        InfoRole,
        IconRole,
        MinOccursRole,
        MaxOccursRole,
        AllowesTypesRole,
        ValuesRole,
        UserRole
    };
    Q_ENUM(Role)

    explicit FieldListModel(QObject *parent = nullptr)
        : QAbstractListModel(parent)
    {}
    explicit FieldListModel(const QList<Field *> &fields, QObject *parent = nullptr)
        : QAbstractListModel(parent)
    {
        setFields(fields);
    }
    explicit FieldListModel(Element *element, QObject *parent = nullptr)
        : QAbstractListModel(parent)
    {
        setElement(element);
    }

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override
    {
        return parent.isValid() ? 0 : mFields.size();
    }

    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roleNames = QAbstractListModel::roleNames();
        roleNames[FieldRole] = "field";
        roleNames[NameRole] = "name";
        roleNames[LabelRole] = "label";
        roleNames[InfoRole] = "info";
        roleNames[IconRole] = "iconSource";
        roleNames[MinOccursRole] = "minOccurs";
        roleNames[MaxOccursRole] = "maxOccurs";
        roleNames[AllowesTypesRole] = "allowesTypes";
        roleNames[ValuesRole] = "values";
        return roleNames;
    }

    [[nodiscard]] QList<Field *> fields() const { return mFields; }
    [[nodiscard]] Q_INVOKABLE Field *field(int index) const { return mFields.value(index); }
    void setFields(const QList<Field *> &fields);

    [[nodiscard]] Element *element() const { return mElement; }
    void setElement(Element *element);

signals:
    void fieldsChanged(QPrivateSignal);
    void elementChanged(QPrivateSignal);

private:
    QList<Field *> mFields;
    Element *mElement = nullptr;

    Q_PROPERTY(QList<Field *> fields READ fields WRITE setFields NOTIFY fieldsChanged FINAL)
    Q_PROPERTY(Element *element READ element WRITE setElement NOTIFY elementChanged FINAL)
};

#endif // LIBNOVELIST_FIELDLISTMODEL_H
