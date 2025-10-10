#ifndef NOVELIST_PROJECTSTORE_H
#define NOVELIST_PROJECTSTORE_H

#include <QHash>
#include <QMap>
#include <QObject>

class QSqlRecord;

namespace novelist {

class Node;
class Element;
class Field;
class Project;
class NodeType;

class ProjectStore : public QObject
{
    Q_OBJECT

public:
    constexpr static double LastVersion = std::numeric_limits<double>::infinity();

    ProjectStore(QObject* parent = nullptr);

    [[nodiscard]] QString filename() const { return mFilename; }
    void setFilename(const QString& filename)
    {
        if (mFilename == filename)
            return;
        mFilename = filename;
        emit filenameChanged();
    }

    Node* load(const QString& type, int rowid, double version = LastVersion);
    bool reload(Node* node);
    bool save(Node* node);
    bool refresh(Node* node, const QSqlRecord& record);

    Field* loadField(const QString& type, const QString& id, double version = NAN);
    Element* loadElement(const QString& type, const QString& id, double version = NAN);

    // Project* loadProject(const QString& type, const QString& id, double version = NAN);
    bool reloadProject(Project* project) { return false; }
    bool saveProject(Project* project) { return false; }
    // bool saveProjectAs(Project* project, const QString& filename);

    void recycle(Node* node);
    [[nodiscard]] Node* wakeup(const QString& type);
    [[nodiscard]] Node* create(const QString& type);
    [[nodiscard]] Node* wakeupOrCreate(const QString& type)
    {
        if (Node* node = wakeup(type))
            return node;
        return create(type);
    }

    [[nodiscard]] Project* project() const { return mProject; }
    void setProject(Project* project);

signals:
    void filenameChanged();
    void projectChanged();

protected:
    [[nodiscard]] NodeType* loadType(const QString& type) const;

    bool refreshElement(Element* element, const QSqlRecord& record);
    bool refreshField(Field* field, const QSqlRecord& record);

    bool reloadElement(Element* element);
    bool reloadField(Field* field);
    bool saveElement(Element* element);
    bool saveField(Field* field);

    bool createDatabase(const QString& databaseName);

private:
    QString mFilename;
    QHash<QString, QList<Node*>> mNodeCache;
    QMap<QString, NodeType*> mNodeTypes;
    Project* mProject = nullptr;

    Q_PROPERTY(QString filename READ filename WRITE setFilename NOTIFY filenameChanged FINAL)
    Q_PROPERTY(Project* project READ project WRITE setProject NOTIFY projectChanged FINAL)
};

} // namespace novelist

#endif // NOVELIST_PROJECTSTORE_H
