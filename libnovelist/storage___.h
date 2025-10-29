#ifndef _LIBNOVELIST_STORAGE_H
#define _LIBNOVELIST_STORAGE_H

#include "element.h"
#include "elementtype.h"
#include "errorhandler.h"
#include "field.h"
#include "fieldtype.h"
#include "storageimpl.h"
#include "value.h"
#include "valuetype.h"

template<typename D>
class StorageImpl<ElementType, D> : public StorageImplBase<ElementType, D>
{
    const D& storage() const { return static_cast<const D&>(*this); }
    D& storage() { return static_cast<D&>(*this); }

public:
    StorageImpl() {}

    ElementType* construct(const QString& name = {});
    ElementType* reload(ElementType* item, int rowid = 0);
    ElementType* insert(ElementType* item);
    ElementType* update(ElementType* item);

    void createTables();
    void updateQueries();

    QSqlQuery mReloadFieldTypesQuery;
    QSqlQuery mInsertFieldTypesQuery;
    QSqlQuery mUpdateFieldTypesQuery;
};

template<typename D>
class StorageImpl<Element, D> : public StorageImplBase<Element, D>
{
    const D& storage() const { return static_cast<const D&>(*this); }
    D& storage() { return static_cast<D&>(*this); }

public:
    StorageImpl() {}

    Element* construct(const QString& name = {});
    Element* reload(Element* item, int rowid = 0);
    Element* insert(Element* item);
    Element* update(Element* item);

    void createTables();
    void updateQueries();

    QSqlQuery mReloadFieldsQuery;
    QSqlQuery mInsertFieldsQuery;
};

template<typename D>
class StorageImpl<FieldType, D> : public StorageImplBase<FieldType, D>
{
    const D& storage() const { return static_cast<const D&>(*this); }
    D& storage() { return static_cast<D&>(*this); }

public:
    StorageImpl() {}

    FieldType* construct(const QString& name = {});
    FieldType* reload(FieldType* item, int rowid = 0);
    FieldType* insert(FieldType* item);
    FieldType* update(FieldType* item);

    void createTables();
    void updateQueries();

    QSqlQuery mReloadElementTypesQuery;
    QSqlQuery mInsertElementTypesQuery;
    QSqlQuery mReloadValueTypesQuery;
    QSqlQuery mInsertValueTypesQuery;
    QSqlQuery mReloadAllowedTypesQuery;
    QSqlQuery mInsertAllowedTypesQuery;
};

template<typename D>
class StorageImpl<Field, D> : public StorageImplBase<Field, D>
{
    const D& storage() const { return static_cast<const D&>(*this); }
    D& storage() { return static_cast<D&>(*this); }

public:
    StorageImpl() {}

    Field* construct(const QString& name = {});
    Field* reload(Field* item, int rowid = 0);
    Field* insert(Field* item);
    Field* update(Field* item);

    void createTables();
    void updateQueries();

    QSqlQuery mReloadElementsQuery;
    QSqlQuery mInsertElementsQuery;
    QSqlQuery mReloadValuesQuery;
    QSqlQuery mInsertValuesQuery;
    QSqlQuery mReloadAllowedTypesQuery;
    QSqlQuery mInsertAllowedTypesQuery;
};

template<typename D>
class StorageImpl<ValueType, D> : public StorageImplBase<ValueType, D>
{
    const D& storage() const { return static_cast<const D&>(*this); }
    D& storage() { return static_cast<D&>(*this); }

public:
    StorageImpl() {}

    ValueType* construct(const QString& name = {});
    ValueType* reload(ValueType* item, int rowid = 0);
    ValueType* insert(ValueType* item);
    ValueType* update(ValueType* item);

    void createTables();
    void updateQueries();

    QSqlQuery mReloadFieldTypesQuery;
    QSqlQuery mInsertFieldTypesQuery;
};

template<typename D>
class StorageImpl<Value, D> : public StorageImplBase<Value, D>
{
    const D& storage() const { return static_cast<const D&>(*this); }
    D& storage() { return static_cast<D&>(*this); }

public:
    StorageImpl() {}

    Value* construct(const QString& name = {});
    Value* reload(Value* item, int rowid = 0);
    Value* insert(Value* item);
    Value* update(Value* item);

    void createTables();
    void updateQueries();

    QSqlQuery mReloadFieldsQuery;
    QSqlQuery mInsertFieldsQuery;
};

class Transaction
{
    QSqlDatabase db;
    int& depth;
    bool owner = false;
    bool done = false;

public:
    Transaction(QSqlDatabase d, int& depth)
        : db(d)
        , depth(depth)
    {
        owner = (depth++ == 0);
        if (owner)
            db.transaction();
    }
    void commit()
    {
        if (owner && !done) {
            db.commit();
            done = true;
            depth = 0;
        }
    }
    void rollback()
    {
        if (owner && !done) {
            db.rollback();
            done = true;
            depth = 0;
        }
    }
    ~Transaction()
    {
        if (owner && !done) {
            db.rollback();
            depth = 0;
        }
    }
};

