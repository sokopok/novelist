#ifndef LIBNOVELIST_NOVELIST_H
#define LIBNOVELIST_NOVELIST_H

#include <QObject>
#include <QQmlEngine>

class Project;
class Storage;

Q_MOC_INCLUDE("project.h")

class Novelist : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    Novelist(QObject *parent = nullptr)
        : QObject{parent}
    {}

    [[nodiscard]] Project *project() const { return mProject; }
    void setProject(Project *project);

    [[nodiscard]] Storage *storage() const { return mStorage; }
    void setStorage(Storage *storage);

signals:
    void projectChanged();
    void storageChanged();

private:
    Project *mProject = nullptr;
    Storage *mStorage = nullptr;

    Q_PROPERTY(Project *project READ project WRITE setProject NOTIFY projectChanged FINAL)
};

#endif // LIBNOVELIST_NOVELIST_H
