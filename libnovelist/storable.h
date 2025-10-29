#ifndef LIBNOVELIST_STORABLE_H
#define LIBNOVELIST_STORABLE_H

#include <QDateTime>
#include <QObject>
#include <qqmlintegration.h>

#include "errorhandler.h"
#include "jsonable.h"

class Storage;
Q_DECLARE_OPAQUE_POINTER(Storage *)

class Storable : public QObject, public ErrorHandler, public Jsonable
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Storable is a base class")

public:
    enum Type {
        Type_Unknown,
        Type_Storable,
        Type_Node,
        Type_Field,
        Type_Element,
        Type_Value,
        Type_Project,
        Type_NodeType,
        Type_FieldType,
        Type_ElementType,
        Type_ValueType,
        Type_ProjectType
    };
    Q_ENUM(Type)

    static QString typeToString(int type) { return mTypeToString.value(type, "Unknown"); }
    static int stringToType(const QString &typeName)
    {
        return mTypeToString.key(typeName, Type_Unknown);
    }

    enum Flag { NoFlag, Flag_Modified = 1, Flag_Saving = 2, Flag_Loading = 4 };
    Q_ENUM(Flag)

    explicit Storable(Storage *storage, QObject *parent = nullptr)
        : Storable{Type_Storable, storage, parent}
    {}
    explicit Storable(int type, Storage *storage, QObject *parent = nullptr);

    [[nodiscard]] int rowid() const { return mRowid; }
    void setRowid(int rowid)
    {
        if (mRowid == rowid)
            return;
        mRowid = rowid;
        emit rowidChanged(QPrivateSignal{});
    }

    [[nodiscard]] int type() const { return mType; }
    void setType(int type)
    {
        if (mType == type)
            return;
        mType = type;
        emit typeChanged(QPrivateSignal{});
    }

    [[nodiscard]] QString typeName() const { return typeToString(mType); }
    void setType(const QString &typeName) { setType(stringToType(typeName)); }

    [[nodiscard]] Storage *storage() const;
    virtual void setStorage(Storage *storage)
    {
        if (mStorage == storage)
            return;
        mStorage = storage;
        emit storageChanged(QPrivateSignal{});
    }

    virtual bool reload() = 0;
    virtual bool save(bool newVersion = true) = 0;
    virtual bool recycle() = 0;

    [[nodiscard]] bool isModified() const { return mFlags & Flag_Modified; }
    void setModified(bool modified)
    {
        if (isModified() == modified)
            return;
        mFlags = modified ? mFlags | Flag_Modified : mFlags & ~Flag_Modified;
        emit modifiedChanged(QPrivateSignal{});
    }

    [[nodiscard]] QString createdBy() const { return mCreatedBy; }
    void setCreatedBy(const QString &createdBy)
    {
        if (mCreatedBy == createdBy)
            return;
        mCreatedBy = createdBy;
        emit createdByChanged(QPrivateSignal{});
    }

    [[nodiscard]] QString updatedBy() const { return mUpdatedBy; }
    void setUpdatedBy(const QString &updatedBy)
    {
        if (mUpdatedBy == updatedBy)
            return;
        mUpdatedBy = updatedBy;
        emit updatedByChanged(QPrivateSignal{});
    }

    [[nodiscard]] QDateTime createdAt() const { return mCreatedAt; }
    void setCreatedAt(const QDateTime &createdAt)
    {
        if (mCreatedAt == createdAt)
            return;
        mCreatedAt = createdAt;
        emit createdAtChanged(QPrivateSignal{});
    }

    [[nodiscard]] QDateTime updatedAt() const { return mUpdatedAt; }
    void setUpdatedAt(const QDateTime &updatedAt)
    {
        if (mUpdatedAt == updatedAt)
            return;
        mUpdatedAt = updatedAt;
        emit updatedAtChanged(QPrivateSignal{});
    }

    [[nodiscard]] int version() const { return mVersion; }
    void setVersion(int version)
    {
        if (mVersion == version)
            return;
        mVersion = version;
        emit versionChanged(QPrivateSignal{});
    }

signals:
    void rowidChanged(QPrivateSignal);
    void typeChanged(QPrivateSignal);
    void storageChanged(QPrivateSignal);
    void modifiedChanged(QPrivateSignal);
    void createdByChanged(QPrivateSignal);
    void updatedByChanged(QPrivateSignal);
    void createdAtChanged(QPrivateSignal);
    void updatedAtChanged(QPrivateSignal);

    void reloaded(QPrivateSignal);
    void saved(QPrivateSignal);
    void recycled(QPrivateSignal);
    void versionChanged(QPrivateSignal);

