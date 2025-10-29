#ifndef LIBNOVELIST_ELEMENTTYPELISTMODEL_H
#define LIBNOVELIST_ELEMENTTYPELISTMODEL_H

#include <QAbstractListModel>
#include <qqmlintegration.h>

class ElementType;

Q_MOC_INCLUDE("elementtype.h")

class ElementTypeListModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum Role {
        ElementTypeRole = Qt::UserRole,
        NameRole,
        LabelRole,
        InfoRole,
        IconRole,
        MinOccursRole,
        MaxOccursRole,
        AllowesTypesRole,
        FieldTypesRole,
        UserRole
    };
    Q_ENUM(Role)

    explicit ElementTypeListModel(QObject *parent = nullptr)
        : QAbstractListModel(parent)
    {}
    explicit ElementTypeListModel(const QList<ElementType *> &elementTypes,
                                  QObject *parent = nullptr)
        : QAbstractListModel(parent)
    {
        setElementTypes(elementTypes);
    }

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override
    {
        return parent.isValid() ? 0 : mElementTypes.size();
    }

    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roleNames = QAbstractListModel::roleNames();
        roleNames[ElementTypeRole] = "elementType";
        roleNames[NameRole] = "name";
        roleNames[LabelRole] = "label";
        roleNames[InfoRole] = "info";
        roleNames[IconRole] = "iconSource";
        roleNames[FieldTypesRole] = "fieldTypes";
        return roleNames;
    }

    [[nodiscard]] QList<ElementType *> elementTypes() const { return mElementTypes; }
    [[nodiscard]] Q_INVOKABLE ElementType *elementType(int index) const
    {
        return mElementTypes.value(index);
    }
    void setElementTypes(const QList<ElementType *> &elementTypes);

signals:
    void elementTypesChanged(QPrivateSignal);

private:
    QList<ElementType *> mElementTypes;

    Q_PROPERTY(QList<ElementType *> elementTypes READ elementTypes WRITE setElementTypes NOTIFY
                   elementTypesChanged FINAL)
};

#endif // LIBNOVELIST_ELEMENTTYPELISTMODEL_H