class Storage : public QObject,
                public ErrorHandler,
                public StorageImpl<Storable, Storage>,
                public StorageImpl<Node, Storage>,
                public StorageImpl<Field, Storage>,
                public StorageImpl<Element, Storage>,
                public StorageImpl<Value, Storage>,
                public StorageImpl<NodeType, Storage>,
                public StorageImpl<FieldType, Storage>,
                public StorageImpl<ElementType, Storage>,
                public StorageImpl<ValueType, Storage>
{
    Q_OBJECT

public:
    Storage() {}

    [[nodiscard]] QSqlDatabase database() const { return mDatabase; }
    void setDatabase(const QSqlDatabase& database)
    {
        mDatabase = database;

        if (database.isOpen()) {
            createTables();
            updateQueries();
        }

        emit databaseChanged(QPrivateSignal{});
    }

    [[nodiscard]] QString databaseName() const { return mDatabaseName; }
    void setDatabaseName(const QString& databaseName)
    {
        if (mDatabaseName == databaseName)
            return;
        if (mDatabase.isOpen()) {
            closeDatabase();
            openDatabase(databaseName);
        } else {
            mDatabaseName = databaseName;
            emit databaseNameChanged(QPrivateSignal{});
        }
    }

    [[nodiscard]] QString databaseConnectionName() const { return mDatabaseConnectionName; }
    void setDatabaseConnectionName(const QString& databaseConnectionName)
    {
        if (mDatabaseConnectionName == databaseConnectionName)
            return;
        mDatabaseConnectionName = databaseConnectionName;
        emit databaseConnectionNameChanged(QPrivateSignal{});
    }

    bool openDatabase(const QString& databaseName = {})
    {
        bool databaseNameHasChanged = false;
        if (!databaseName.isEmpty() && mDatabaseName != databaseName) {
            databaseNameHasChanged = true;
            mDatabaseName = databaseName;
        }

        if (mDatabaseName.isEmpty())
            return false;

        if (QSqlDatabase::contains(mDatabaseConnectionName))
            QSqlDatabase::removeDatabase(mDatabaseConnectionName);

        mDatabase = QSqlDatabase::addDatabase("QSQLITE", mDatabaseConnectionName);
        mDatabase.setDatabaseName(mDatabaseName);
        if (!mDatabase.open())
            return false;

        // QSqlQuery pragma{mDatabase};
        // pragma.exec("PRAGMA foreign_keys = ON");

        setDatabase(mDatabase);

        if (databaseNameHasChanged)
            emit databaseNameChanged(QPrivateSignal{});

        return true;
    }
    void closeDatabase()
    {
        if (!mDatabase.isValid())
            return;
        if (mDatabase.isOpen()) {
            const auto name = mDatabase.connectionName();
            mDatabase.close();
            QSqlDatabase::removeDatabase(name);

            emit databaseChanged(QPrivateSignal{});
        }
    }

    QMap<QString, NodeType*> nodeTypes(int type) { return mNodeTypes.value(type); }
    NodeType* nodeType(int type, const QString& name) { return mNodeTypes.value(type).value(name); }

    Storable* get(int rowid)
    {
        if (rowid <= 0)
            return nullptr;

        if (Storable* item = getItem(rowid))
            return item;

        return load(rowid);
    }
    Storable* load(int rowid)
    {
        if (rowid <= 0)
            return nullptr;

        if (Storable* item = getItem(rowid)) {
            switch (item->type()) {
            case Storable::Type_Storable:
                return reload<Storable>(item, item->rowid());
            case Storable::Type_Node:
                return reload<Node>(qobject_cast<Node*>(item), item->rowid());
            case Storable::Type_Field:
                return reload<Field>(qobject_cast<Field*>(item), item->rowid());
            case Storable::Type_Element:
                return reload<Element>(qobject_cast<Element*>(item), item->rowid());
            case Storable::Type_Value:
                return reload<Value>(qobject_cast<Value*>(item), item->rowid());
            case Storable::Type_NodeType:
                return reload<NodeType>(qobject_cast<NodeType*>(item), item->rowid());
            case Storable::Type_FieldType:
                return reload<FieldType>(qobject_cast<FieldType*>(item), item->rowid());
            case Storable::Type_ElementType:
                return reload<ElementType>(qobject_cast<ElementType*>(item), item->rowid());
            case Storable::Type_ValueType:
                return reload<ValueType>(qobject_cast<ValueType*>(item), item->rowid());
            default:
                handleError("");
                return nullptr;
            }
        }

        QSqlQuery query = createQuery("SELECT `type` FROM `Storable` WHERE `id`=:id");
        query.bindValue(":id", rowid);
        if (!query.exec() || !query.next())
            return nullptr;

        switch (query.value("type").toInt()) {
        case Storable::Type_Storable:
            if (Storable* item = get<Storable>(); item && (item = reload<Storable>(item, rowid)))
                return item;
            break;
        case Storable::Type_Node:
            if (Node* item = get<Node>(); item && (item = reload<Node>(item, rowid)))
                return item;
            break;
        case Storable::Type_Field:
            if (Field* item = get<Field>(); item && (item = reload<Field>(item, rowid)))
                return item;
            break;
        case Storable::Type_Element:
            if (Element* item = get<Element>(); item && (item = reload<Element>(item, rowid)))
                return item;
            break;
        case Storable::Type_Value:
            if (Value* item = get<Value>(); item && (item = reload<Value>(item, rowid)))
                return item;
            break;
        case Storable::Type_NodeType:
            if (NodeType* item = get<NodeType>(); item && (item = reload<NodeType>(item, rowid)))
                return item;
            break;
        case Storable::Type_FieldType:
            if (FieldType* item = get<FieldType>(); item && (item = reload<FieldType>(item, rowid)))
                return item;
            break;
        case Storable::Type_ElementType:
            if (ElementType* item = get<ElementType>();
                item && (item = reload<ElementType>(item, rowid)))
                return item;
            break;
        case Storable::Type_ValueType:
            if (ValueType* item = get<ValueType>(); item && (item = reload<ValueType>(item, rowid)))
                return item;
            break;
        default:
            handleError("");
            return nullptr;
        }

        return nullptr;
    }

    template<typename T>
    T* get()
    {
        if (T* item = revive<T>())
            return item;
        return create<T>();
    }
    template<typename T>
    T* get(int rowid)
    {
        if (rowid <= 0)
            return nullptr;

        if (T* item = getItem<T>(rowid))
            return item;

        return load<T>(rowid);
    }
    template<typename T>
    T* put(T* item)
    {
        if (!item)
            return nullptr;

        if ((item->rowid() > 0 && hasItem(item->rowid())) || hasAnonymousItem(item))
            return nullptr;

        if (item->rowid() > 0) {
            takeAnonymousItem(item);
            putItem(item->rowid(), item);
        } else
            putAnonymousItem(item);

        return item;
    }
    template<typename T>
    T* load(int rowid)
    {
        if (rowid <= 0)
            return nullptr;

        if (T* item = getItem<T>(rowid))
            return reload<T>(item, item->rowid());

        QSqlQuery query = createQuery("SELECT `id` FROM `Storable` WHERE `id`=:id");
        query.bindValue(":id", rowid);
        if (!query.exec() || !query.next())
            return nullptr;

        if (T* item = get<T>(); item && (item = reload<T>(item, rowid)))
            return item;

        return nullptr;
    }
    template<typename T>
    T* save(T* item, bool newVersion = true)
    {
        if (!item)
            return nullptr;

        return newVersion || item->rowid() <= 0 ? insert<T>(item) : update<T>(item);
    }

    template<typename T>
    T* create()
    {
        if (T* item = construct<T>(); item && (item = revive<T>(item)))
            return item;
        return nullptr;
    }
    template<typename T>
    T* revive(T* item = nullptr)
    {
        if (!item) {
            if (item = takeCachedItem<T>(); !item)
                return nullptr;
        }

        if (item->rowid())
            putItem(item->rowid(), item);
        else
            putAnonymousItem(item);

        if (NodeType* nodeType = qobject_cast<NodeType*>(item)) {
            connect(nodeType, &Node::nameChanged, this, [this, nodeType](const QString& oldName) {
                if (!oldName.isEmpty())
                    mNodeTypes[nodeType->type()].remove(oldName);
                if (!nodeType->name().isEmpty())
                    mNodeTypes[nodeType->type()].insert(nodeType->name(), nodeType);
            });
        }

        return item;
    }
    template<typename T>
    T* recycle(T* item)
    {
        if (!item)
            return nullptr;

        if (!takeItem(item->rowid()) && !takeAnonymousItem(item))
            return nullptr;

        if (NodeType* nodeType = qobject_cast<NodeType*>(item)) {
            if (!nodeType->name().isEmpty())
                mNodeTypes[nodeType->type()].remove(nodeType->name());
        }

        item->disconnect();
        // item->setParent(this);

        putCachedItem(item);

        return item;
    }

    bool remove(int rowid)
    {
        if (rowid <= 0)
            return false;

        return false;
    }

    template<typename T>
    T* construct(const QString& name = {})
    {
        return StorageImpl<T, Storage>::construct(name);
    }
    template<typename T>
    T* reload(T* item, int rowid = 0)
    {
        return StorageImpl<T, Storage>::reload(item, rowid);
    }
    template<typename T>
    T* insert(T* item)
    {
        return StorageImpl<T, Storage>::insert(item);
    }
    template<typename T>
    T* update(T* item)
    {
        return StorageImpl<T, Storage>::update(item);
    }


signals:
    void databaseChanged(QPrivateSignal);
    void databaseNameChanged(QPrivateSignal);
    void databaseConnectionNameChanged(QPrivateSignal);

    void reloaded(Storable* item, QPrivateSignal);
    void saved(Storable* item, QPrivateSignal);
    void recycled(Storable* item, QPrivateSignal);

protected:
    void createTables();
    void updateQueries();

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

    bool hasItem(int rowid) const { return mItems.contains(rowid); }
    Storable* getItem(int rowid) const { return mItems.value(rowid); }
    Storable* takeItem(int rowid) { return mItems.take(rowid); }
    void putItem(int rowid, Storable* item) { mItems[rowid] = item; }
    template<typename T>
    T* getItem(int rowid) const
    {
        return qobject_cast<T*>(getItem(rowid));
    }
    template<typename T>
    T* takeItem(int rowid)
    {
        return qobject_cast<T*>(takeItem(rowid));
    }

    bool hasAnonymousItem(Storable* item) const { return mAnonymousItems.contains(item); }
    Storable* takeAnonymousItem(Storable* item)
    {
        if (mAnonymousItems.removeOne(item))
            return item;
        return nullptr;
    }
    void putAnonymousItem(Storable* item) { mAnonymousItems.append(item); }
    template<typename T>
    T* takeAnonymousItem(Storable* item)
    {
        return qobject_cast<T*>(takeAnonymousItem(item));
    }

    bool hasCachedItems() const { return !mCachedItems.isEmpty(); }
    Storable* takeCachedItem()
    {
        if (hasCachedItems())
            return mCachedItems.takeLast();
        return nullptr;
    }
    void putCachedItem(Storable* item) { mCachedItems.append(item); }
    template<typename T>
    T* takeCachedItem()
    {
        return qobject_cast<T*>(takeCachedItem());
    }

    bool mTransaction = false;

private:
    QMap<int, Storable*> mItems;
    QList<Storable*> mAnonymousItems;
    QList<Storable*> mCachedItems;
    QMap<int, QMap<QString, NodeType*>> mNodeTypes;

    QSqlDatabase mDatabase = QSqlDatabase::database();
    QString mDatabaseName;
    QString mDatabaseConnectionName;

    friend StorageImpl<Storable, Storage>;
    friend StorageImpl<Node, Storage>;
    friend StorageImpl<Field, Storage>;
    friend StorageImpl<Element, Storage>;
    friend StorageImpl<Value, Storage>;
    friend StorageImpl<NodeType, Storage>;
    friend StorageImpl<FieldType, Storage>;
    friend StorageImpl<ElementType, Storage>;
    friend StorageImpl<ValueType, Storage>;
    friend StorageImplBase<Storable, Storage>;
    friend StorageImplBase<Node, Storage>;
    friend StorageImplBase<Field, Storage>;
    friend StorageImplBase<Element, Storage>;
    friend StorageImplBase<Value, Storage>;
    friend StorageImplBase<NodeType, Storage>;
    friend StorageImplBase<FieldType, Storage>;
    friend StorageImplBase<ElementType, Storage>;
    friend StorageImplBase<ValueType, Storage>;

    Q_PROPERTY(QString databaseConnectionName READ databaseConnectionName WRITE
                   setDatabaseConnectionName NOTIFY databaseConnectionNameChanged FINAL)
};

