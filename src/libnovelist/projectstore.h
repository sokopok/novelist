#ifndef NOVELIST_PROJECTSTORE_H
#define NOVELIST_PROJECTSTORE_H

#include <QHash>
#include <QMap>
#include <QObject>

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

    Node* load(int type, int id, double version = LastVersion);
    bool reload(Node* node);
    bool save(Node* node);

    Field* loadField(const QString& type, const QString& id, double version = NAN);
    Element* loadElement(const QString& type, const QString& id, double version = NAN);

    // Project* loadProject(const QString& type, const QString& id, double version = NAN);
    bool reloadProject(Project* project) { return false; }
    bool saveProject(Project* project) { return false; }
    // bool saveProjectAs(Project* project, const QString& filename);

    void recycle(Node* node);
    [[nodiscard]] Node* wakeup(int type);
    [[nodiscard]] Node* create(int type);
    [[nodiscard]] Node* wakeupOrCreate(int type)
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
    [[nodiscard]] NodeType* loadType(int type) const;

    bool reloadElement(Element* element);
    bool reloadField(Field* field);
    bool saveElement(Element* element);
    bool saveField(Field* field);

private:
    QString mFilename;
    QHash<int, QList<Node*>> mNodeCache;
    QMap<int, NodeType*> mNodeTypes;
    Project* mProject = nullptr;

    Q_PROPERTY(QString filename READ filename WRITE setFilename NOTIFY filenameChanged FINAL)
    Q_PROPERTY(Project* project READ project WRITE setProject NOTIFY projectChanged FINAL)
};

} // namespace novelist

#endif // NOVELIST_PROJECTSTORE_H
