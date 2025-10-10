#ifndef AI_CONFIG_REASONING_H
#define AI_CONFIG_REASONING_H

#include "common.h"

namespace ai {

class Reasoning
{
    Q_GADGET
    Q_PROPERTY(ai::UtilityType utilityType READ utilityType CONSTANT FINAL)
    Q_PROPERTY(QJsonObject extra READ extra FINAL)
    Q_PROPERTY(bool empty READ isEmpty FINAL)
    Q_PROPERTY(bool valid READ isValid FINAL)
    Q_PROPERTY(Effort effort READ effort WRITE setEffort)
    Q_PROPERTY(Summary summary READ summary WRITE setSummary)

public:
    enum struct Effort { None, Minimal, Low, Medium, High };
    Q_ENUM(Effort)

    enum struct Summary { Auto, Concise, Detailed };
    Q_ENUM(Summary)

private:
    Effort e;
    Summary s;
    QJsonObject x;

    inline static const QMap<Effort, QString> effortKV = {{Effort::None, "none"},
                                                          {Effort::Minimal, "minimal"},
                                                          {Effort::Low, "low"},
                                                          {Effort::Medium, "medium"},
                                                          {Effort::High, "high"}};
    inline static const QMap<Summary, QString> summaryKV = {{Summary::Auto, "auto"},
                                                            {Summary::Concise, "concise"},
                                                            {Summary::Detailed, "detailed"}};

public:
    Reasoning(const QJsonObject& extra = {})
        : Reasoning{{}, {}, extra}
    {}
    Reasoning(Effort effort, Summary summary = Summary::Auto, const QJsonObject& extra = {})
        : e(effort)
        , s(summary)
        , x(extra)
    {}
    Reasoning(const QString& effort,
              const QString& summary = toString(Summary::Auto),
              const QJsonObject& extra = {})
        : e(toEffort(effort))
        , s(toSummary(summary))
        , x(extra)
    {}

    [[nodiscard]] ai::UtilityType utilityType() const { return UtilityType_Reasoning; }

    [[nodiscard]] Effort effort() const { return e; }
    void setEffort(Effort effort) { e = effort; }
    void setEffort(const QString& effort) { e = toEffort(effort); }

    [[nodiscard]] Summary summary() const { return s; }
    void setSummary(Summary summary) { s = summary; }
    void setSummary(const QString& summary) { s = toSummary(summary); }

    [[nodiscard]] QJsonObject extra() const { return x; }
    // void setExtra(const QJsonObject& extra) { d->extra = extra; }

    [[nodiscard]] bool operator==(const Reasoning& that) const
    {
        return e == that.e && s == that.s && x == that.x;
    }

    [[nodiscard]] bool isEmpty() const
    {
        return e == Effort::None && s == Summary::Auto && x.isEmpty();
    }
    [[nodiscard]] bool isValid() const { return e != Effort::None || s != Summary::Auto; }

    static Effort toEffort(const QString& effort) { return effortKV.key(effort, Effort::None); }
    static QString toString(Effort effort) { return effortKV.value(effort); }

    static Summary toSummary(const QString& summary)
    {
        return summaryKV.key(summary, Summary::Auto);
    }
    static QString toString(Summary summary) { return summaryKV.value(summary); }

    QJsonObject toJson() const
    {
        QJsonObject json = x;

        if (e != Effort::None)
            json.insert(QStringLiteral("effort"), toString(e));

        if (s != Summary::Auto)
            json.insert(QStringLiteral("summary"), toString(s));

        return json;
    }

    static Reasoning fromJson(const QJsonObject& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        QString e;
        QString s;
        QJsonObject x = json;

        if (json.contains(QStringLiteral("effort"))) {
            if (const auto v = json.value(QStringLiteral("effort")); v.isString()) {
                e = v.toString();
                x.remove(QStringLiteral("effort"));
            } else if (ok)
                *ok = false;
        }

        if (json.contains(QStringLiteral("summary"))) {
            if (const auto v = json.value(QStringLiteral("summary")); v.isString()) {
                s = v.toString();
                x.remove(QStringLiteral("summary"));
            } else if (ok)
                *ok = false;
        }

        return {e, s, x};
    }
};

} // namespace ai

#endif // AI_CONFIG_REASONING_H
