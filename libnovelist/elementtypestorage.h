#ifndef LIBNOVELIST_ELEMENTTYPESTORAGE_H
#define LIBNOVELIST_ELEMENTTYPESTORAGE_H

#include "elementtype.h"
#include "nodetypestorage.h"

class ElementTypeStorage : public BaseTypeStorage
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit ElementTypeStorage(Storage* parent = nullptr)
        : BaseTypeStorage{parent}
    {}

    void setDatabase(const QSqlDatabase& database) override;

    [[nodiscard]] Q_INVOKABLE ElementType* elementType()
    {
        return static_cast<ElementType*>(node());
    }
    [[nodiscard]] Q_INVOKABLE ElementType* elementType(int rowid)
    {
        return static_cast<ElementType*>(node(rowid));
    }
    [[nodiscard]] Q_INVOKABLE ElementType* elementType(const QString& name)
    {
        return static_cast<ElementType*>(nodeType(name));
    }
    [[nodiscard]] Q_INVOKABLE ElementType* createElementType(const QString& name,
                                                             const QString& label = {},
                                                             const QString& info = {},
                                                             const QString& icon = {})
    {
        if (name.isEmpty())
            return handleError(this, "removeNode", "name is empty"), nullptr;

        if (mNodesByName.contains(name))
            return handleError(
                       this,
                       "removeNode",
                       QStringLiteral("storage already contains a type with name '%1'").arg(name)),
                   nullptr;

        if (ElementType* elementType = static_cast<ElementType*>(createNode())) {
            mNodesByName.insert(name, elementType);
            elementType->setName(name);
            elementType->setLabel(label);
            elementType->setInfo(info);
            elementType->setIcon(icon);
            return elementType;
        }

        return nullptr;
    }

    QList<ElementType*> allElementTypes() const { return toDerived<ElementType>(mNodes); }

protected:
    [[nodiscard]] Node* createNode() override;
    bool insertNode(Node* node) override;
    bool updateNode(Node* node) override;
    bool reloadNode(Node* node) override;
    bool removeNode(int rowid) override;

    bool updateFieldTypes(ElementType* elementType);

    friend class ElementType;
    friend class Storage;
    friend class ProjectTypeStorage;

    QSqlQuery mReloadQuery;
    QSqlQuery mInsertQuery;
    QSqlQuery mUpdateQuery;
    QSqlQuery mReloadFieldTypesQuery;
    QSqlQuery mInsertFieldTypesQuery;
    QSqlQuery mUpdateFieldTypesQuery;
    QSqlQuery mRemoveFieldTypesQuery;
};

#endif // LIBNOVELIST_ELEMENTTYPESTORAGE_H