template<typename T, typename D>
inline bool StorageImplBase<T, D>::transaction()
{
    if (!storage().mTransaction)
        return storage().mTransaction = storage().database().transaction();
    return false;
}

template<typename T, typename D>
inline bool StorageImplBase<T, D>::commit()
{
    if (storage().mTransaction) {
        storage().mTransaction = false;
        return storage().database().commit();
    }
    return false;
}

template<typename T, typename D>
inline bool StorageImplBase<T, D>::rollback()
{
    if (storage().mTransaction) {
        storage().mTransaction = false;
        return storage().database().rollback();
    }
    return false;
}

template<>
inline void StorageImpl<Storable, Storage>::createTables()
{
    storage().executeQuery("CREATE TABLE IF NOT EXISTS `Storable` (\n"
                           "  `id`	      INTEGER NOT NULL UNIQUE,\n"
                           "  `type`	  INTEGER NOT NULL,\n"
                           "  `version`	  INTEGER NOT NULL,\n"
                           "  `createdAt` INTEGER,\n"
                           "  `updatedAt` INTEGER,\n"
                           "  `createdBy` TEXT,\n"
                           "  `updatedBy` TEXT,\n"
                           "  PRIMARY KEY(`id` AUTOINCREMENT)\n"
                           ")");
}

template<>
inline void StorageImpl<Storable, Storage>::updateQueries()
{
    mReloadQuery = storage().createQuery("SELECT * FROM `Storable` WHERE `id`=:id");
    mInsertQuery = storage().createQuery(
        "INSERT INTO `Storable` (`type`,`version`,`createdAt`,`createdBy`) VALUES "
        "(:type,1,:createdAt,:createdBy)");
    mUpdateQuery = storage().createQuery("UPDATE `Storable` SET "
                                         "`type`=:type,`version`=:version,`createdAt`=:createdAt,`"
                                         "createdBy`=:createdBy,`updatedAt`=:updatedAt,`"
                                         "updatedBy`=:updatedBy WHERE `id`=:id");
}

template<>
inline Storable* StorageImpl<Storable, Storage>::construct(const QString& name)
{
    return nullptr;
}

template<>
inline Storable* StorageImpl<Storable, Storage>::reload(Storable* storable, int rowid)
{
    if (!storable)
        return nullptr;

    if (rowid <= 0)
        rowid = storable->rowid();

    if (rowid <= 0)
        return nullptr;

    if (!storage().executeQuery(mReloadQuery, QVariantMap{{":id", rowid}}))
        return nullptr;

    if (!mReloadQuery.next())
        return nullptr;

    storable->setRowid(rowid);
    storable->setType(mReloadQuery.value("type").toInt());
    storable->setVersion(mReloadQuery.value("version").toInt());
    storable->setCreatedAt(
        QDateTime::fromMSecsSinceEpoch(mReloadQuery.value("createdAt").value<qint64>()));
    storable->setUpdatedAt(
        QDateTime::fromMSecsSinceEpoch(mReloadQuery.value("updatedAt").value<qint64>()));
    storable->setCreatedBy(mReloadQuery.value("createdBy").toString());
    storable->setUpdatedBy(mReloadQuery.value("updatedBy").toString());

    storage().takeAnonymousItem(storable);
    storage().putItem(rowid, storable);

    return storable;
}

template<>
inline Storable* StorageImpl<Storable, Storage>::insert(Storable* storable)
{
    if (!storable) {
        rollback();
        return nullptr;
    }

    bool myTransaction = transaction();

    const QDateTime createdAt = QDateTime::currentDateTime();
    const int version = storable->version() + 1;

    if (!storage().executeQuery(mInsertQuery,
                                QVariantMap{{":type", storable->type()},
                                            {":version", version},
                                            {":createdAt", createdAt.toMSecsSinceEpoch()},
                                            {":createdBy", storable->createdBy()}})) {
        rollback();
        return nullptr;
    }

    if (!mInsertQuery.lastInsertId().isValid()) {
        rollback();
        return nullptr;
    }

    const int rowid = mInsertQuery.lastInsertId().toInt();

    if (myTransaction) {
        commit();
        storable->setModified(false);
    }

    storable->setRowid(rowid);
    storable->setCreatedAt(createdAt);
    storable->setVersion(version);

    return storable;
}

template<>
inline Storable* StorageImpl<Storable, Storage>::update(Storable* storable)
{
    if (!storable) {
        storage().handleError("");
        return nullptr;
    }

    bool myTransaction = transaction();

    const QDateTime updatedAt = QDateTime::currentDateTime();
    const int version = storable->version();

    if (!storage().executeQuery(mUpdateQuery,
                                QVariantMap{{":type", storable->type()},
                                            {":version", version},
                                            {":createdAt",
                                             storable->createdAt().toMSecsSinceEpoch()},
                                            {":updatedAt", updatedAt.toMSecsSinceEpoch()},
                                            {":createdBy", storable->createdBy()},
                                            {":updatedBy", storable->updatedBy()},
                                            {":id", storable->rowid()}})) {
        storage().handleError("");
        return nullptr;
    }

    if (myTransaction) {
        commit();
        storable->setModified(false);
    }

    storable->setUpdatedAt(updatedAt);
    storable->setVersion(version);

    return storable;
}

template<>
inline void StorageImpl<Node, Storage>::createTables()
{
    storage().executeQuery(
        "CREATE TABLE IF NOT EXISTS `Node` (\n"
        "  `id`	     INTEGER NOT NULL UNIQUE,\n"
        "  `nodeType` INTEGER NOT NULL,\n"
        "  `name`     TEXT,\n"
        "  `label`    TEXT,\n"
        "  `info`     TEXT,\n"
        "  `icon`     TEXT,\n"
        "  PRIMARY KEY(`id`),\n"
        "  FOREIGN KEY(`id`) REFERENCES Storable(`id`) ON DELETE CASCADE,\n"
        "  FOREIGN KEY(`nodeType`) REFERENCES Storable(`id`) ON DELETE NO ACTION\n"
        ")");
}

template<>
inline void StorageImpl<Node, Storage>::updateQueries()
{
    mReloadQuery = storage().createQuery("SELECT * FROM `Node` WHERE `id`=:id");
    mInsertQuery = storage().createQuery(
        "INSERT INTO `Node` (`id`,`nodeType`,`name`,`label`,`info`,`icon`) VALUES "
        "(:id,:nodeType,:name,:label,:info,:icon)");
    mUpdateQuery = storage().createQuery("UPDATE `Node` SET "
                                         "`nodeType=:nodeType`,`name`=:name,`label`=:label,`info`=:"
                                         "info,`icon`=:icon WHERE `id`=:id");
}

template<>
inline Node* StorageImpl<Node, Storage>::construct(const QString& name)
{
    return nullptr;
}

template<>
inline Node* StorageImpl<Node, Storage>::reload(Node* node, int rowid)
{
    if (!node)
        return nullptr;

    if (!storage().reload<Storable>(node, rowid))
        return nullptr;

    if (!storage().executeQuery(mReloadQuery, QVariantMap{{":id", node->rowid()}}))
        return nullptr;

    if (!mReloadQuery.next())
        return nullptr;

    node->setNodeType(qobject_cast<NodeType*>(storage().nodeType(node->type(), "")));
    node->setName(mReloadQuery.value("name").toString());
    node->setLabel(mReloadQuery.value("label").toString());
    node->setInfo(mReloadQuery.value("info").toString());
    node->setIcon(mReloadQuery.value("icon").toString());

    return node;
}

