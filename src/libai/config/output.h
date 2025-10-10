#ifndef AI_CONFIG_OUTPUT_H
#define AI_CONFIG_OUTPUT_H

#include "../json.h"
#include "input.h"
#include "outputmessage.h"
#include "refusal.h"

namespace ai::config {

class ImageGenerationCall
{
    Q_GADGET
    Q_PROPERTY(ai::config::Type objectType READ objectType CONSTANT FINAL)
    Q_PROPERTY(QString id READ id WRITE setId FINAL)
    Q_PROPERTY(QString status READ status WRITE setStatus FINAL)
    Q_PROPERTY(QString result READ result WRITE setResult FINAL)
    Q_PROPERTY(QJsonObject extra READ extra FINAL)
    Q_PROPERTY(bool empty READ isEmpty FINAL)
    Q_PROPERTY(bool valid READ isValid FINAL)

    QString i;
    QString s;
    QString r;
    QJsonObject e;

public:
    ImageGenerationCall(const QJsonObject& extra = {})
        : ImageGenerationCall{{}, {}, {}, extra}
    {}
    ImageGenerationCall(const QString& id,
                        const QString& status,
                        const QString& result,
                        const QJsonObject& extra = {})
        : i{id}
        , s{status}
        , r{result}
        , e{extra}
    {}

    [[nodiscard]] ai::config::Type objectType() const
    {
        return ai::config::Type::Type_ImageGenerationCall;
    }

    [[nodiscard]] QJsonObject extra() const { return e; }

    [[nodiscard]] QString id() const { return i; }
    ImageGenerationCall& setId(const QString& id)
    {
        i = id;
        return *this;
    }

    [[nodiscard]] QString result() const { return i; }
    ImageGenerationCall& setResult(const QString& result)
    {
        r = result;
        return *this;
    }

    [[nodiscard]] QString status() const { return i; }
    ImageGenerationCall& setStatus(const QString& status)
    {
        s = status;
        return *this;
    }

    [[nodiscard]] bool operator==(const ImageGenerationCall& that) const
    {
        return i == that.i && r == that.r && s == that.s && e == that.e;
    }

    [[nodiscard]] bool isEmpty() const
    {
        return i.isEmpty() && r.isEmpty() && s.isEmpty() && e.isEmpty();
    }
    [[nodiscard]] bool isValid() const { return !i.isEmpty() && !s.isEmpty(); }

    QJsonObject toJson() const
    {
        QJsonObject json = e;
        json.insert(QStringLiteral("id"), i);
        json.insert(QStringLiteral("result"), r);
        json.insert(QStringLiteral("status"), s);
        json.insert(QStringLiteral("type"), QStringLiteral("image_generation_call"));
        return json;
    }

    static ImageGenerationCall fromJson(const QJsonObject& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        if (json.value(QStringLiteral("type")).toString()
            != QStringLiteral("image_generation_call")) {
            if (ok)
                *ok = false;
            return {json};
        }

        QJsonObject extra = json;
        extra.remove(QStringLiteral("type"));

        QString i;
        QString r;
        QString s;

        if (const auto v = json.value(QStringLiteral("id")); v.isString()) {
            extra.remove(QStringLiteral("id"));
            i = v.toString();
        }

        if (const auto v = json.value(QStringLiteral("result")); v.isString()) {
            extra.remove(QStringLiteral("result"));
            r = v.toString();
        }

        if (const auto v = json.value(QStringLiteral("status")); v.isString()) {
            extra.remove(QStringLiteral("status"));
            s = v.toString();
        }

        else if (ok)
            *ok = false;

        return {i, s, r, extra};
    }
};

class OutputItem
{
    using Variant = std::variant<Empty, OutputMessage, ImageGenerationCall>;
    Variant d;
    QJsonObject e;

public:
    OutputItem(const QJsonObject& extra = {})
        : OutputItem{{}, extra}
    {}
    OutputItem(const Variant& item, const QJsonObject& extra = {})
        : d{item}
        , e{extra}
    {}

    [[nodiscard]] QJsonObject extra() const { return e; }

    [[nodiscard]] bool isMessage() const { return d.index() == 1; }
    [[nodiscard]] bool isImageGenerationCall() const { return d.index() == 2; }

    [[nodiscard]] OutputMessage message() const { return std::get<OutputMessage>(d); }
    OutputItem& setMessage(const OutputMessage& message)
    {
        std::get<OutputMessage>(d) = message;
        return *this;
    }

    [[nodiscard]] ImageGenerationCall imageGenerationCall() const { return std::get<2>(d); }
    OutputItem& setImageGenerationCall(const ImageGenerationCall& imageGenerationCall)
    {
        std::get<2>(d) = imageGenerationCall;
        return *this;
    }

    [[nodiscard]] bool operator==(const OutputItem& that) const
    {
        return d == that.d && e == that.e;
    }

    [[nodiscard]] bool isEmpty() const
    {
        if (isMessage())
            return message().isEmpty() && e.isEmpty();

        if (isImageGenerationCall())
            return imageGenerationCall().isEmpty() && e.isEmpty();

        return e.isEmpty();
    }
    [[nodiscard]] bool isValid() const
    {
        if (isMessage())
            return message().isValid();

        if (isImageGenerationCall())
            return imageGenerationCall().isValid();

        return false;
    }

    QJsonValue toJson() const
    {
        if (isMessage())
            return message().toJson();

        if (isImageGenerationCall())
            return imageGenerationCall().toJson();

        return e;
    }

    static OutputItem fromJson(const QJsonObject& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        if (const auto v = json.value(QStringLiteral("type")).toString();
            v == QStringLiteral("message"))
            return {OutputMessage::fromJson(json, ok)};

        else if (v == QStringLiteral("image_generation_call"))
            return {ImageGenerationCall::fromJson(json, ok)};

        return {{}, json};
    }
};

class OutputItemList : public QList<OutputItem>
{
public:
    OutputItemList(const QList<OutputItem>& items = {})
        : QList<OutputItem>{items}
    {}

    [[nodiscard]] ai::config::Type objectType() const { return ai::config::Type::Type_OutputItemList; }

    [[nodiscard]] bool isValid() const { return !isEmpty(); }

    QJsonArray toJson() const
    {
        QJsonArray array;
        for (const auto& item : *this)
            array.append(item.toJson());
        return array;
    }

    static OutputItemList fromJson(const QJsonArray& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        OutputItemList list;

        for (const auto& i : json)
            list.append(OutputItem::fromJson(i.toObject(), ok));

        return list;
    }
};

class Output : public OutputItemList
{
    Q_GADGET

public:
    Output(const QList<OutputItem>& items = {})
        : OutputItemList{items}
    {}
};

} // namespace ai::config

#endif // AI_CONFIG_OUTPUT_H
