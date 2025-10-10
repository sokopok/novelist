#ifndef AI_CONFIG_REFUSAL_H
#define AI_CONFIG_REFUSAL_H

#include "common.h"

namespace ai {

class Refusal
{
    Q_GADGET
    Q_PROPERTY(ai::UtilityType utilityType READ utilityType CONSTANT FINAL)
    Q_PROPERTY(QString refusal READ refusal WRITE setRefusal FINAL)
    Q_PROPERTY(QJsonObject extra READ extra FINAL)
    Q_PROPERTY(bool empty READ isEmpty FINAL)
    Q_PROPERTY(bool valid READ isValid FINAL)

    QString r;
    QJsonObject e;

public:
    Refusal(const QJsonObject& extra = {})
        : e{extra}
    {}
    Refusal(const QString& refusal, const QJsonObject& extra = {})
        : r{refusal}
        , e{extra}
    {}

    [[nodiscard]] ai::UtilityType utilityType() const { return UtilityType_Refusal; }

    [[nodiscard]] QJsonObject extra() const { return e; }

    [[nodiscard]] QString refusal() const { return r; }
    Refusal& setRefusal(const QString& refusal)
    {
        r = refusal;
        return *this;
    }

    [[nodiscard]] bool operator==(const Refusal& that) const { return r == that.r && e == that.e; }

    [[nodiscard]] bool isEmpty() const { return r.isEmpty() && e.isEmpty(); }
    [[nodiscard]] bool isValid() const { return true; }

    QJsonObject toJson() const
    {
        QJsonObject json = e;
        json[QStringLiteral("refusal")] = r;
        json[QStringLiteral("type")] = QStringLiteral("refusal");
        return json;
    }

    static Refusal fromJson(const QJsonObject& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        if (json.value(QStringLiteral("type")).toString() != QStringLiteral("refusal")) {
            if (ok)
                *ok = false;
            return {json};
        }

        QJsonObject extra = json;
        extra.remove(QStringLiteral("type"));

        QString refusal;

        if (const auto v = json.value(QStringLiteral("refusal")); v.isString())
            refusal = v.toString();

        else if (ok)
            *ok = false;

        extra.remove(QStringLiteral("refusal"));

        return {refusal, extra};
    }
};

} // namespace ai

#endif // AI_CONFIG_REFUSAL_H
