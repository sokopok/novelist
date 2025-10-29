#ifndef LIBNOVELIST_PROJECTTYPE_H
#define LIBNOVELIST_PROJECTTYPE_H

#include "elementtype.h"

class FieldType;
class Project;

class ProjectType : public ElementType
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("")

public:
    explicit ProjectType(Storage* storage, QObject* parent = nullptr)
        : ProjectType{Type_ProjectType, storage, parent}
    {}
    ProjectType(int type, Storage* storage, QObject* parent = nullptr)
        : ElementType{type, storage, parent}
    {}

    [[nodiscard]] Project* createProject();
    [[nodiscard]] Project* project(int rowid);

    bool reload() override;
    bool save(bool newVersion = true) override;
    bool recycle() override;

protected:
    // bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override;
    // bool writeJson(QJsonObject& json, QStringList* errors = nullptr) const override;
};

#endif // LIBNOVELIST_PROJECTTYPE_H
