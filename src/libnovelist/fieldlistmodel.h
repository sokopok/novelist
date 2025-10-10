#ifndef NOVELIST_FIELDLISTMODEL_H
#define NOVELIST_FIELDLISTMODEL_H

#include <QAbstractListModel>
#include <QQmlEngine>

namespace novelist {

class Element;

class FieldListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role { LabelRole = Qt::UserRole + 1, ValueRole };

    explicit FieldListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roleNames = QAbstractListModel::roleNames();
        roleNames[LabelRole] = "label";
        roleNames[ValueRole] = "value";
        return roleNames;
    }

    [[nodiscard]] Element *element() const { return mElement; }
    void setElement(Element *element);

signals:
    void elementChanged();
    void rowCountChanged();

private:
    Element *mElement = nullptr;

    Q_PROPERTY(Element *element READ element WRITE setElement NOTIFY elementChanged FINAL)
    Q_PROPERTY(int rowCount READ rowCount NOTIFY rowCountChanged FINAL)
};

} // namespace novelist

#endif // NOVELIST_FIELDLISTMODEL_H
