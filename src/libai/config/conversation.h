#ifndef AI_CONFIG_CONVERSATION_H
#define AI_CONFIG_CONVERSATION_H

#include "base.h"

namespace ai {

class Conversation
{
    Q_GADGET
    Q_PROPERTY(Type type READ type CONSTANT FINAL)
    Q_PROPERTY(QString id READ id WRITE setId FINAL)
    Q_PROPERTY(QJsonObject extra READ extra FINAL)
    Q_PROPERTY(bool empty READ isEmpty FINAL)
    Q_PROPERTY(bool valid READ isValid FINAL)

    QString i;
    QJsonObject e;

public:
    Conversation(const QJsonObject& extra = {})
        : e{extra}
    {}
    Conversation(const QString& id, const QJsonObject& extra = {})
        : i{id}
        , e{extra}
    {}

    [[nodiscard]] Type type() const { return Type::Conversation; }

    [[nodiscard]] QJsonObject extra() const { return e; }

    [[nodiscard]] QString id() const { return i; }
    Conversation& setId(const QString& id)
    {
        i = id;
        return *this;
    }

    [[nodiscard]] bool operator==(const Conversation& that) const
    {
        return i == that.i && e == that.e;
    }

    [[nodiscard]] bool isEmpty() const { return i.isEmpty() && e.isEmpty(); }
    [[nodiscard]] bool isValid() const { return !i.isEmpty(); }

    QJsonObject toJson() const
    {
        QJsonObject json = e;
        json[QStringLiteral("id")] = i;
        json[QStringLiteral("type")] = QStringLiteral("conversation");
        return json;
    }

    static Conversation fromJson(const QJsonObject& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        if (json.value(QStringLiteral("type")).toString() != QStringLiteral("conversation")) {
            if (ok)
                *ok = false;
            return {json};
        }

        QJsonObject extra = json;
        extra.remove(QStringLiteral("type"));

        QString id;

        if (const auto v = json.value(QStringLiteral("id")); v.isString())
            id = v.toString();

        else if (ok)
            *ok = false;

        extra.remove(QStringLiteral("id"));

        return {id, extra};
    }
};

} // namespace ai

#endif // AI_CONFIG_CONVERSATION_H
