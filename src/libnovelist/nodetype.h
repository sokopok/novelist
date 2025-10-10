#ifndef NOVELIST_NODETYPE_H
#define NOVELIST_NODETYPE_H

#include "element.h"
#include "field.h"
#include "node.h"

namespace novelist {

class NodeType : public QObject
{
    Q_OBJECT

public:
    NodeType(QObject *parent = nullptr);

    [[nodiscard]] virtual bool isElementType() const { return false; }
    [[nodiscard]] virtual bool isFieldType() const { return false; }

    [[nodiscard]] QString table() const { return mTable; }
    void setTable(const QString &table);

    [[nodiscard]] QString name() const { return mName; }
    void setName(const QString &name);

    [[nodiscard]] QString label() const { return mLabel; }
    void setLabel(const QString &label);

    [[nodiscard]] QString description() const { return mDescription; }
    void setDescription(const QString &description);

    [[nodiscard]] QString icon() const { return mIcon; }
    void setIcon(const QString &icon);

    virtual Node *create(QObject *parent = nullptr) = 0;
    virtual bool createTable() = 0;

signals:
    void tableChanged();
    void nameChanged();
    void labelChanged();
    void descriptionChanged();
    void iconChanged();

private:
    QString mTable;
    QString mName;
    QString mLabel;
    QString mDescription;
    QString mIcon;

    Q_PROPERTY(QString table READ table WRITE setTable NOTIFY tableChanged FINAL)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged FINAL)
    Q_PROPERTY(
        QString description READ description WRITE setDescription NOTIFY descriptionChanged FINAL)
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged FINAL)
};

class ElementType : public NodeType
{
    Q_OBJECT

public:
    ElementType(QObject *parent = nullptr);

    [[nodiscard]] bool isElementType() const override { return true; }

    Element *create(QObject *parent = nullptr) override;

    bool createTable() override;
};

class FieldType : public NodeType
{
    Q_OBJECT

public:
    FieldType(QObject *parent = nullptr);

    [[nodiscard]] bool isFieldType() const override { return true; }

    Field *create(QObject *parent = nullptr) override;

    bool createTable() override;

    [[nodiscard]] QVariant defaultValue() const { return mDefaultValue; }
    void setDefaultValue(const QVariant &defaultValue);

signals:
    void defaultValueChanged();

private:
    QVariant mDefaultValue;

    Q_PROPERTY(QVariant defaultValue READ defaultValue WRITE setDefaultValue NOTIFY
                   defaultValueChanged FINAL)
};

} // namespace novelist

#endif // NOVELIST_NODETYPE_H
