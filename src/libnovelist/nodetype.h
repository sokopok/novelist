#ifndef NOVELIST_NODETYPE_H
#define NOVELIST_NODETYPE_H

#include <QObject>

namespace novelist {

class Node;

class NodeType : public QObject
{
    Q_OBJECT

public:
    NodeType(QObject *parent = nullptr);

    [[nodiscard]] int type() const { return mType; }
    void setType(int type);

    [[nodiscard]] static bool isElementType(int type) { return type & 0x01000000; }
    [[nodiscard]] static bool isFieldType(int type) { return type & 0x01000000; }

    [[nodiscard]] bool isElementType() const { return isElementType(mType); }
    [[nodiscard]] bool isFieldType() const { return isFieldType(mType); }

    [[nodiscard]] QString table() const { return mTable; }
    void setTable(const QString &table);

    Node *create(QObject *parent = nullptr);

signals:
    void typeChanged();
    void tableChanged();

private:
    int mType = 0;
    QString mTable;

    Q_PROPERTY(QString table READ table WRITE setTable NOTIFY tableChanged FINAL)
    Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged FINAL)
};

} // namespace novelist

#endif // NOVELIST_NODETYPE_H
