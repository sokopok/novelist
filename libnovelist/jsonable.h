#ifndef LIBNOVELIST_JSONABLE_H
#define LIBNOVELIST_JSONABLE_H

#include <QJsonObject>

class Jsonable
{
public:
    virtual ~Jsonable() = default;

    QJsonObject toJson(QStringList* errors = nullptr) const
    {
        QJsonObject json;
        writeJson(json, errors);
        return json;
    }

protected:
    virtual bool readJson(const QJsonObject& json, QStringList* errors = nullptr) = 0;
    virtual bool writeJson(QJsonObject& json, QStringList* errors = nullptr) const = 0;
};

#endif // LIBNOVELIST_JSONABLE_H