template<>
inline Node* StorageImpl<Node, Storage>::insert(Node* node)
{
    if (!node) {
        rollback();
        return nullptr;
    }

    bool myTransaction = transaction();

    if (!storage().insert<Storable>(node)) {
        rollback();
        return nullptr;
    }

    if (!storage().executeQuery(mInsertQuery,
                                QVariantMap{{":id", node->rowid()},
                                            {":nodeType",
                                             node->nodeType() ? node->nodeType()->rowid() : 0},
                                            {":name", node->name()},
                                            {":label", node->label()},
                                            {":info", node->info()},
                                            {":icon", node->icon()}})) {
        rollback();
        return nullptr;
    }

    if (myTransaction) {
        commit();
        node->setModified(false);
    }

    return node;
}

template<>
inline Node* StorageImpl<Node, Storage>::update(Node* node)
{
    if (!node) {
        storage().handleError("");
        return nullptr;
    }

    bool myTransaction = transaction();

    if (!storage().executeQuery(mUpdateQuery,
                                QVariantMap{{":nodeType",
                                             node->nodeType() ? node->nodeType()->rowid() : 0},
                                            {":name", node->name()},
                                            {":label", node->label()},
                                            {":info", node->info()},
                                            {":icon", node->icon()},
                                            {":id", node->rowid()}})) {
        storage().handleError("");
        return nullptr;
    }

    if (myTransaction) {
        commit();
        node->setModified(false);
    }

    return node;
}

template<>
inline void StorageImpl<Field, Storage>::createTables()
{
    storage().executeQuery("CREATE TABLE IF NOT EXISTS `Field` (\n"
                           "  `id`	      INTEGER NOT NULL UNIQUE,\n"
                           "  `minOccurs` INTEGER NOT NULL,\n"
                           "  `maxOccurs` INTEGER NOT NULL,\n"
                           "  PRIMARY KEY(`id`),\n"
                           "  FOREIGN KEY(`id`) REFERENCES Storable(`id`) ON DELETE CASCADE\n"
                           ")");
    storage().executeQuery("CREATE TABLE IF NOT EXISTS `Field_values` (\n"
                           "  `id`	        INTEGER NOT NULL UNIQUE,\n"
                           "  `index`	    INTEGER NOT NULL,\n"
                           "  `field`       INTEGER NOT NULL,\n"
                           "  `value`       INTEGER NOT NULL,\n"
                           "  PRIMARY KEY(`id` AUTOINCREMENT)\n"
                           ")");
    storage().executeQuery(
        "CREATE INDEX IF NOT EXISTS idx_Field_values_field ON Field_values(field)");
    storage().executeQuery(
        "CREATE INDEX IF NOT EXISTS idx_Field_values_value ON Field_values(value)");
    storage().executeQuery("CREATE TABLE IF NOT EXISTS `Field_allowedTypes` (\n"
                           "  `id`	        INTEGER NOT NULL UNIQUE,\n"
                           "  `index`	    INTEGER NOT NULL,\n"
                           "  `field`       INTEGER NOT NULL,\n"
                           "  `type`        INTEGER NOT NULL,\n"
                           "  PRIMARY KEY(`id` AUTOINCREMENT)\n"
                           ")");
    storage().executeQuery(
        "CREATE INDEX IF NOT EXISTS idx_Field_allowedTypes_field ON Field_allowedTypes(field)");
    storage().executeQuery(
        "CREATE INDEX IF NOT EXISTS idx_Field_allowedTypes_type ON Field_allowedTypes(type)");
}

template<>
inline void StorageImpl<Field, Storage>::updateQueries()
{
    mReloadQuery = storage().createQuery("SELECT * FROM `Field` WHERE `id`=:id");
    mReloadElementsQuery = storage().createQuery(
        "SELECT * FROM `Element_fields` WHERE `field`=:field ORDER BY `index`");
    mInsertQuery = storage().createQuery(
        "INSERT INTO `Field` (`id`,`minOccurs`,`maxOccurs`) VALUES (:id,:minOccurs,:maxOccurs)");
    mUpdateQuery = storage().createQuery(
        "UPDATE `Field` SET `minOccurs`=:minOccurs,`maxOccurs`=:maxOccurs WHERE `id`=:id");

    mReloadValuesQuery = storage().createQuery(
        "SELECT * FROM `Field_values` WHERE `field`=:field ORDER BY `index`");
    mInsertValuesQuery = storage().createQuery(
        "INSERT INTO `Field_values` (`index`,`field`,`value`) VALUES "
        "(:index,:field,:value)");

    mReloadAllowedTypesQuery = storage().createQuery(
        "SELECT * FROM `Field_allowedTypes` WHERE `field`=:field ORDER BY `index`");
    mInsertAllowedTypesQuery = storage().createQuery(
        "INSERT INTO `Field_allowedTypes` (`index`,`field`,`type`) VALUES "
        "(:index,:field,:type)");
}

template<>
inline Field* StorageImpl<Field, Storage>::construct(const QString& name)
{
    return new Field{qobject_cast<FieldType*>(
                         storage().nodeType(Storable::Type_FieldType,
                                            name.isEmpty() ? "FieldType" : name)),
                     &storage()};
}

template<>
inline Field* StorageImpl<Field, Storage>::reload(Field* field, int rowid)
{
    if (!field)
        return nullptr;

    if (!storage().reload<Node>(field, rowid))
        return nullptr;

    if (!storage().executeQuery(mReloadQuery, {field->rowid()}))
        return nullptr;

    if (!mReloadQuery.next())
        return nullptr;

    field->setMinOccurs(mReloadQuery.value("minOccurs").toInt());
    field->setMaxOccurs(mReloadQuery.value("maxOccurs").toInt());

    if (!storage().executeQuery(mReloadElementsQuery, QVariantMap{{":field", field->rowid()}})) {
        storage().handleError("");
        return nullptr;
    }

    QList<Element*> elements;
    // elements.reserve(mReloadElementsQuery.size());
    while (mReloadElementsQuery.next())
        if (Element* element = qobject_cast<Element*>(
                storage().get(mReloadElementsQuery.value("element").toInt())))
            elements.append(element);
        else
            storage().handleError("");

    field->setElements(elements);

    if (!storage().executeQuery(mReloadValuesQuery, QVariantMap{{":field", field->rowid()}})) {
        storage().handleError("");
        return nullptr;
    }

    QList<Value*> values;
    // values.reserve(mReloadValuesQuery.size());
    while (mReloadValuesQuery.next())
        if (Value* value = qobject_cast<Value*>(
                storage().get(mReloadValuesQuery.value("value").toInt())))
            values.append(value);
        else
            storage().handleError("");

    field->setValues(values);

    if (!storage().executeQuery(mReloadAllowedTypesQuery, QVariantMap{{":field", field->rowid()}})) {
        storage().handleError("");
        return nullptr;
    }

    QList<int> allowedTypes;
    while (mReloadAllowedTypesQuery.next())
        if (int type = mReloadAllowedTypesQuery.value("type").toInt(); type > 0)
            allowedTypes.append(type);
        else
            storage().handleError("");

    field->setAllowedTypes(allowedTypes);

    return field;
}

template<>
inline Field* StorageImpl<Field, Storage>::insert(Field* field)
{
    if (!field) {
        rollback();
        return nullptr;
    }

    bool myTransaction = transaction();

    if (!storage().insert<Node>(field)) {
        rollback();
        return nullptr;
    }

    for (Value* value : field->values())
        value->save(true);

    if (!storage().executeQuery(mInsertQuery,
                                QVariantMap{{":id", field->rowid()},
                                            {":minOccurs", field->mMinOccurs},
                                            {":maxOccurs", field->mMaxOccurs}})) {
        rollback();
        return nullptr;
    }

    int index = 0;
    for (Value* value : field->values()) {
        if (!storage().executeQuery(mInsertValuesQuery,
                                    QVariantMap{{":index", index},
                                                {":field", field->rowid()},
                                                {":value", value->rowid()}})) {
            rollback();
            return nullptr;
        }
        ++index;
    }

    index = 0;
    for (int type : field->mAllowedTypes) {
        if (!storage().executeQuery(mInsertAllowedTypesQuery,
                                    QVariantMap{{":index", index},
                                                {":field", field->rowid()},
                                                {":type", type}})) {
            rollback();
            return nullptr;
        }
        ++index;
    }

    if (myTransaction) {
        commit();
        field->setModified(false);
    }

    return field;
}

