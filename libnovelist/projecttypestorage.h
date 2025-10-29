#ifndef LIBNOVELIST_PROJECTTYPESTORAGE_H
#define LIBNOVELIST_PROJECTTYPESTORAGE_H

#include "elementtypestorage.h"
#include "projecttype.h"

class ProjectTypeStorage : public BaseTypeStorage
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit ProjectTypeStorage(Storage* parent = nullptr)
        : BaseTypeStorage{parent}
    {}

    void setDatabase(const QSqlDatabase& database) override;

    [[nodiscard]] Q_INVOKABLE ProjectType* projectType()
    {
        return static_cast<ProjectType*>(node());
    }
    [[nodiscard]] Q_INVOKABLE ProjectType* projectType(int rowid)
    {
        return static_cast<ProjectType*>(node(rowid));
    }
    [[nodiscard]] Q_INVOKABLE ProjectType* projectType(const QString& name)
    {
        return static_cast<ProjectType*>(nodeType(name));
    }
    [[nodiscard]] Q_INVOKABLE ProjectType* createProjectType(const QString& name,
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

        if (ProjectType* projectType = static_cast<ProjectType*>(createNode())) {
            mNodesByName.insert(name, projectType);
            projectType->setName(name);
            projectType->setLabel(label);
            projectType->setInfo(info);
            projectType->setIcon(icon);
            return projectType;
        }

        return nullptr;
    }

    QList<ProjectType*> allProjectTypes() const { return toDerived<ProjectType>(mNodes); }

protected:
    [[nodiscard]] Node* createNode() override;
    bool insertNode(Node* node) override;
    bool updateNode(Node* node) override;
    bool reloadNode(Node* node) override;
    bool removeNode(int rowid) override;

    friend class ProjectType;
    friend class Storage;

    QSqlQuery mReloadQuery;
    QSqlQuery mInsertQuery;
    QSqlQuery mUpdateQuery;
};

#endif // LIBNOVELIST_PROJECTTYPESTORAGE_H
