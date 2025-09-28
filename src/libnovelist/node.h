#ifndef NOVELIST_NODE_H
#define NOVELIST_NODE_H

#include <QObject>
#include <QVariantMap>
#include "interfaces.h"
#include "logging.h"

namespace novelist {

class Project;

class Node : public QObject, public Storable, public Throwable
{
    Q_OBJECT

public:
    Q_ENUM(Error)

    Node(QObject* parent = nullptr)
        : QObject{parent}
    {}

    bool reload() override;
    bool save() override;

    // [[nodiscard]] static Node* load(const QString& id);

    [[nodiscard]] quint64 rowid() const override { return mRowid; }

    void recycle() override;

    [[nodiscard]] virtual Project* project() const;
    [[nodiscard]] ProjectStore* projectStore() const override;

    [[nodiscard]] bool isModified() const { return mModified; }

    [[nodiscard]] int type() const { return mType; }
    void setType(int type)
    {
        if (mType == type)
            return;
        mType = type;
        emit typeChanged();
    }

    [[nodiscard]] int id() const { return mId; }
    void setId(int id)
    {
        if (mId == id)
            return;
        mId = id;
        emit idChanged();
    }

signals:
    void loaded();
    void saved();

    void rowidChanged();

    void error(int error, const QString& message, const QString& file, int line);
    void warning(int error, const QString& message, const QString& file, int line);

    void modifiedChanged();

    void typeChanged();
    void idChanged();

protected:
    void setRowid(quint64 rowid) override
    {
        if (mRowid == rowid)
            return;
        mRowid = rowid;
        emit rowidChanged();
    }

    using Throwable::throwError;
    void throwError(int e, QString message, const char* file = 0, const int line = 0) override
    {
        emit error(e, message, file, line);
    }

    using Throwable::throwWarning;
    void throwWarning(int w,
                      QString message,
                      QVariantMap arguments,
                      const char* file = 0,
                      const int line = 0) override
    {
        while (!arguments.isEmpty()) {
            message = message.arg(arguments.firstKey() + ':' + arguments.first().toString());
            arguments.erase(arguments.begin());
        }
        emit warning(w, message, file, line);
    }

    void setModified(bool modified)
    {
        if (mModified == modified)
            return;
        mModified = modified;
        emit modifiedChanged();
    }

private:
    quint64 mRowid = 0;
    bool mModified = false;
    int mType = 0;
    int mId = 0;

    Q_PROPERTY(bool modified READ isModified NOTIFY modifiedChanged FINAL)
    Q_PROPERTY(quint64 rowid READ rowid NOTIFY rowidChanged FINAL)
    Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged FINAL)
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged FINAL)
};

} // namespace novelist

#endif // NOVELIST_NODE_H
