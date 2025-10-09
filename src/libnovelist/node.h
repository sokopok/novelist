#ifndef NOVELIST_NODE_H
#define NOVELIST_NODE_H

#include <QBitArray>
#include <QJsonObject>
#include <QObject>
#include <QVariantMap>
#include "../libai/config/error.h"
#include "interfaces.h"
#include "libnovelist/nodetype.h"

namespace novelist {

template<std::integral T>
constexpr T bit(T pos)
{
    return T{1} << pos;
}
template<std::integral T>
constexpr T pos(T bit)
{
    T pos = 0;
    while (!(bit & 1) && pos < sizeof(T)) {
        ++pos;
        bit = bit >> 1;
    }
    return pos;
}

class Project;

class Node : public QObject, public Storable
{
    Q_OBJECT

public:
    enum ExplicitHandling {
        LeaveExplicit,
        SetExplicit,
        UnsetExplicit,
    };
    Q_ENUM(ExplicitHandling)

    enum SaveStrategry { SaveImmediately, SaveOnTriggered, DefaultSaveStrategy = SaveOnTriggered };
    Q_ENUM(SaveStrategry)

    Node(QObject *parent = nullptr)
        : QObject{parent}
    {}

    bool reload() override;
    bool save() override;

    // [[nodiscard]] static Node* load(const QString& id);

    void recycle() override;
    void reuse(const QVariantMap &values) override;

    [[nodiscard]] virtual Project* project() const;
    [[nodiscard]] ProjectStore *projectStore() const override;

    [[nodiscard]] bool hasError() const { return mFlags & ErrorFlag; }
    [[nodiscard]] bool isValid() const { return mFlags & ValidFlag; }
    [[nodiscard]] bool isEmpty() const { return mFlags & EmptyFlag; }
    [[nodiscard]] bool isModified() const { return mFlags & ModifiedFlag; }

    [[nodiscard]] QString name() const { return mName; }
    void setName(const QString &name) { setName(name, SetExplicit); }
    void setName(const QString &name, ExplicitHandling e);

    [[nodiscard]] QString label() const { return mLabel; }
    void setLabel(const QString &label) { setLabel(label, SetExplicit); }
    void setLabel(const QString &label, ExplicitHandling e);

    [[nodiscard]] QString description() const { return mDescription; }
    void setDescription(const QString &description) { setDescription(description, SetExplicit); }
    void setDescription(const QString &description, ExplicitHandling e);

    [[nodiscard]] QString icon() const { return mIcon; }
    void setIcon(const QString &icon) { setIcon(icon, SetExplicit); }
    void setIcon(const QString &icon, ExplicitHandling e);

    // [[nodiscard]] int type() const { return mType; }
    // void setType(int type)
    // {
    //     if (mType == type)
    //         return;
    //     mType = type;
    //     emit typeChanged(QPrivateSignal{});
    // }

    // [[nodiscard]] int id() const { return mId; }
    // void setId(int id)
    // {
    //     if (mId == id)
    //         return;
    //     mId = id;
    //     emit idChanged(QPrivateSignal{});
    // }

    [[nodiscard]] SaveStrategry saveStrategry() const { return mSaveStrategry; }
    void setSaveStrategry(const SaveStrategry &saveStrategry);
    void resetSaveStrategry() { setSaveStrategry(DefaultSaveStrategy); }

    ai::Error error() const { return mError; }

    [[nodiscard]] virtual QJsonObject toJson(bool *error = nullptr) const
    {
        QJsonObject json;

        if (mExplicit.testBit(NameTag))
            json["name"] = mName;

        if (mExplicit.testBit(LabelTag))
            json["label"] = mLabel;

        if (mExplicit.testBit(DescriptionTag))
            json["description"] = mDescription;

        if (mExplicit.testBit(IconTag))
            json["icon"] = mIcon;

        if (error)
            *error = false;

        return json;
    }
    virtual bool setJson(const QJsonObject &json)
    {
        if (const auto v = json.value("name"); v.isString()) {
            if (const auto n = v.toString(); n.isEmpty()) {
                setError({ai::Error::InternalErrorType, ai::Error::InternalError, name()});
                return false;
            }

            else
                setName(n);
        }

        if (const auto v = json.value("label"); v.isString())
            setLabel(v.toString());

        if (const auto v = json.value("description"); v.isString())
            setDescription(v.toString());

        if (const auto v = json.value("icon"); v.isString())
            setIcon(v.toString());

        return true;
    }

    [[nodiscard]] virtual QJsonObject toSchema(bool *error = nullptr) const
    {
        QJsonObject json;

        json["name"] = mName;
        json["label"] = mLabel;
        json["description"] = mDescription;
        json["icon"] = mIcon;

        if (error)
            *error = false;

        return json;
    }
    virtual bool setSchema(const QJsonObject &json)
    {
        if (const auto v = json.value("name"); v.isString()) {
            if (const auto n = v.toString(); n.isEmpty()) {
                setError({ai::Error::InternalErrorType, ai::Error::InternalError, name()});
                return false;
            }

            else
                setName(n);
        }

        if (const auto v = json.value("label"); v.isString())
            setLabel(v.toString());

        if (const auto v = json.value("description"); v.isString())
            setDescription(v.toString());

        if (const auto v = json.value("icon"); v.isString())
            setIcon(v.toString());

        return true;
    }

