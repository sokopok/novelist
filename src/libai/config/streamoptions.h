#ifndef AI_CONFIG_STREAMOPTIONS_H
#define AI_CONFIG_STREAMOPTIONS_H

#include "base.h"

namespace ai {

class StreamOptions
{
    Q_GADGET
    Q_PROPERTY(bool includeObfuscation READ includeObfuscation WRITE setIncludeObfuscation)

public:
    StreamOptions(const QJsonObject& extra = {})
        : StreamOptions{false, extra}
    {}
    StreamOptions(bool includeObfuscation, const QJsonObject& extra = {})
        : d{new Data{includeObfuscation, extra}}
    {}

    [[nodiscard]] bool includeObfuscation() const { return d->includeObfuscation; }
    void setIncludeObfuscation(bool includeObfuscation)
    {
        d->includeObfuscation = includeObfuscation;
    }

    [[nodiscard]] QJsonObject extra() const { return d->extra; }
    // void setExtra(const QJsonObject& extra) { d->extra = extra; }

    [[nodiscard]] bool operator==(const StreamOptions& that) const
    {
        return d->includeObfuscation == that.d->includeObfuscation;
    }

    [[nodiscard]] bool isEmpty() const { return !d->includeObfuscation && d->extra.isEmpty(); }
    [[nodiscard]] bool isValid() const { return true; }

    QJsonObject toJson() const
    {
        QJsonObject json = d->extra;
        json.insert(QStringLiteral("include_obfuscation"), d->includeObfuscation);
        return json;
    }

    static StreamOptions fromJson(const QJsonObject& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        bool includeObfuscation = false;

        if (const auto v = json.value(QStringLiteral("include_obfuscation")); v.isBool())
            includeObfuscation = v.toBool();
        else if (ok)
            *ok = false;

        QJsonObject extra = json;
        extra.remove(QStringLiteral("include_obfuscation"));

        return {includeObfuscation, extra};
    }

private:
    struct Data : public QSharedData
    {
        Data(bool includeObfuscation = false, const QJsonObject& extra = {})
            : includeObfuscation{includeObfuscation}
            , extra{extra}
        {}

        bool includeObfuscation = false;
        QJsonObject extra;
    };

    QSharedPointer<Data> d;
};

} // namespace ai

#endif // AI_CONFIG_STREAMOPTIONS_H
