#ifndef AI_CONFIG_CONVERSATION_H
#define AI_CONFIG_CONVERSATION_H

#include "common.h"

namespace ai {

class ConversationData;

class Conversation
{
    Q_GADGET
    Q_PROPERTY(ai::UtilityType utilityType READ utilityType CONSTANT FINAL)
    Q_PROPERTY(QString id READ id WRITE setId FINAL)
    Q_PROPERTY(QJsonObject extra READ extra FINAL)
    Q_PROPERTY(bool empty READ isEmpty FINAL)
    Q_PROPERTY(bool valid READ isValid FINAL)

public:
    Conversation(const QJsonObject& extra = {});
    Conversation(const QString& id, const QJsonObject& extra = {});
    Conversation(const Conversation&);
    Conversation(Conversation&&);
    Conversation& operator=(const Conversation&);
    Conversation& operator=(Conversation&&);
    ~Conversation();

    [[nodiscard]] ai::UtilityType utilityType() const { return UtilityType_Conversation; }

    [[nodiscard]] QJsonObject extra() const;
    bool setExtra(const QJsonObject& extra);

    [[nodiscard]] QString id() const;
    bool setId(const QString& id);

    [[nodiscard]] bool operator==(const Conversation& that) const
    {
        return id() == that.id() && extra() == that.extra();
    }

    [[nodiscard]] bool isEmpty() const { return id().isEmpty(); }
    [[nodiscard]] bool isValid() const { return !id().isEmpty(); }

    QJsonObject toJson() const;

    static Conversation fromJson(const QJsonObject& json, QStringList* errors = nullptr)
    {
        QJsonObject x = json;

        if (x.value(QStringLiteral("type")).toString() != QStringLiteral("conversation")) {
            if (errors)
                errors->append(QStringLiteral("not a converation"));
            return {x};
        }

        x.remove(QStringLiteral("type"));

        QString id;

        if (x.contains(QStringLiteral("id"))) {
            if (const auto v = x.value(QStringLiteral("id")); !v.isString()) {
                if (errors)
                    errors->append(QStringLiteral("id is not a string"));
            } else if (id = v.toString(); id.isEmpty()) {
                if (errors)
                    errors->append(QStringLiteral("id is empty"));
            } else {
                id = v.toString();
                x.remove(QStringLiteral("id"));
            }
        }

        return {id, x};
    }

private:
    QSharedDataPointer<ConversationData> d;
};

} // namespace ai

#endif // AI_CONFIG_CONVERSATION_H