    [[nodiscard]] NodeType *nodeType() const { return mNodeType; }
    void setNodeType(NodeType *nodeType);

signals:
    void loaded(QPrivateSignal);
    void saved(QPrivateSignal);

    void rowidChanged(QPrivateSignal);

    void errorOccurred(const ai::Error &error, QPrivateSignal);

    // void typeChanged(QPrivateSignal);
    // void idChanged(QPrivateSignal);
    void validChanged(QPrivateSignal);
    void emptyChanged(QPrivateSignal);
    void modifiedChanged(QPrivateSignal);
    void errorChanged(QPrivateSignal);

    void saveStrategryChanged(QPrivateSignal);
    void nameChanged(QPrivateSignal);
    void labelChanged(QPrivateSignal);
    void descriptionChanged(QPrivateSignal);
    void iconChanged(QPrivateSignal);

    void nodeTypeChanged();

protected:
    enum Tag { NameTag, LabelTag, DescriptionTag, IconTag, NumTags };
    enum Flag {
        NoFlag,
        ValidFlag = bit(0),
        EmptyFlag = bit(1),
        ModifiedFlag = bit(2),
        ErrorFlag = bit(3),
        NumFlags = 3,
    };

    void setError(const ai::Error &error);

    bool setRowid(quint64 rowid) override
    {
        if (Dbable::setRowid(rowid)) {
            emit rowidChanged(QPrivateSignal{});
            return true;
        }
        return false;
    }

    void setValid(bool valid)
    {
        if (isValid() != valid)
            mFlags = valid ? mFlags | ValidFlag : mFlags & ~ValidFlag;
        emit validChanged(QPrivateSignal{});
    }
    void setEmpty(bool empty)
    {
        if (isEmpty() != empty)
            mFlags = empty ? mFlags | EmptyFlag : mFlags & ~EmptyFlag;
        emit emptyChanged(QPrivateSignal{});
    }
    void setModified(bool modified)
    {
        if (isModified() != modified)
            mFlags = modified ? mFlags | ModifiedFlag : mFlags & ~ModifiedFlag;
        emit modifiedChanged(QPrivateSignal{});
    }

    [[nodiscard]] bool isExplicit(int tag) const { return mExplicit.testBit(tag); }
    void setExplicit(int tag, ExplicitHandling e)
    {
        if (e != LeaveExplicit)
            setExplicit(tag, e == SetExplicit);
    }
    void setExplicit(int tag, bool e) { mExplicit.setBit(tag, e); }

    int flags() const { return mFlags; }
    int &flags() { return mFlags; }

    QBitArray explicits() const { return mExplicit; }
    QBitArray &explicits() { return mExplicit; }

private:
    ai::Error mError;
    QString mName;
    QString mLabel;
    QString mDescription;
    QString mIcon;
    QString mPath;
    SaveStrategry mSaveStrategry = DefaultSaveStrategy;
    bool mModified = false;
    bool mEmpty = true;
    bool mValid = true;
    int mType = 0;
    int mId = 0;
    QBitArray mExplicit{8};
    int mFlags = ValidFlag | EmptyFlag;
    NodeType *mNodeType = nullptr;

    friend class ProjectStore;

    // static ProjectStore *mProjectStore;

    // Q_PROPERTY(QString path READ path NOTIFY pathChanged FINAL)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged FINAL)
    Q_PROPERTY(
        QString description READ description WRITE setDescription NOTIFY descriptionChanged FINAL)
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged FINAL)

    Q_PROPERTY(SaveStrategry saveStrategry READ saveStrategry WRITE setSaveStrategry RESET
                   resetSaveStrategry NOTIFY saveStrategryChanged FINAL)

    Q_PROPERTY(bool modified READ isModified NOTIFY modifiedChanged FINAL)
    Q_PROPERTY(bool valid READ isValid NOTIFY validChanged FINAL)
    Q_PROPERTY(bool empty READ isEmpty NOTIFY emptyChanged FINAL)
    Q_PROPERTY(bool hasError READ hasError NOTIFY errorChanged FINAL)
    Q_PROPERTY(ai::Error error READ error NOTIFY errorChanged FINAL)

    Q_PROPERTY(quint64 rowid READ rowid NOTIFY rowidChanged FINAL)
    // Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged FINAL)
    // Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged FINAL)
    Q_PROPERTY(NodeType *nodeType READ nodeType NOTIFY nodeTypeChanged FINAL)
};

} // namespace novelist

#endif // NOVELIST_NODE_H