template<>
inline Field* StorageImpl<Field, Storage>::update(Field* field)
{
    if (!field) {
        storage().handleError("");
        return nullptr;
    }

    bool myTransaction = transaction();

    if (!storage().executeQuery(mUpdateQuery,
                                QVariantMap{{":minOccurs", field->mMinOccurs},
                                            {":maxOccurs", field->mMaxOccurs},
                                            {":id", field->rowid()}})) {
        storage().handleError("");
        return nullptr;
    }

    for (Value* value : field->values())
        value->save(true);

    if (!storage().executeQuery("DELETE FROM `Field_values` WHERE `field`=:field",
                                QVariantMap{{":field", field->rowid()}})) {
        storage().handleError("");
        rollback();
        return nullptr;
    }

    int index = 0;
    for (Value* value : field->values()) {
        if (!storage().executeQuery(mInsertValuesQuery,
                                    QVariantMap{{":index", index},
                                                {":field", field->rowid()},
                                                {":value", value->rowid()}})) {
            storage().handleError("");
            rollback();
            return nullptr;
        }
        ++index;
    }

    if (!storage().executeQuery("DELETE FROM `Field_allowedTypes` WHERE `field`=:field",
                                QVariantMap{{":field", field->rowid()}})) {
        storage().handleError("");
        rollback();
        return nullptr;
    }

    index = 0;
    for (int type : field->allowedTypes()) {
        if (!storage().executeQuery(mInsertAllowedTypesQuery,
                                    QVariantMap{{":index", index},
                                                {":field", field->rowid()},
                                                {":type", type}})) {
            rollback();
            return nullptr;
        }
        ++index;
    }

    if (myTransaction) {
        commit();
        field->setModified(false);
    }

    return field;
}

template<>
inline void StorageImpl<Element, Storage>::createTables()
{
    storage().executeQuery("CREATE TABLE IF NOT EXISTS `Element` (\n"
                           "  `id`	   INTEGER NOT NULL UNIQUE,\n"
                           "  PRIMARY KEY(`id`),\n"
                           "  FOREIGN KEY(`id`) REFERENCES Storable(`id`) ON DELETE CASCADE\n"
                           ")");
    storage().executeQuery("CREATE TABLE IF NOT EXISTS `Element_fields` (\n"
                           "  `id`	        INTEGER NOT NULL UNIQUE,\n"
                           "  `index`	    INTEGER NOT NULL,\n"
                           "  `element`     INTEGER NOT NULL,\n"
                           "  `field`       INTEGER NOT NULL,\n"
                           "  PRIMARY KEY(`id` AUTOINCREMENT)\n"
                           ")");
    storage().executeQuery(
        "CREATE INDEX IF NOT EXISTS idx_Element_fields_element ON Element_fields(element)");
    storage().executeQuery(
        "CREATE INDEX IF NOT EXISTS idx_Element_fields_field ON Element_fields(field)");
}

template<>
inline void StorageImpl<Element, Storage>::updateQueries()
{
    mReloadQuery = storage().createQuery("SELECT * FROM `Element` WHERE `id`=:id");
    mReloadFieldsQuery = storage().createQuery(
        "SELECT * FROM `Element_fields` WHERE `element`=:element ORDER BY `index`");
    mInsertQuery = storage().createQuery("INSERT INTO `Element` (`id`) VALUES (:id)");
    mInsertFieldsQuery = storage().createQuery(
        "INSERT INTO `Element_fields` (`index`,`element`,`field`) VALUES "
        "(:index,:element,:field)");
    mUpdateQuery = storage().createQuery("UPDATE `Element` SET `id`=:id WHERE `id`=:id");
}

template<>
inline Element* StorageImpl<Element, Storage>::construct(const QString& name)
{
    return new Element{qobject_cast<ElementType*>(
                           storage().nodeType(Storable::Type_ElementType,
                                              name.isEmpty() ? "ElementType" : name)),
                       &storage()};
}

template<>
inline Element* StorageImpl<Element, Storage>::reload(Element* element, int rowid)
{
    if (!element)
        return nullptr;

    if (!storage().reload<Node>(element, rowid))
        return nullptr;

    if (!storage().executeQuery(mReloadQuery, {element->rowid()}))
        return nullptr;

    if (!mReloadQuery.next())
        return nullptr;

    element->setRowid(rowid);

    if (!storage().executeQuery(mReloadFieldsQuery, QVariantMap{{":element", element->rowid()}})) {
        storage().handleError("");
        return nullptr;
    }

    QList<Field*> fields;
    // fields.reserve(mReloadFieldsQuery.size());
    while (mReloadFieldsQuery.next())
        if (Field* field = qobject_cast<Field*>(
                storage().get(mReloadFieldsQuery.value("field").toInt())))
            fields.append(field);
        else
            storage().handleError("");

    element->setFields(fields);

    return element;
}

template<>
inline Element* StorageImpl<Element, Storage>::insert(Element* element)
{
    if (!element) {
        rollback();
        return nullptr;
    }

    bool myTransaction = transaction();

    if (!storage().insert<Node>(element)) {
        rollback();
        return nullptr;
    }

    for (Field* field : element->fields())
        field->save(true);

    if (!storage().executeQuery(mInsertQuery, QVariantMap{{":id", element->rowid()}})) {
        rollback();
        return nullptr;
    }

    int index = 0;
    for (Field* field : element->fields()) {
        if (!storage().executeQuery(mInsertFieldsQuery,
                                    QVariantMap{{":index", index},
                                                {":element", element->rowid()},
                                                {":field", field->rowid()}})) {
            rollback();
            return nullptr;
        }
        ++index;
    }

    if (myTransaction) {
        commit();
        element->setModified(false);
    }

    return element;
}

template<>
inline Element* StorageImpl<Element, Storage>::update(Element* element)
{
    if (!element) {
        storage().handleError("");
        return nullptr;
    }

    bool myTransaction = transaction();

    // if (!storage().executeQuery(mUpdateQuery, QVariantMap{{":id", element->rowid()}})) {
    //     storage().handleError("");
    //     return nullptr;
    // }

    if (!storage().executeQuery("DELETE FROM `Element_fields` WHERE `element`=:element",
                                QVariantMap{{":element", element->rowid()}})) {
        storage().handleError("");
        rollback();
        return nullptr;
    }

    for (Field* field : element->fields())
        field->save(true);

    int index = 0;
    for (Field* field : element->fields()) {
        if (!storage().executeQuery(mInsertFieldsQuery,
                                    QVariantMap{{":index", index},
                                                {":element", element->rowid()},
                                                {":field", field->rowid()}})) {
            storage().handleError("");
            rollback();
            return nullptr;
        }
        ++index;
    }

    if (myTransaction) {
        commit();
        element->setModified(false);
    }

    return element;
}

template<>
inline void StorageImpl<Value, Storage>::createTables()
{
    storage().executeQuery("CREATE TABLE IF NOT EXISTS `Value` (\n"
                           "  `id`	      INTEGER NOT NULL UNIQUE,\n"
                           "  `valueType` INTEGER NOT NULL,\n"
                           "  `value`     TEXT,\n"
                           "  PRIMARY KEY(`id`),\n"
                           "  FOREIGN KEY(`id`) REFERENCES Storable(`id`) ON DELETE CASCADE\n"
                           ")");
}

template<>
inline void StorageImpl<Value, Storage>::updateQueries()
{
    mReloadQuery = storage().createQuery("SELECT * FROM `Value` WHERE `id`=:id");
    mReloadFieldsQuery = storage().createQuery(
        "SELECT * FROM `Field_values` WHERE `value`=:value ORDER BY `index`");
    mInsertQuery = storage().createQuery(
        "INSERT INTO `Value` (`id`,`valueType`,`value`) VALUES (:id,:valueType,:value)");
    mUpdateQuery = storage().createQuery(
        "UPDATE `Value` SET `valueType`=:valueType,`value`=:value WHERE `id`=:id");
}

template<>
inline Value* StorageImpl<Value, Storage>::construct(const QString& name)
{
    return new Value{qobject_cast<ValueType*>(
                         storage().nodeType(Storable::Type_ValueType,
                                            name.isEmpty() ? "ValueType" : name)),
                     &storage()};
}

template<>
inline Value* StorageImpl<Value, Storage>::reload(Value* value, int rowid)
{
    if (!value)
        return nullptr;

    if (!storage().reload<Node>(value, rowid))
        return nullptr;

    if (!storage().executeQuery(mReloadQuery, {value->rowid()}))
        return nullptr;

    if (!mReloadQuery.next())
        return nullptr;

    value->setValue(mReloadQuery.value("value"));
    value->setValueType(mReloadQuery.value("valueType").toInt());

    if (!storage().executeQuery(mReloadFieldsQuery, QVariantMap{{":value", value->rowid()}})) {
        storage().handleError("");
        return nullptr;
    }

    QList<Field*> fields;
    // fields.reserve(mReloadFieldsQuery.size());
    while (mReloadFieldsQuery.next())
        if (Field* field = qobject_cast<Field*>(
                storage().get(mReloadFieldsQuery.value("field").toInt())))
            fields.append(field);
        else
            storage().handleError("");

    value->setFields(fields);

    return value;
}

