#ifndef ELEMENTTYPETABLEMODEL_H
#define ELEMENTTYPETABLEMODEL_H

#include <QAbstractItemModel>
#include <QQmlEngine>

class ElementType;
class Node;

class ElementTypeTableModel : public QAbstractItemModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum Role {};
    enum ItemFlag {
        DefaultItemFlags = Qt::ItemIsSelectable | Qt::ItemIsEnabled,
        ItemIsHidden = Qt::ItemIsUserTristate << 1
    };

    explicit ElementTypeTableModel(QObject *parent = nullptr);

    // QVariant headerData(int section,
    //                     Qt::Orientation orientation,
    //                     int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    [[nodiscard]] QList<ElementType *> elementTypes() const { return mElementTypes; }
    void setElementTypes(const QList<ElementType *> &elementTypes);

signals:
    void elementTypesChanged();

private:
    QList<ElementType *> mElementTypes;

    Q_PROPERTY(QList<ElementType *> elementTypes READ elementTypes WRITE setElementTypes NOTIFY
                   elementTypesChanged FINAL)

    struct Row;
    struct Item
    {
        Item(Row *row, Node *node = nullptr, int flags = DefaultItemFlags)
            : row{row}
            , node{node}
            , flags{flags}
        {}
        Item(Node *node = nullptr, int flags = DefaultItemFlags)
            : node{node}
            , flags{flags}
        {}

        Row *row = nullptr;
        Node *node = nullptr;
        int flags = DefaultItemFlags;

        void clear();
        void appendChild(Item *child);
        void appendRow(Row *row);
    };
    struct Row
    {
        Node *node = nullptr;
        QList<Item *> columns = {};
        int flags = DefaultItemFlags;

        void clear();
        void appendChild(Item *child);
    };
    QList<Row *> mRows;
    int mColumnCount = 1;

    void appendRow(Node *node, QList<Item *> items)
    {
        Row *row = new Row;
        for (int i = 0, n = items.size(); i < n; ++i)
            items[i]->row = row;
        for (int i = items.size(), n = columnCount(); i < n; ++i)
            items.append(new Item{row, nullptr, Qt::NoItemFlags});
        row->columns = items;
        row->node = node;
        mRows.append(row);
    }
};

#endif // ELEMENTTYPETABLEMODEL_H
