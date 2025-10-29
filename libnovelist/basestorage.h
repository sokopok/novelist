#ifndef BASESTORAGE_H
#define BASESTORAGE_H

#include <QHash>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "errorhandler.h"
#include "node.h"

class Storage;

class Transaction
{
protected:
    QSqlDatabase db;
    Node* node;
    int& depth;
    bool owner = false;
    bool done = false;
    int mode;

public:
    enum Mode {
        Read = 1,
        Write = 2,
        Modified = 4,
        ReadModified = Read | Modified,
        WriteModified = Write | Modified
    };

    Transaction(Mode mode, Node* node, Storage* storage);
    void commit();
    void rollback()
    {
        if (owner && !done) {
            if (mode & Write)
                db.rollback();
            done = true;
            depth = 0;
        }
    }
    ~Transaction()
    {
        if (owner && !done) {
            if (mode & Write)
                db.rollback();
            depth = 0;
        }
    }
};

class BaseStorage : public QObject, public ErrorHandler
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("BaseStorage is a base class")

public:
    explicit BaseStorage(Storage* parent = nullptr);

    [[nodiscard]] Storage* storage() const;

    [[nodiscard]] QSqlDatabase database() const { return mDatabase; }
    virtual void setDatabase(const QSqlDatabase& database) = 0;

signals:
    void nodeCreated(Node* node, QPrivateSignal);
    void nodeRecycled(Node* node, QPrivateSignal);
    void nodeRevived(Node* node, QPrivateSignal);
    void nodeDestroyed(Node* node, QPrivateSignal);
    void nodeInserted(Node* node, QPrivateSignal);
    void nodeUpdated(Node* node, QPrivateSignal);
    void nodeSaved(Node* node, QPrivateSignal);
    void nodeReloaded(Node* node, QPrivateSignal);
    void nodeLoaded(Node* node, QPrivateSignal);
    void nodeRemoved(Node* node, QPrivateSignal);

    void databaseChanged(QPrivateSignal);

protected:
    [[nodiscard]] virtual Node* createNode() = 0;
    bool virtual insertNode(Node* node) = 0;
    bool virtual updateNode(Node* node) = 0;
    bool virtual reloadNode(Node* node) = 0;
    bool virtual removeNode(int rowid) = 0;

    [[nodiscard]] Node* node()
    {
        if (Node* e = reviveNode())
            return e;
        if (Node* n = createNode()) {
            return n;
        }
        return nullptr;
    }
    [[nodiscard]] Node* node(int rowid)
    {
        if (Node* e = mNodesByRowid.value(rowid))
            return e;
        return loadNode(rowid);
    }
    bool virtual recycleNode(Node* node)
    {
        if (!node)
            return false;
        if (!mNodesByRowid.remove(node->rowid()) && !mNodes.removeOne(node))
            return false;
        mCache.append(node);
        emit nodeRecycled(node, QPrivateSignal{});
        return true;
    }
    [[nodiscard]] virtual Node* reviveNode()
    {
        if (!mCache.isEmpty()) {
            Node* node = mCache.takeLast();
            mNodes.append(node);
            emit nodeRevived(node, QPrivateSignal{});
            return node;
        }
        return nullptr;
    }
    void virtual destroyNode(Node* node)
    {
        if (!node)
            return;
        node->deleteLater();
        emit nodeDestroyed(node, QPrivateSignal{});
    }
    bool virtual saveNode(Node* node, bool newVersion = true)
    {
        if (!node)
            return false;
        if (!node->isModified())
            return true;
        return newVersion || node->rowid() <= 0 ? insertNode(node) : updateNode(node);
    }
    [[nodiscard]] virtual Node* loadNode(int rowid)
    {
        if (rowid <= 0)
            return nullptr;
        Node* n = node();
        if (!n)
            return nullptr;
        n->setRowid(rowid);
        mNodesByRowid.insert(rowid, n);
        if (!reloadNode(n)) {
            recycleNode(n);
        }
        emit nodeLoaded(n, QPrivateSignal{});
        return n;
    }

    QSqlQuery createQuery(const QString& queryString, bool forwardOnly = false)
    {
        QSqlQuery query{mDatabase};
        query.prepare(queryString);
        query.setForwardOnly(forwardOnly);
        return query;
    }
    bool executeQuery(QSqlQuery& query)
    {
        if (!query.exec()) {
            handleError({query.lastQuery(),
                         query.boundValues(),
                         query.lastError().driverText(),
                         query.lastError().databaseText()});
            return false;
        }
        return true;
    }
    bool executeQuery(QSqlQuery& query, const QVariantList& values)
    {
        query.finish();
        for (const auto& v : values)
            query.addBindValue(v);
        return executeQuery(query);
    }
    bool executeQuery(QSqlQuery& query, const QVariantMap& values)
    {
        query.finish();
        for (auto it = values.constBegin(); it != values.constEnd(); ++it)
            query.bindValue(it.key(), it.value());
        return executeQuery(query);
    }
    bool executeQuery(const QString& queryString)
    {
        QSqlQuery query{mDatabase};
        query.prepare(queryString);
        return executeQuery(query);
    }
    bool executeQuery(const QString& queryString, const QVariantList& values)
    {
        QSqlQuery query{mDatabase};
        query.prepare(queryString);
        return executeQuery(query, values);
    }
    bool executeQuery(const QString& queryString, const QVariantMap& values)
    {
        QSqlQuery query{mDatabase};
        query.prepare(queryString);
        return executeQuery(query, values);
    }

    void emitDatabaseChanged() { emit databaseChanged(QPrivateSignal{}); }

    template<typename T>
    QString itemsToString(const QList<T*>& items)
    {
        QString s;
        for (T* item : items) {
            if (!s.isEmpty())
                s += '\n';
            s += QString::number(item->rowid());
        }
        return s;
    }

    template<typename T>
    QList<T*> stringToItems(const QString& string)
    {
        QList<T*> items;
        for (const auto& s : string.split('\n', Qt::SkipEmptyParts)) {
            if (T* item = get<T>(s.toInt()); !item)
                //error!!!
                ;
            else
                items.append(item);
        }
        return items;
    }

protected:
    QHash<int, Node*> mNodesByRowid;
    QList<Node*> mNodes;
    QList<Node*> mCache;
    QSqlDatabase mDatabase;

    friend class Node;

    Q_PROPERTY(QSqlDatabase database READ database WRITE setDatabase NOTIFY databaseChanged FINAL)
};

class BaseTypeStorage : public BaseStorage
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("BaseTypeStorage is a base class")

public:
    explicit BaseTypeStorage(Storage* parent = nullptr)
        : BaseStorage{parent}
    {}

    [[nodiscard]] Q_INVOKABLE NodeType* nodeType(const QString& name)
    {
        return mNodesByName.value(name);
    }

protected:
    QHash<QString, NodeType*> mNodesByName;

    template<typename T>
    static QList<T*> toDerived(const QList<Node*>& nodes)
    {
        QList<T*> derived;
        derived.reserve(nodes.size());
        for (Node* n : nodes)
            derived.append(qobject_cast<T*>(n));
        return derived;
    }
};

#endif // BASESTORAGE_H
