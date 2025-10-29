#ifndef LIBNOVELIST_PROJECTSTORAGE_H
#define LIBNOVELIST_PROJECTSTORAGE_H

#include "elementstorage.h"
#include "project.h"

class ProjectStorage : public BaseStorage
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit ProjectStorage(Storage* parent = nullptr)
        : BaseStorage{parent}
    {}

    void setDatabase(const QSqlDatabase& database) override;

    [[nodiscard]] Q_INVOKABLE Project* project() { return static_cast<Project*>(node()); }
    [[nodiscard]] Q_INVOKABLE Project* project(int rowid)
    {
        return static_cast<Project*>(node(rowid));
    }
    [[nodiscard]] Q_INVOKABLE Project* createProject(const QString& type);
    [[nodiscard]] Q_INVOKABLE Project* createProject(ProjectType* nodeType = nullptr)
    {
        if (Project* e = static_cast<Project*>(createNode())) {
            e->setNodeType(nodeType);
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

    friend class Project;
    friend class Storage;

    QSqlQuery mReloadQuery;
    QSqlQuery mInsertQuery;
    QSqlQuery mUpdateQuery;
};

#endif // LIBNOVELIST_PROJECTSTORAGE_H
