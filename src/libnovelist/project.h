#ifndef NOVELIST_PROJECT_H
#define NOVELIST_PROJECT_H

#include <QObject>
#include "node.h"
#include "projectstore.h"

namespace novelist {

class Project : public Node
{
    Q_OBJECT

public:
    Project(QObject* parent = nullptr);

    [[nodiscard]] static ProjectStore* staticProjectStore() { return mProjectStore; }
    static void setStaticProjectStore(ProjectStore* projectStore)
    {
        if (mProjectStore == projectStore)
            return;
        mProjectStore = projectStore;
    }
    static void resetStaticProjectStore();

    [[nodiscard]] QString filename() const { return mFilename; }
    void setFilename(const QString& filename)
    {
        if (mFilename == filename)
            return;
        mFilename = filename;
        emit filenameChanged();
    }

    bool reload() override;
    bool save() override;
    bool saveAs(const QString& filename);

    static Project* load(const QString& filename);

    [[nodiscard]] Project* project() const override { return mSelf; }
    [[nodiscard]] ProjectStore* projectStore() const override { return staticProjectStore(); }

signals:
    void projectStoreChanged();
    void filenameChanged();

private:
    inline static ProjectStore* mProjectStore = nullptr;
    QString mFilename;
    Project* mSelf = nullptr;

    Q_PROPERTY(QString filename READ filename WRITE setFilename NOTIFY filenameChanged FINAL)
};

} // namespace novelist

#endif // NOVELIST_PROJECT_H
