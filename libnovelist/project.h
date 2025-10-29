#ifndef PROJECT_H
#define PROJECT_H

#include "element.h"
#include "projecttype.h"

class Storage;
class ValueType;
class Value;

class Project : public Element
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Project(Storage *storage, QObject *parent = nullptr)
        : Project{Type_Project, storage, parent}
    {}
    Project(int type, Storage *storage, QObject *parent = nullptr)
        : Project{nullptr, type, storage, parent}
    {}
    Project(ProjectType *projectType, Storage *storage, QObject *parent = nullptr)
        : Project{projectType, Type_Project, storage, parent}
    {}
    Project(ProjectType *projectType, int type, Storage *storage, QObject *parent = nullptr)
        : Element{projectType, type, storage, parent}
    {}

    bool reload() override;
    bool save(bool newVersion = true) override;
    bool recycle() override;

    // [[nodiscard]] Storage *storage() const { return mStorage; }
    void setStorage(Storage *storage) override;

    [[nodiscard]] QString databaseName() const;
    void setDatabaseName(const QString &databaseName);

    QList<ElementType *> elementTypes() const;
    ElementType *elementType(const QString &name) const;
    ElementType *addElementType(const QString &name,
                                const QString &label = {},
                                const QString &info = {},
                                const QString &icon = {});

    QList<FieldType *> fieldTypes() const;
    FieldType *fieldType(const QString &name) const;
    FieldType *addFieldType(const QString &name,
                            const QString &label = {},
                            const QString &info = {},
                            const QString &icon = {});

    QList<ValueType *> valueTypes() const;
    ValueType *valueType(const QString &name) const;
    ValueType *addValueType(const QString &name,
                            const QString &label = {},
                            const QString &info = {},
                            const QString &icon = {});

    Element *elementFromStorage(int rowid) const;
    Element *addElement(ElementType *elementType,
                        const QString &label = {},
                        const QString &info = {},
                        const QString &icon = {});

    Field *fieldFromStorage(int rowid) const;
    Field *addField(FieldType *fieldType,
                    const QString &label = {},
                    const QString &info = {},
                    const QString &icon = {});

    Value *valueFromStorage(int rowid) const;
    Value *addValue(ValueType *valueType,
                    const QString &label = {},
                    const QString &info = {},
                    const QString &icon = {});

signals:
    void storageChanged();
    void databaseNameChanged();

protected:
    // bool readJson(const QJsonObject &json, QStringList *errors = nullptr) override;
    // bool writeJson(QJsonObject &json, QStringList *errors = nullptr) const override;

private:
    // Storage *mStorage = nullptr;

    // Q_PROPERTY(Storage *storage READ storage WRITE setStorage NOTIFY storageChanged FINAL)
    Q_PROPERTY(QString databaseName READ databaseName WRITE setDatabaseName NOTIFY
                   databaseNameChanged FINAL)
};

#endif // PROJECT_H
