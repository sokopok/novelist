#ifndef NOVELIST_PROJECTSTORE_H
#define NOVELIST_PROJECTSTORE_H

#include <QHash>
#include <QObject>

namespace novelist {

class Node;
class Element;
class Field;
class Project;

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

    Project* loadProject(const QString& type, const QString& id, double version = NAN);
    bool reloadProject(Project* project);
    bool saveProject(Project* project);
    bool saveProjectAs(Project* project, const QString& filename);

    void recycle(Node* node);

signals:
    void filenameChanged();

protected:
    [[nodiscard]] bool loadType(int type) const;

    [[nodiscard]] Node* wakeupOrCreate(int type)
    {
        if (mNodeCache.contains(type)) {
            QList<Node*>& nodes = mNodeCache[type];
            if (!nodes.isEmpty()) {
                return nodes.takeLast();
            }
        }

        QMetaType metaType{type};
        Node* node = static_cast<Node*>(metaType.create());
        return node;
    }

private:
    QString mFilename;
    QHash<int, QList<Node*>> mNodeCache;

    Q_PROPERTY(QString filename READ filename WRITE setFilename NOTIFY filenameChanged FINAL)
};

} // namespace novelist

#endif // NOVELIST_PROJECTSTORE_H