protected:
    bool readJson(const QJsonObject &json, QStringList *errors = nullptr) override
    {
        if (const auto v = json.value(QStringLiteral("rowid")); v.isDouble())
            setRowid(v.toInt());

        if (const auto v = json.value(QStringLiteral("type")); v.isDouble())
            setType(v.toInt());

        if (const auto v = json.value(QStringLiteral("version")); v.isDouble())
            setVersion(v.toInt());

        if (const auto created = json.value(QStringLiteral("created")).toObject();
            !created.isEmpty()) {
            if (const auto v = json.value(QStringLiteral("at")); v.isDouble())
                setCreatedAt(QDateTime::fromMSecsSinceEpoch(v.toInteger()));
            if (const auto v = json.value(QStringLiteral("by")); v.isString())
                setCreatedBy(v.toString());
        }

        if (const auto updated = json.value(QStringLiteral("updated")).toObject();
            !updated.isEmpty()) {
            if (const auto v = json.value(QStringLiteral("at")); v.isDouble())
                setUpdatedAt(QDateTime::fromMSecsSinceEpoch(v.toInteger()));
            if (const auto v = json.value(QStringLiteral("by")); v.isString())
                setUpdatedBy(v.toString());
        }

        return true;

        Q_UNUSED(errors);
    }
    bool writeJson(QJsonObject &json, QStringList *errors = nullptr) const override
    {
        json.insert(QStringLiteral("rowid"), mRowid);
        json.insert(QStringLiteral("type"), mType);
        json.insert(QStringLiteral("version"), mVersion);
        QJsonObject created;
        if (const auto at = mCreatedAt.toMSecsSinceEpoch())
            created.insert(QStringLiteral("at"), at);
        if (!mCreatedBy.isEmpty())
            created.insert(QStringLiteral("by"), mCreatedBy);
        if (!created.isEmpty())
            json.insert(QStringLiteral("created"), created);
        QJsonObject updated;
        if (const auto at = mUpdatedAt.toMSecsSinceEpoch())
            updated.insert(QStringLiteral("at"), at);
        if (!mUpdatedBy.isEmpty())
            updated.insert(QStringLiteral("by"), mUpdatedBy);
        if (!updated.isEmpty())
            json.insert(QStringLiteral("updated"), updated);
        return true;

        Q_UNUSED(errors);
    }

    [[nodiscard]] bool isLoading() const { return mFlags & Flag_Loading; }
    void setLoading(bool loading)
    {
        if (isLoading() == loading)
            return;
        mFlags = loading ? mFlags | Flag_Loading : mFlags & ~Flag_Loading;
        // emit loadingChanged(QPrivateSignal{});
    }

    [[nodiscard]] bool isSaving() const { return mFlags & Flag_Saving; }
    void setSaving(bool saving)
    {
        if (isSaving() == saving)
            return;
        mFlags = saving ? mFlags | Flag_Saving : mFlags & ~Flag_Saving;
        // emit savingChanged(QPrivateSignal{});
    }

private:
    QString mCreatedBy;
    QString mUpdatedBy;
    QDateTime mCreatedAt;
    QDateTime mUpdatedAt;
    Storage *mStorage = nullptr;
    int mRowid = 0;
    int mType = 0;
    int mVersion = 0;
    int mFlags = Flag_Modified;

    inline static const QMap<int, QString> mTypeToString = {{Type_Storable, "Storable"},
                                                            {Type_Node, "Node"},
                                                            {Type_NodeType, "NodeType"},
                                                            {Type_Element, "Element"},
                                                            {Type_ElementType, "ElementType"},
                                                            {Type_Field, "Field"},
                                                            {Type_FieldType, "FieldType"},
                                                            {Type_Value, "Value"},
                                                            {Type_ValueType, "ValueType"},
                                                            {Type_Project, "Project"},
                                                            {Type_ProjectType, "ProjectType"}};

    void emitReloaded() { emit reloaded(QPrivateSignal{}); }
    void emitSaved() { emit saved(QPrivateSignal{}); }
    void emitRecycled() { emit recycled(QPrivateSignal{}); }

    friend class Storage;
    friend class Transaction;

    Q_PROPERTY(int rowid READ rowid NOTIFY rowidChanged FINAL)
    Q_PROPERTY(int type READ type NOTIFY typeChanged FINAL)
    // Q_PROPERTY(Storage *storage READ storage WRITE setStorage NOTIFY storageChanged FINAL)
    Q_PROPERTY(bool modified READ isModified WRITE setModified NOTIFY modifiedChanged FINAL)
    Q_PROPERTY(QString createdBy READ createdBy WRITE setCreatedBy NOTIFY createdByChanged FINAL)
    Q_PROPERTY(QString updatedBy READ updatedBy WRITE setUpdatedBy NOTIFY updatedByChanged FINAL)
    Q_PROPERTY(QDateTime createdAt READ createdAt WRITE setCreatedAt NOTIFY createdAtChanged FINAL)
    Q_PROPERTY(QDateTime updatedAt READ updatedAt WRITE setUpdatedAt NOTIFY updatedAtChanged FINAL)
    Q_PROPERTY(int version READ version WRITE setVersion NOTIFY versionChanged FINAL)
};

#endif // LIBNOVELIST_STORABLE_H
