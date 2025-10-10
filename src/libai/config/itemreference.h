#ifndef AI_CONFIG_ITEMREFERENCE_H
#define AI_CONFIG_ITEMREFERENCE_H

#include "common.h"

namespace ai {

class ItemReference
{
    Q_GADGET
    Q_PROPERTY(ai::UtilityType utilityType READ utilityType CONSTANT FINAL)
    Q_PROPERTY(QString id READ id WRITE setId FINAL)
    Q_PROPERTY(QJsonObject extra READ extra FINAL)
    Q_PROPERTY(bool empty READ isEmpty FINAL)
    Q_PROPERTY(bool valid READ isValid FINAL)

    QString i;
    QJsonObject e;

public:
    ItemReference(const QJsonObject& extra = {})
        : ItemReference{{}, extra}
    {}
    ItemReference(const QString& id, const QJsonObject& extra = {})
        : i{id}
        , e{extra}
    {}

    [[nodiscard]] ai::UtilityType utilityType() const
    {
        return UtilityType_ItemReference;
    }

    [[nodiscard]] QJsonObject extra() const { return e; }

    [[nodiscard]] QString id() const { return i; }
    ItemReference& setId(const QString& id)
    {
        i = id;
        return *this;
    }

    [[nodiscard]] bool operator==(const ItemReference& that) const
    {
        return i == that.i && e == that.e;
    }

    [[nodiscard]] bool isEmpty() const { return i.isEmpty() && e.isEmpty(); }
    [[nodiscard]] bool isValid() const { return !i.isEmpty(); }

    QJsonObject toJson() const
    {
        QJsonObject json = e;
        json.insert(QStringLiteral("id"), i);
        json.insert(QStringLiteral("type"), QStringLiteral("item_reference"));
        return json;
    }

    static ItemReference fromJson(const QJsonObject& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        if (json.value(QStringLiteral("type")).toString() != QStringLiteral("item_reference")) {
            if (ok)
                *ok = false;
            return {json};
        }

        QJsonObject extra = json;
        extra.remove(QStringLiteral("type"));

        QString id;

        if (const auto v = json.value(QStringLiteral("id")); v.isString()) {
            extra.remove(QStringLiteral("id"));
            id = v.toString();
        }

        else if (ok)
            *ok = false;

        return {id, extra};
    }
};

} // namespace ai

#endif // AI_CONFIG_ITEMREFERENCE_H
