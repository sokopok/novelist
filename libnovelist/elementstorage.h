#ifndef LIBNOVELIST_ELEMENTSTORAGE_H
#define LIBNOVELIST_ELEMENTSTORAGE_H

#include "basestorage.h"
#include "element.h"
#include "elementtype.h"
#include "field.h"

class ElementStorage : public BaseStorage
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit ElementStorage(Storage* parent = nullptr)
        : BaseStorage{parent}
    {}

    void setDatabase(const QSqlDatabase& database) override;

    [[nodiscard]] Q_INVOKABLE Element* element() { return static_cast<Element*>(node()); }
    [[nodiscard]] Q_INVOKABLE Element* element(int rowid)
    {
        return static_cast<Element*>(node(rowid));
    }
    [[nodiscard]] Q_INVOKABLE Element* createElement(ElementType* nodeType = nullptr,
                                                     const QString& label = {},
                                                     const QString& info = {},
                                                     const QString& icon = {})
    {
        if (Element* e = static_cast<Element*>(createNode())) {
            e->setNodeType(nodeType);
            e->setLabel(label);
            e->setInfo(info);
            e->setIcon(icon);
            return e;
        }
        return nullptr;
    }

protected:
    [[nodiscard]] Node* createNode() override;
    bool insertNode(Node* node) override;
    bool updateNode(Node* node) override;
    bool reloadNode(Node* node) override;
    bool removeNode(int rowid) override;

    bool updateFields(Element* element);

    friend class Element;
    friend class Storage;
    friend class ProjectStorage;

    QSqlQuery mReloadQuery;
    QSqlQuery mInsertQuery;
    QSqlQuery mUpdateQuery;
    QSqlQuery mReloadFieldsQuery;
    QSqlQuery mInsertFieldsQuery;
    QSqlQuery mRemoveFieldsQuery;
};

#endif // LIBNOVELIST_ELEMENTSTORAGE_H
