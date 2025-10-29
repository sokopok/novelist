#ifndef LIBNOVELIST_ELEMENT_H
#define LIBNOVELIST_ELEMENT_H

#include "elementtype.h"
#include "fieldlistmodel.h"
#include "node.h"

class Field;

Q_MOC_INCLUDE("field.h")

class Element : public Node
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("")

public:
    explicit Element(Storage *storage, QObject *parent = nullptr)
        : Element{Type_Element, storage, parent}
    {}
    Element(int type, Storage *storage, QObject *parent = nullptr)
        : Element{nullptr, type, storage, parent}
    {}
    Element(ElementType *elementType, Storage *storage, QObject *parent = nullptr)
        : Element{elementType, Type_Element, storage, parent}
    {}
    Element(ElementType *elementType, int type, Storage *storage, QObject *parent = nullptr)
        : Node{elementType, type, storage, parent}
    {}

    bool reload() override;
    bool save(bool newVersion = true) override;
    bool recycle() override;

    [[nodiscard]] QList<Field *> fields() const { return mFields; }
    void setFields(const QList<Field *> &fields);

    [[nodiscard]] Field *field(int index) const { return mFields.value(index); }
    [[nodiscard]] Field *field(const QString &name) const { return mFieldsByName.value(name); }
    bool insertField(int index, Field *field);
    bool appendField(Field *field) { return insertField(mFields.size(), field); }
    bool prependField(Field* field) { return insertField(0, field); }
    bool removeField(Field* field)
    {
        if (!field)
            return false;
        int index = mFields.indexOf(field);
        while (index >= 0) {
            if (!removeFieldAt(index))
                return false;
            index = mFields.indexOf(field, index);
        }
        return true;
    }
    bool removeFieldAt(int index);
    Field* takeFieldAt(int index)
    {
        if (index < 0 || index >= mFields.size())
            return nullptr;
        Field *field = mFields[index];
        if (!removeFieldAt(index))
            return nullptr;
        return field;
    }

    [[nodiscard]] FieldListModel *fieldListModel();

    using Node::setNodeType;

signals:
    void fieldsChanged(QPrivateSignal);
    void fieldsAdded(int first, int last, QPrivateSignal);
    void fieldsRemoved(int first, int last, QPrivateSignal);

protected:
    bool readJson(const QJsonObject &json, QStringList *errors = nullptr) override;
    bool writeJson(QJsonObject &json, QStringList *errors = nullptr) const override;

    void setNodeType(NodeType *nodeType, bool emitSignals) override;

    bool updateFields();

private:
    QList<Field *> mFields;
    QMap<QString, Field *> mFieldsByName;
    FieldListModel *mFieldListModel = nullptr;
    bool mPerformUpdateFields = true;

    Q_PROPERTY(QList<Field*> fields READ fields WRITE setFields NOTIFY fieldsChanged FINAL)
    Q_PROPERTY(FieldListModel *fieldListModel READ fieldListModel CONSTANT FINAL)
};

#endif // LIBNOVELIST_ELEMENT_H