template<>
inline Value* StorageImpl<Value, Storage>::insert(Value* value)
{
    if (!value) {
        rollback();
        return nullptr;
    }

    bool myTransaction = transaction();

    if (!storage().insert<Node>(value)) {
        rollback();
        return nullptr;
    }

    if (!storage().executeQuery(mInsertQuery,
                                QVariantMap{{":id", value->rowid()},
                                            {":value", value->value()},
                                            {":valueType", value->valueType()}})) {
        rollback();
        return nullptr;
    }

    if (myTransaction) {
        commit();
        value->setModified(false);
    }

    return value;
}

template<>
inline Value* StorageImpl<Value, Storage>::update(Value* value)
{
    if (!value) {
        storage().handleError("");
        return nullptr;
    }

    bool myTransaction = transaction();

    if (!storage().executeQuery(mUpdateQuery,
                                QVariantMap{{":value", value->value()},
                                            {":id", value->rowid()},
                                            {":valueType", value->valueType()}})) {
        storage().handleError("");
        return nullptr;
    }

    if (!storage().executeQuery("DELETE FROM `Field_values` WHERE `field`=:field",
                                QVariantMap{{":field", value->rowid()}})) {
        storage().handleError("");
        rollback();
        return nullptr;
    }

    if (myTransaction) {
        commit();
        value->setModified(false);
    }

    return value;
}

template<>
inline void StorageImpl<NodeType, Storage>::createTables()
{
    storage().executeQuery("CREATE TABLE IF NOT EXISTS `NodeType` (\n"
                           "  `id`	   INTEGER NOT NULL UNIQUE,\n"
                           "  PRIMARY KEY(`id`),\n"
                           "  FOREIGN KEY(`id`) REFERENCES Storable(`id`) ON DELETE CASCADE\n"
                           ")");
}

template<>
inline void StorageImpl<NodeType, Storage>::updateQueries()
{
    mReloadQuery = storage().createQuery("SELECT * FROM `NodeType` WHERE `id`=:id");
    mInsertQuery = storage().createQuery("INSERT INTO `NodeType` (`id`) VALUES (:id)");
    mUpdateQuery = storage().createQuery("UPDATE `NodeType` SET `id`=:id WHERE `id`=:id");
}

template<>
inline NodeType* StorageImpl<NodeType, Storage>::construct(const QString& name)
{
    return nullptr;
}

template<>
inline NodeType* StorageImpl<NodeType, Storage>::reload(NodeType* nodeType, int rowid)
{
    if (!nodeType)
        return nullptr;

    if (!storage().reload<Node>(nodeType, rowid))
        return nullptr;

    if (!storage().executeQuery(mReloadQuery, QVariantMap{{":id", nodeType->rowid()}}))
        return nullptr;

    if (!mReloadQuery.next())
        return nullptr;

    return nodeType;
}

template<>
inline NodeType* StorageImpl<NodeType, Storage>::insert(NodeType* nodeType)
{
    if (!nodeType) {
        rollback();
        return nullptr;
    }

    bool myTransaction = transaction();

    if (!storage().insert<Node>(nodeType)) {
        rollback();
        return nullptr;
    }

    if (!storage().executeQuery(mInsertQuery,
                                QVariantMap{{":id", nodeType->rowid()}/*,
                                            {":name", nodeType->name()},
                                            {":label", nodeType->label()}*/})) {
        rollback();
        return nullptr;
    }

    if (myTransaction) {
        commit();
        nodeType->setModified(false);
    }

    return nodeType;
}

template<>
inline NodeType* StorageImpl<NodeType, Storage>::update(NodeType* nodeType)
{
    if (!nodeType) {
        storage().handleError("");
        return nullptr;
    }

    bool myTransaction = transaction();

    // if (!storage().executeQuery(mUpdateQuery, QVariantMap{{":id", nodeType->rowid()}})) {
    //     storage().handleError("");
    //     return nullptr;
    // }

    if (myTransaction) {
        commit();
        nodeType->setModified(false);
    }

    return nodeType;
}

template<>
inline void StorageImpl<FieldType, Storage>::createTables()
{
    storage().executeQuery("CREATE TABLE IF NOT EXISTS `FieldType` (\n"
                           "  `id` INTEGER NOT NULL UNIQUE,\n"
                           "  `minOccurs` INTEGER NOT NULL,\n"
                           "  `maxOccurs` INTEGER NOT NULL,\n"
                           "  PRIMARY KEY(`id`),\n"
                           "  FOREIGN KEY(`id`) REFERENCES Storable(`id`) ON DELETE CASCADE\n"
                           ")");
    storage().executeQuery("CREATE TABLE IF NOT EXISTS `FieldType_valueTypes` (\n"
                           "  `id`	        INTEGER NOT NULL UNIQUE,\n"
                           "  `index`	    INTEGER NOT NULL,\n"
                           "  `fieldType` INTEGER NOT NULL,\n"
                           "  `valueType`   INTEGER NOT NULL,\n"
                           "  PRIMARY KEY(`id` AUTOINCREMENT)\n"
                           ")");
    storage().executeQuery("CREATE INDEX IF NOT EXISTS idx_FieldType_valueTypes_fieldType ON "
                           "FieldType_valueTypes(fieldType)");
    storage().executeQuery("CREATE INDEX IF NOT EXISTS idx_FieldType_valueTypes_valueType ON "
                           "FieldType_valueTypes(valueType)");
    storage().executeQuery("CREATE TABLE IF NOT EXISTS `FieldType_allowedTypes` (\n"
                           "  `id`	        INTEGER NOT NULL UNIQUE,\n"
                           "  `index`	    INTEGER NOT NULL,\n"
                           "  `fieldType`   INTEGER NOT NULL,\n"
                           "  `type`        INTEGER NOT NULL,\n"
                           "  PRIMARY KEY(`id` AUTOINCREMENT)\n"
                           ")");
    storage().executeQuery("CREATE INDEX IF NOT EXISTS idx_FieldType_allowedTypes_field ON "
                           "FieldType_allowedTypes(fieldType)");
    storage().executeQuery("CREATE INDEX IF NOT EXISTS idx_FieldType_allowedTypes_type ON "
                           "FieldType_allowedTypes(type)");
}

template<>
inline void StorageImpl<FieldType, Storage>::updateQueries()
{
    mReloadQuery = storage().createQuery("SELECT * FROM `FieldType` WHERE `id`=:id");
    mReloadElementTypesQuery = storage().createQuery(
        "SELECT * FROM `ElementType_fieldTypes` WHERE `fieldType`=:fieldType ORDER BY `index`");
    mInsertQuery = storage().createQuery("INSERT INTO `FieldType` (`id`,`minOccurs`,`maxOccurs`) "
                                         "VALUES (:id,:minOccurs,:maxOccurs)");
    mUpdateQuery = storage().createQuery(
        "UPDATE `FieldType` SET `minOccurs`=:minOccurs,`maxOccurs`=:maxOccurs WHERE "
        "`id`=:id");
    mReloadValueTypesQuery = storage().createQuery(
        "SELECT * FROM `FieldType_valueTypes` WHERE `fieldType`=:fieldType ORDER BY `index`");
    mInsertValueTypesQuery = storage().createQuery(
        "INSERT INTO `FieldType_valueTypes` (`index`,`fieldType`,`valueType`) VALUES "
        "(:index,:fieldType,:valueType)");

    mReloadAllowedTypesQuery = storage().createQuery(
        "SELECT * FROM `FieldType_allowedTypes` WHERE `fieldType`=:fieldType ORDER BY `index`");
    mInsertAllowedTypesQuery = storage().createQuery(
        "INSERT INTO `FieldType_allowedTypes` (`index`,`fieldType`,`type`) VALUES "
        "(:index,:fieldType,:type)");
}

template<>
inline FieldType* StorageImpl<FieldType, Storage>::construct(const QString& name)
{
    return new FieldType{&storage()};
}

