#ifndef LIBNOVELIST_ELEMENTTYPETREEMODEL_H
#define LIBNOVELIST_ELEMENTTYPETREEMODEL_H

#include <QObject>
#include <QQmlEngine>
#include <QStandardItemModel>

class ElementType;

class ElementTypeTreeModel : public QStandardItemModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    ElementTypeTreeModel(QObject *parent = nullptr)
        : QStandardItemModel{parent}
    {}

    [[nodiscard]] QList<ElementType *> elementTypes() const { return mElementTypes; }
    void setElementTypes(const QList<ElementType *> &elementTypes);

signals:
    void elementTypesChanged();

private:
    QList<ElementType *> mElementTypes;

    Q_PROPERTY(QList<ElementType *> elementTypes READ elementTypes WRITE setElementTypes NOTIFY
                   elementTypesChanged FINAL)
};

#endif // LIBNOVELIST_ELEMENTTYPETREEMODEL_H
