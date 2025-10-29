#ifndef LIBNOVELIST_NODE_H
#define LIBNOVELIST_NODE_H

#include "nodelistmodel.h"
#include "storable.h"

class NodeType;

Q_MOC_INCLUDE("nodetype.h")

class Node : public Storable
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Node is a base class")

public:
    explicit Node(Storage *storage, QObject *parent = nullptr)
        : Node{Type_Node, storage, parent}
    {}
    Node(int type, Storage *storage, QObject *parent = nullptr)
        : Node{nullptr, type, storage, parent}
    {}
    Node(NodeType *nodeType, Storage *storage, QObject *parent = nullptr)
        : Node{nodeType, Type_Node, storage, parent}
    {}
    Node(NodeType *nodeType, int type, Storage *storage, QObject *parent = nullptr)
        : Storable{type, storage, parent}
        , mNodeType{nodeType}
    {}

    bool reload() override;
    bool save(bool newVersion = true) override;
    bool recycle() override;

    [[nodiscard]] QString name() const { return mName; }
    void setName(const QString &name)
    {
        if (mName == name)
            return;
        const auto old = mName;
        mName = name;
        if (!updateName())
            setModified(true);
        emit nameChanged(mName, old, QPrivateSignal{});
    }

    [[nodiscard]] QString label() const;
    void setLabel(const QString &label)
    {
        if (mLabel == label)
            return;
        const auto old = mLabel;
        mLabel = label;
        if (!updateLabel())
            setModified(true);
        emit labelChanged(mLabel, old, QPrivateSignal{});
    }

    [[nodiscard]] QString info() const;
    void setInfo(const QString &info)
    {
        if (mInfo == info)
            return;
        const auto old = mInfo;
        mInfo = info;
        if (!updateInfo())
            setModified(true);
        emit infoChanged(mInfo, old, QPrivateSignal{});
    }

    [[nodiscard]] QString icon() const;
    void setIcon(const QString &icon)
    {
        if (mIcon == icon)
            return;
        const auto old = mIcon;
        mIcon = icon;
        if (!updateIcon())
            setModified(true);
        emit iconChanged(mIcon, old, QPrivateSignal{});
    }

    [[nodiscard]] NodeType *nodeType() const { return mNodeType; }
    void setNodeType(NodeType *nodeType) { setNodeType(nodeType, true); }

    [[nodiscard]] NodeListModel *nodeListModel();

    bool event(QEvent *event) override;

signals:
    void nameChanged(const QString &newName, const QString &oldName, QPrivateSignal);
    void labelChanged(const QString &newLabel, const QString &oldLabel, QPrivateSignal);
    void infoChanged(const QString &newInfo, const QString &oldInfo, QPrivateSignal);
    void iconChanged(const QString &newIcon, const QString &oldIcon, QPrivateSignal);
    void nodeTypeChanged(NodeType *newNodeType, NodeType *oldNodeType, QPrivateSignal);

    void childNodeAdded(Node *newChild, QPrivateSignal);
    void childNodeRemoved(Node *oldChild, QPrivateSignal);

protected:
    bool readJson(const QJsonObject &json, QStringList *errors = nullptr) override
    {
        if (!Storable::readJson(json, errors))
            return false;

        if (const auto v = json.value(QStringLiteral("name")); v.isString())
            setName(v.toString());

        if (const auto v = json.value(QStringLiteral("label")); v.isString())
            setLabel(v.toString());

        if (const auto v = json.value(QStringLiteral("info")); v.isString())
            setInfo(v.toString());

        if (const auto v = json.value(QStringLiteral("icon")); v.isString())
            setIcon(v.toString());

        return true;

        Q_UNUSED(errors);
    }
    bool writeJson(QJsonObject &json, QStringList *errors = nullptr) const override;

    virtual void setNodeType(NodeType *nodeType, bool emitSignals);
    void emitNodeTypeChanged(NodeType *newNodeType, NodeType *oldNodeType)
    {
        emit nodeTypeChanged(newNodeType, oldNodeType, QPrivateSignal{});
    }

    bool updateName();
    bool updateLabel();
    bool updateInfo();
    bool updateIcon();
    bool updateNodeType();

private:
    QString mName;
    QString mLabel;
    QString mInfo;
    QString mIcon;
    NodeType *mNodeType = nullptr;
    NodeListModel *mNodeListModel = nullptr;

    friend class NodeStorage;

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged FINAL)
    Q_PROPERTY(QString info READ info WRITE setInfo NOTIFY infoChanged FINAL)
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged FINAL)
    Q_PROPERTY(NodeType *nodeType READ nodeType NOTIFY nodeTypeChanged FINAL)
    Q_PROPERTY(NodeListModel *nodeListModel READ nodeListModel CONSTANT FINAL)
};

using NodeList = QList<Node *>;

#endif // LIBNOVELIST_NODE_H
