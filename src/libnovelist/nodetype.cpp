#include "nodetype.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "element.h"
#include "field.h"

namespace novelist {

NodeType::NodeType(QObject *parent)
    : QObject{parent}
{}

void NodeType::setTable(const QString &table)
{
    if (mTable == table)
        return;
    mTable = table;
    emit tableChanged();
}

Node *NodeType::create(QObject *parent)
{
    if (isElementType())
        return new Element{parent};

    if (isFieldType())
        return new Field{parent};

    return nullptr;
}

void NodeType::setName(const QString &name)
{
    if (mName == name)
        return;
    mName = name;
    emit nameChanged();
}

void NodeType::setLabel(const QString &label)
{
    if (mLabel == label)
        return;
    mLabel = label;
    emit labelChanged();
}

void NodeType::setDescription(const QString &description)
{
    if (mDescription == description)
        return;
    mDescription = description;
    emit descriptionChanged();
}

void NodeType::setIcon(const QString &icon)
{
    if (mIcon == icon)
        return;
    mIcon = icon;
    emit iconChanged();
}

bool ElementType::createTable()
{
    QSqlQuery(QStringLiteral("CREATE TABLE `%1` ("
                             "`rowid`           INTEGER NOT NULL UNIQUE,"
                             "`label`           TEXT,"
                             "`description`     TEXT,"
                             "`icon`            TEXT,"
                             "PRIMARY KEY(`rowid` AUTOINCREMENT)"
                             ")")
                  .arg(table()));

    return true;
}

bool FieldType::createTable()
{
    QSqlQuery(QStringLiteral("CREATE TABLE `%1` ("
                             "`rowid`           INTEGER NOT NULL UNIQUE,"
                             "`label`           TEXT,"
                             "`description`     TEXT,"
                             "`icon`            TEXT,"
                             "`default`         BLOB,"
                             "`value`           BLOB,"
                             "PRIMARY KEY(`rowid` AUTOINCREMENT)"
                             ")")
                  .arg(table()));

    return true;
}

void FieldType::setDefaultValue(const QVariant &defaultValue)
{
    if (mDefaultValue == defaultValue)
        return;
    mDefaultValue = defaultValue;
    emit defaultValueChanged();
}

} // namespace novelist