template<>
inline FieldType* StorageImpl<FieldType, Storage>::reload(FieldType* fieldType, int rowid)
{
    if (!fieldType) {
        storage().handleError("");
        return nullptr;
    }

    if (!storage().reload<NodeType>(fieldType, rowid)) {
        storage().handleError("");
        return nullptr;
    }

    if (!storage().executeQuery(mReloadQuery, QVariantMap{{":id", fieldType->rowid()}})) {
        storage().handleError("");
        return nullptr;
    }

    if (!mReloadQuery.next()) {
        storage().handleError("");
        return nullptr;
    }

    fieldType->setMinOccurs(mReloadQuery.value("minOccurs").toInt());
    fieldType->setMaxOccurs(mReloadQuery.value("maxOccurs").toInt());

    if (!storage().executeQuery(mReloadElementTypesQuery,
                                QVariantMap{{":fieldType", fieldType->rowid()}})) {
        storage().handleError("");
        return nullptr;
    }

    QList<ElementType*> elementTypes;
    // elementTypes.reserve(mReloadElementTypesQuery.size());
    while (mReloadElementTypesQuery.next())
        if (ElementType* elementType = qobject_cast<ElementType*>(
                storage().get(mReloadElementTypesQuery.value("elementType").toInt())))
            elementTypes.append(elementType);
        else
            storage().handleError("");

    fieldType->setElementTypes(elementTypes);

    if (!storage().executeQuery(mReloadValueTypesQuery,
                                QVariantMap{{":fieldType", fieldType->rowid()}})) {
        storage().handleError("");
        return nullptr;
    }

    QList<ValueType*> valueTypes;
    // valueTypes.reserve(mReloadValueTypesQuery.size());
    while (mReloadValueTypesQuery.next())
        if (ValueType* valueType = qobject_cast<ValueType*>(
                storage().get(mReloadValueTypesQuery.value("valueType").toInt())))
            valueTypes.append(valueType);
        else
            storage().handleError("");

    fieldType->setValueTypes(valueTypes);

    if (!storage().executeQuery(mReloadAllowedTypesQuery,
                                QVariantMap{{":fieldType", fieldType->rowid()}})) {
        storage().handleError("");
        return nullptr;
    }

    QList<int> allowedTypes;
    while (mReloadAllowedTypesQuery.next())
        if (int type = mReloadAllowedTypesQuery.value("type").toInt(); type > 0)
            allowedTypes.append(type);
        else
            storage().handleError("");

    fieldType->setAllowedTypes(allowedTypes);

    return fieldType;
}

template<>
inline FieldType* StorageImpl<FieldType, Storage>::insert(FieldType* fieldType)
{
    if (!fieldType) {
        storage().handleError("");
        rollback();
        return nullptr;
    }

    bool myTransaction = transaction();

    if (!storage().insert<NodeType>(fieldType)) {
        storage().handleError("");
        rollback();
        return nullptr;
    }

    for (ValueType* valueType : fieldType->valueTypes())
        valueType->save();

    if (!storage().executeQuery(mInsertQuery,
                                QVariantMap{{":id", fieldType->rowid()},
                                            {":minOccurs", fieldType->minOccurs()},
                                            {":maxOccurs", fieldType->maxOccurs()}})) {
        storage().handleError("");
        rollback();
        return nullptr;
    }

    int index = 0;
    for (ValueType* valueType : fieldType->valueTypes()) {
        if (!storage().executeQuery(mInsertValueTypesQuery,
                                    QVariantMap{{":index", index},
                                                {":fieldType", fieldType->rowid()},
                                                {":valueType", valueType->rowid()}})) {
            storage().handleError("");
            rollback();
            return nullptr;
        }
        ++index;
    }

    index = 0;
    for (int type : fieldType->allowedTypes()) {
        if (!storage().executeQuery(mInsertAllowedTypesQuery,
                                    QVariantMap{{":index", index},
                                                {":fieldType", fieldType->rowid()},
                                                {":type", type}})) {
            rollback();
            return nullptr;
        }
        ++index;
    }

    if (myTransaction) {
        commit();
        fieldType->setModified(false);
    }

    return fieldType;
}

template<>
inline FieldType* StorageImpl<FieldType, Storage>::update(FieldType* fieldType)
{
    if (!fieldType) {
        storage().handleError("");
        rollback();
        return nullptr;
    }

    bool myTransaction = transaction();

    if (!storage().update<NodeType>(fieldType)) {
        storage().handleError("");
        rollback();
        return nullptr;
    }

    if (!storage().executeQuery(mInsertQuery,
                                QVariantMap{{":minOccurs", fieldType->minOccurs()},
                                            {":maxOccurs", fieldType->maxOccurs()},
                                            {":id", fieldType->rowid()}})) {
        storage().handleError("");
        rollback();
        return nullptr;
    }

    for (ValueType* valueType : fieldType->valueTypes())
        valueType->save();

    if (!storage().executeQuery("DELETE FROM `FieldType_valueTypes` WHERE `fieldType`=:fieldType",
                                QVariantMap{{":fieldType", fieldType->rowid()}})) {
        storage().handleError("");
        rollback();
        return nullptr;
    }

    int index = 0;
    for (ValueType* valueType : fieldType->valueTypes()) {
        if (!storage().executeQuery(mInsertValueTypesQuery,
                                    QVariantMap{{":index", index},
                                                {":fieldType", fieldType->rowid()},
                                                {":valueType", valueType->rowid()}})) {
            storage().handleError("");
            rollback();
            return nullptr;
        }
        ++index;
    }

    if (!storage().executeQuery("DELETE FROM `FieldType_allowedTypes` WHERE `fieldType`=:fieldType",
                                QVariantMap{{":fieldType", fieldType->rowid()}})) {
        storage().handleError("");
        rollback();
        return nullptr;
    }

    index = 0;
    for (int type : fieldType->allowedTypes()) {
        if (!storage().executeQuery(mInsertAllowedTypesQuery,
                                    QVariantMap{{":index", index},
                                                {":fieldType", fieldType->rowid()},
                                                {":type", type}})) {
            rollback();
            return nullptr;
        }
        ++index;
    }

    if (myTransaction) {
        commit();
        fieldType->setModified(false);
    }

    return fieldType;
}

template<>
inline void StorageImpl<ElementType, Storage>::createTables()
{
    storage().executeQuery("CREATE TABLE IF NOT EXISTS `ElementType` (\n"
                           "  `id`          INTEGER NOT NULL UNIQUE,\n"
                           "  PRIMARY KEY(`id`),\n"
                           "  FOREIGN KEY(`id`) REFERENCES Storable(`id`) ON DELETE CASCADE\n"
                           ")");
    storage().executeQuery("CREATE TABLE IF NOT EXISTS `ElementType_fieldTypes` (\n"
                           "  `id`	        INTEGER NOT NULL UNIQUE,\n"
                           "  `index`	    INTEGER NOT NULL,\n"
                           "  `elementType` INTEGER NOT NULL,\n"
                           "  `fieldType`   INTEGER NOT NULL,\n"
                           "  PRIMARY KEY(`id` AUTOINCREMENT)\n"
                           ")");
    storage().executeQuery("CREATE INDEX IF NOT EXISTS idx_ElementType_fieldTypes_elementType ON "
                           "ElementType_fieldTypes(elementType)");
    storage().executeQuery("CREATE INDEX IF NOT EXISTS idx_ElementType_fieldTypes_fieldType ON "
                           "ElementType_fieldTypes(fieldType)");
}

template<>
inline void StorageImpl<ElementType, Storage>::updateQueries()
{
    mReloadQuery = storage().createQuery("SELECT * FROM `ElementType` WHERE `id`=:id");
    mReloadFieldTypesQuery = storage().createQuery(
        "SELECT * FROM `ElementType_fieldTypes` WHERE `elementType`=:elementType ORDER BY `index`");
    mInsertQuery = storage().createQuery("INSERT INTO `ElementType` (`id`) VALUES (:id)");
    mInsertFieldTypesQuery = storage().createQuery(
        "INSERT INTO `ElementType_fieldTypes` (`index`,`elementType`,`fieldType`) VALUES "
        "(:index,:elementType,:fieldType)");
    mUpdateQuery = storage().createQuery("UPDATE `ElementType` SET `id`=:id WHERE `id`=:id");
    mUpdateFieldTypesQuery = storage().createQuery(
        "UPDATE `ElementType_fieldTypes` SET "
        "`index`=:index,`elementType`=:elementType,`fieldType`=:fieldType WHERE `id`=:id");
}

