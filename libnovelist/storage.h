#ifndef LIBNOVELIST_STORAGE_H
#define LIBNOVELIST_STORAGE_H

#include <QObject>

#include "elementstorage.h"
#include "elementtypestorage.h"
#include "fieldstorage.h"
#include "fieldtypestorage.h"
#include "projectstorage.h"
#include "projecttypestorage.h"
#include "valuestorage.h"
#include "valuetypestorage.h"

class Storage : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Storage(QObject* parent = nullptr)
        : QObject{parent}
        , mNodeStorage{new NodeStorage{this}}
        , mNodeTypeStorage{new NodeTypeStorage{this}}
        , mElementStorage{new ElementStorage{this}}
        , mElementTypeStorage{new ElementTypeStorage{this}}
        , mFieldStorage{new FieldStorage{this}}
        , mFieldTypeStorage{new FieldTypeStorage{this}}
        , mValueStorage{new ValueStorage{this}}
        , mValueTypeStorage{new ValueTypeStorage{this}}
        , mProjectStorage{new ProjectStorage{this}}
        , mProjectTypeStorage{new ProjectTypeStorage{this}}
    {}
    [[nodiscard]] QSqlDatabase database() const { return mDatabase; }
    void setDatabase(const QSqlDatabase& database)
    {
        mDatabase = database;

        mNodeStorage->setDatabase(mDatabase);
        mNodeTypeStorage->setDatabase(mDatabase);
        mElementStorage->setDatabase(mDatabase);
        mElementTypeStorage->setDatabase(mDatabase);
        mFieldStorage->setDatabase(mDatabase);
        mFieldTypeStorage->setDatabase(mDatabase);
        mValueStorage->setDatabase(mDatabase);
        mValueTypeStorage->setDatabase(mDatabase);
        mProjectStorage->setDatabase(mDatabase);
        mProjectTypeStorage->setDatabase(mDatabase);

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

    [[nodiscard]] Node* node() { return mNodeStorage->node(); }
    [[nodiscard]] Node* node(int rowid) { return mNodeStorage->node(rowid); }

    [[nodiscard]] NodeType* nodeType() { return mNodeTypeStorage->nodeType(); }
    [[nodiscard]] NodeType* nodeType(int rowid) { return mNodeTypeStorage->nodeType(rowid); }

    [[nodiscard]] Element* element() { return mElementStorage->element(); }
    [[nodiscard]] Element* element(int rowid) { return mElementStorage->element(rowid); }

    [[nodiscard]] Field* field() { return mFieldStorage->field(); }
    [[nodiscard]] Field* field(int rowid) { return mFieldStorage->field(rowid); }

    [[nodiscard]] Value* value() { return mValueStorage->value(); }
    [[nodiscard]] Value* value(int rowid) { return mValueStorage->value(rowid); }

    [[nodiscard]] ElementType* elementType() { return mElementTypeStorage->elementType(); }
    [[nodiscard]] ElementType* elementType(int rowid)
    {
        return mElementTypeStorage->elementType(rowid);
    }

    [[nodiscard]] FieldType* fieldType() { return mFieldTypeStorage->fieldType(); }
    [[nodiscard]] FieldType* fieldType(int rowid) { return mFieldTypeStorage->fieldType(rowid); }

    [[nodiscard]] ValueType* valueType() { return mValueTypeStorage->valueType(); }
    [[nodiscard]] ValueType* valueType(int rowid) { return mValueTypeStorage->valueType(rowid); }

    [[nodiscard]] NodeStorage* nodeStorage() const { return mNodeStorage; }
    [[nodiscard]] NodeTypeStorage* nodeTypeStorage() const { return mNodeTypeStorage; }
    [[nodiscard]] ElementStorage* elementStorage() const { return mElementStorage; }
    [[nodiscard]] ElementTypeStorage* elementTypeStorage() const { return mElementTypeStorage; }
    [[nodiscard]] FieldStorage* fieldStorage() const { return mFieldStorage; }
    [[nodiscard]] FieldTypeStorage* fieldTypeStorage() const { return mFieldTypeStorage; }
    [[nodiscard]] ValueStorage* valueStorage() const { return mValueStorage; }
    [[nodiscard]] ValueTypeStorage* valueTypeStorage() const { return mValueTypeStorage; }
    [[nodiscard]] ProjectStorage* projectStorage() const { return mProjectStorage; }
    [[nodiscard]] ProjectTypeStorage* projectTypeStorage() const { return mProjectTypeStorage; }

    [[nodiscard]] int& transactionDepth() { return mTransactionDepth; }

signals:
    void databaseChanged(QPrivateSignal);
    void databaseNameChanged(QPrivateSignal);
    void databaseConnectionNameChanged(QPrivateSignal);

private:
    QSqlDatabase mDatabase;
    QString mDatabaseName;
    QString mDatabaseConnectionName;

    NodeStorage* mNodeStorage = nullptr;
    NodeTypeStorage* mNodeTypeStorage = nullptr;
    ElementStorage* mElementStorage = nullptr;
    ElementTypeStorage* mElementTypeStorage = nullptr;
    FieldStorage* mFieldStorage = nullptr;
    FieldTypeStorage* mFieldTypeStorage = nullptr;
    ValueStorage* mValueStorage = nullptr;
    ValueTypeStorage* mValueTypeStorage = nullptr;
    ProjectStorage* mProjectStorage = nullptr;
    ProjectTypeStorage* mProjectTypeStorage = nullptr;

    int mTransactionDepth = -1;

    Q_PROPERTY(ElementStorage* elementStorage READ elementStorage CONSTANT FINAL)
    Q_PROPERTY(ElementTypeStorage* elementTypeStorage READ elementTypeStorage CONSTANT FINAL)
    Q_PROPERTY(FieldStorage* fieldStorage READ fieldStorage CONSTANT FINAL)
    Q_PROPERTY(FieldTypeStorage* fieldTypeStorage READ fieldTypeStorage CONSTANT FINAL)
    Q_PROPERTY(ValueStorage* valueStorage READ valueStorage CONSTANT FINAL)
    Q_PROPERTY(ValueTypeStorage* valueTypeStorage READ valueTypeStorage CONSTANT FINAL)
    Q_PROPERTY(ProjectStorage* projectStorage READ projectStorage CONSTANT FINAL)
    Q_PROPERTY(ProjectTypeStorage* projectTypeStorage READ projectTypeStorage CONSTANT FINAL)
    Q_PROPERTY(QString databaseName READ databaseName WRITE setDatabaseName NOTIFY
                   databaseNameChanged FINAL)
    Q_PROPERTY(QString databaseConnectionName READ databaseConnectionName WRITE
                   setDatabaseConnectionName NOTIFY databaseConnectionNameChanged FINAL)
};

#endif // LIBNOVELIST_STORAGE_H
