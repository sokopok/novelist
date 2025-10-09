#ifndef NOVELIST_ELEMENT_H
#define NOVELIST_ELEMENT_H

#include <QObject>
#include "fieldlistmodel.h"
#include "node.h"
#include "projectstore.h"

namespace novelist {

class Element : public Node
{
    Q_OBJECT

public:
    explicit Element(QObject *parent = nullptr)
        : Element{"", parent}
    {}
    explicit Element(const QString &type, QObject *parent = nullptr);

    // [[nodiscard]] QString id() const { return mId; }
    // void setId(const QString &id);

    [[nodiscard]] QList<Field *> fields() const { return mFields; }
    [[nodiscard]] Field *field(int index) const { return mFields.value(index); }
    [[nodiscard]] Field *field(const QString &name) const { return mFieldMap.value(name); }
    Q_INVOKABLE Field *appendField(Field *field);

    [[nodiscard]] FieldListModel *fieldListModel() const { return mFieldListModel; }

    [[nodiscard]] QString type() const { return mType; }
    void setType(const QString &type);

    [[nodiscard]] virtual QJsonObject toJson(bool *error = nullptr) const;
    virtual bool setJson(const QJsonObject &json);

signals:
    void fieldsChanged(QPrivateSignal);
    void typeChanged(QPrivateSignal);

private:
    QList<Field *> mFields;
    QMap<QString, Field *> mFieldMap;
    QString mType;
    QString mId;
    FieldListModel *mFieldListModel = nullptr;

    Q_PROPERTY(QList<Field *> fields READ fields NOTIFY fieldsChanged FINAL)
    Q_PROPERTY(QString type READ type NOTIFY typeChanged FINAL)
    Q_PROPERTY(FieldListModel *fieldListModel READ fieldListModel CONSTANT FINAL)
};

} // namespace novelist

#endif // NOVELIST_ELEMENT_H