template<>
inline ElementType* StorageImpl<ElementType, Storage>::construct(const QString& name)
{
    return new ElementType{&storage()};
}

template<>
inline ElementType* StorageImpl<ElementType, Storage>::reload(ElementType* elementType, int rowid)
{
    if (!elementType) {
        storage().handleError("");
        return nullptr;
    }

    if (!storage().reload<NodeType>(elementType, rowid)) {
        storage().handleError("");
        return nullptr;
    }

    if (!storage().executeQuery(mReloadQuery, QVariantMap{{":id", elementType->rowid()}})) {
        storage().handleError("");
        return nullptr;
    }

    if (!mReloadQuery.next()) {
        storage().handleError("");
        return nullptr;
    }

    if (!storage().executeQuery(mReloadFieldTypesQuery,
                                QVariantMap{{":elementType", elementType->rowid()}})) {
        storage().handleError("");
        return nullptr;
    }

    QList<FieldType*> fieldTypes;
    // fieldTypes.reserve(mReloadFieldTypesQuery.size());
    while (mReloadFieldTypesQuery.next())
        if (FieldType* fieldType = qobject_cast<FieldType*>(
                storage().get(mReloadFieldTypesQuery.value("fieldType").toInt())))
            fieldTypes.append(fieldType);
        else
            storage().handleError("");

    elementType->setFieldTypes(fieldTypes);

    return elementType;
}

template<>
inline ElementType* StorageImpl<ElementType, Storage>::insert(ElementType* elementType)
{
    if (!elementType) {
        storage().handleError("");
        rollback();
        return nullptr;
    }

    bool myTransaction = transaction();

    if (!storage().insert<NodeType>(elementType)) {
        storage().handleError("");
        rollback();
        return nullptr;
    }

    for (FieldType* fieldType : elementType->fieldTypes())
        fieldType->save(true);

    if (!storage().executeQuery(mInsertQuery, QVariantMap{{":id", elementType->rowid()}})) {
        storage().handleError("");
        rollback();
        return nullptr;
    }

    int index = 0;
    for (FieldType* fieldType : elementType->fieldTypes()) {
        if (!storage().executeQuery(mInsertFieldTypesQuery,
                                    QVariantMap{{":index", index},
                                                {":elementType", elementType->rowid()},
                                                {":fieldType", fieldType->rowid()}})) {
            storage().handleError("");
            rollback();
            return nullptr;
        }
        ++index;
    }

    if (myTransaction) {
        commit();
        elementType->setModified(false);
    }

    return elementType;
}

template<>
inline ElementType* StorageImpl<ElementType, Storage>::update(ElementType* elementType)
{
    if (!elementType) {
        storage().handleError("");
        rollback();
        return nullptr;
    }

    bool myTransaction = transaction();

    if (!storage().update<NodeType>(elementType)) {
        storage().handleError("");
        rollback();
        return nullptr;
    }

    for (FieldType* fieldType : elementType->fieldTypes())
        fieldType->save(true);

    // if (!storage().executeQuery(mUpdateQuery, QVariantMap{{":id", elementType->rowid()}})) {
    //     storage().handleError("");
    //     rollback();
    //     return nullptr;
    // }

    if (!storage().executeQuery(
            "DELETE FROM `ElementType_fieldTypes` WHERE `elementType`=:elementType",
            QVariantMap{{":elementType", elementType->rowid()}})) {
        storage().handleError("");
        rollback();
        return nullptr;
    }

    int index = 0;
    for (FieldType* fieldType : elementType->fieldTypes()) {
        if (!storage().executeQuery(mInsertFieldTypesQuery,
                                    QVariantMap{{":index", index},
                                                {":elementType", elementType->rowid()},
                                                {":fieldType", fieldType->rowid()}})) {
            storage().handleError("");
            rollback();
            return nullptr;
        }
        ++index;
    }

    if (myTransaction) {
        commit();
        elementType->setModified(false);
    }

    return elementType;
}

template<>
inline void StorageImpl<ValueType, Storage>::createTables()
{
    storage().executeQuery("CREATE TABLE IF NOT EXISTS `ValueType` (\n"
                           "  `id` INTEGER NOT NULL UNIQUE,\n"
                           "  PRIMARY KEY(`id`),\n"
                           "  FOREIGN KEY(`id`) REFERENCES Storable(`id`) ON DELETE CASCADE\n"
                           ")");
}

template<>
inline void StorageImpl<ValueType, Storage>::updateQueries()
{
    mReloadQuery = storage().createQuery("SELECT * FROM `ValueType` WHERE `id`=:id");
    mReloadFieldTypesQuery = storage().createQuery(
        "SELECT * FROM `FieldType_valueTypes` WHERE `valueType`=:valueType ORDER BY `index`");
    mInsertQuery = storage().createQuery("INSERT INTO `ValueType` (`id`) VALUES (:id)");
    mUpdateQuery = storage().createQuery("UPDATE `ValueType` SET `id`=:id WHERE `id`=:id");
}

template<>
inline ValueType* StorageImpl<ValueType, Storage>::construct(const QString& name)
{
    return new ValueType{&storage()};
}

template<>
inline ValueType* StorageImpl<ValueType, Storage>::reload(ValueType* valueType, int rowid)
{
    if (!valueType) {
        storage().handleError("");
        return nullptr;
    }

    if (!storage().reload<NodeType>(valueType, rowid)) {
        storage().handleError("");
        return nullptr;
    }

    if (!storage().executeQuery(mReloadQuery, QVariantMap{{":id", valueType->rowid()}})) {
        storage().handleError("");
        return nullptr;
    }

    if (!mReloadQuery.next()) {
        storage().handleError("");
        return nullptr;
    }

    if (!storage().executeQuery(mReloadFieldTypesQuery,
                                QVariantMap{{":valueType", valueType->rowid()}})) {
        storage().handleError("");
        return nullptr;
    }

    QList<FieldType*> fieldTypes;
    // fieldTypes.reserve(mReloadFieldTypesQuery.size());
    while (mReloadFieldTypesQuery.next())
        if (FieldType* fieldType = qobject_cast<FieldType*>(
                storage().get(mReloadFieldTypesQuery.value("fieldType").toInt())))
            fieldTypes.append(fieldType);
        else
            storage().handleError("");

    valueType->setFieldTypes(fieldTypes);

    return valueType;
}

template<>
inline ValueType* StorageImpl<ValueType, Storage>::insert(ValueType* valueType)
{
    if (!valueType) {
        storage().handleError("");
        rollback();
        return nullptr;
    }

    bool myTransaction = transaction();

    if (!storage().insert<NodeType>(valueType)) {
        storage().handleError("");
        rollback();
        return nullptr;
    }

    if (!storage().executeQuery(mInsertQuery, QVariantMap{{":id", valueType->rowid()}})) {
        storage().handleError("");
        rollback();
        return nullptr;
    }

    if (myTransaction) {
        commit();
        valueType->setModified(false);
    }

    return valueType;
}

template<>
inline ValueType* StorageImpl<ValueType, Storage>::update(ValueType* valueType)
{
    if (!valueType) {
        storage().handleError("");
        rollback();
        return nullptr;
    }

    bool myTransaction = transaction();

    if (!storage().update<NodeType>(valueType)) {
        storage().handleError("");
        rollback();
        return nullptr;
    }

    if (myTransaction) {
        commit();
        valueType->setModified(false);
    }

    return valueType;
}

inline void Storage::createTables()
{
    StorageImpl<Storable, Storage>::createTables();
    StorageImpl<Node, Storage>::createTables();
    StorageImpl<Field, Storage>::createTables();
    StorageImpl<Element, Storage>::createTables();
    StorageImpl<Value, Storage>::createTables();
    StorageImpl<NodeType, Storage>::createTables();
    StorageImpl<FieldType, Storage>::createTables();
    StorageImpl<ElementType, Storage>::createTables();
    StorageImpl<ValueType, Storage>::createTables();
}

inline void Storage::updateQueries()
{
    StorageImpl<Storable, Storage>::updateQueries();
    StorageImpl<Node, Storage>::updateQueries();
    StorageImpl<Field, Storage>::updateQueries();
    StorageImpl<Element, Storage>::updateQueries();
    StorageImpl<Value, Storage>::updateQueries();
    StorageImpl<NodeType, Storage>::updateQueries();
    StorageImpl<FieldType, Storage>::updateQueries();
    StorageImpl<ElementType, Storage>::updateQueries();
    StorageImpl<ValueType, Storage>::updateQueries();
}

#endif // _LIBNOVELIST_STORAGE_H
