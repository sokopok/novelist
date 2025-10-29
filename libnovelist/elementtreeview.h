#ifndef ELEMENTTREEVIEW_H
#define ELEMENTTREEVIEW_H

#include <QAbstractItemModel>

class Element;

class ElementTreeView : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit ElementTreeView(QObject *parent = nullptr);

    QModelIndex index(int row,
                      int column = 0,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    Element *mRoot;
};

#endif // ELEMENTTREEVIEW_H
