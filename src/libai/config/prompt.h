#ifndef AI_CONFIG_PROMPT_H
#define AI_CONFIG_PROMPT_H

#include "common.h"

namespace ai::config {

class Prompt
{
    Q_GADGET
    Q_PROPERTY(ai::config::Type objectType READ objectType CONSTANT FINAL)
    Q_PROPERTY(QJsonObject extra READ extra FINAL)
    Q_PROPERTY(bool empty READ isEmpty FINAL)
    Q_PROPERTY(bool valid READ isValid FINAL)
    Q_PROPERTY(QVariantMap variables READ variables WRITE setVariables FINAL)
    Q_PROPERTY(QString id READ id WRITE setId FINAL)
    Q_PROPERTY(QString version READ version WRITE setVersion FINAL)

public:
private:
    QString i;
    QString ve;
    QVariantMap va;
    QJsonObject e;

public:
    Prompt(const QJsonObject& extra = {})
        : e{extra}
    {}
    Prompt(const QString& id,
           const QVariantMap& variables = {},
           const QString& version = {},
           const QJsonObject& extra = {})
        : i{id}
        , ve{version}
        , va{variables}
        , e{extra}
    {}

    [[nodiscard]] ai::config::Type objectType() const { return ai::config::Type::Type_Prompt; }

    [[nodiscard]] QJsonObject extra() const { return e; }

    [[nodiscard]] QString id() const { return i; }
    Prompt& setId(const QString& id)
    {
        i = id;
        return *this;
    }

    [[nodiscard]] QString version() const { return ve; }
    Prompt& setVersion(const QString& version)
    {
        ve = version;
        return *this;
    }

    [[nodiscard]] QVariantMap variables() const { return va; }
    Prompt& setVariables(const QVariantMap& variables)
    {
        va = variables;
        return *this;
    }

    [[nodiscard]] bool operator==(const Prompt& that) const
    {
        return i == that.i && ve == that.ve && va == that.va && e == that.e;
    }

    [[nodiscard]] bool isEmpty() const { return i.isEmpty(); }
    [[nodiscard]] bool isValid() const { return !isEmpty(); }

    QJsonObject toJson() const
    {
        QJsonObject json = e;

        if (!i.isEmpty())
            json.insert(QStringLiteral("id"), i);

        if (!ve.isEmpty())
            json.insert(QStringLiteral("version"), ve);

        if (!va.isEmpty())
            json.insert(QStringLiteral("variables"), QJsonObject::fromVariantMap(va));

        return json;
    }

    static Prompt fromJson(const QJsonObject& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        // if (json.value(QStringLiteral("type")).toString() != QStringLiteral("prompt")) {
        //     if (ok)
        //         *ok = false;
        //     return {};
        // }

        QJsonObject x = json;
        // extra.remove(QStringLiteral("type"));

        Prompt p;

        if (json.contains(QStringLiteral("id"))) {
            if (const auto v = json.value(QStringLiteral("id")); !v.isString()) {
                if (ok)
                    *ok = false;
            } else {
                p.setId(v.toString());
                x.remove(QStringLiteral("id"));
            }
        }

        if (json.contains(QStringLiteral("version"))) {
            if (const auto v = json.value(QStringLiteral("version")); v.isString()) {
                p.setVersion(v.toString());
                x.remove(QStringLiteral("version"));
            } else if (ok)
                *ok = false;
        }

        if (json.contains(QStringLiteral("variables"))) {
            if (const auto v = json.value(QStringLiteral("variables")); v.isObject()) {
                p.setVariables(v.toVariant().toMap());
                x.remove(QStringLiteral("variables"));
            } else if (ok)
                *ok = false;
        }

        return p;
    }
};

} // namespace ai::config

#endif // AI_CONFIG_PROMPT_H
