#ifndef AI_CONFIG_OUTPUTMESSAGE_H
#define AI_CONFIG_OUTPUTMESSAGE_H

#include "message.h"
#include "refusal.h"

namespace ai {

class OutputText
{
    Q_GADGET
    Q_PROPERTY(AiObjectType objectType READ objectType CONSTANT FINAL)
    Q_PROPERTY(QString text READ text WRITE setText FINAL)
    Q_PROPERTY(QJsonObject extra READ extra FINAL)
    Q_PROPERTY(bool empty READ isEmpty FINAL)
    Q_PROPERTY(bool valid READ isValid FINAL)

    // annotations and logprobs!!!

    QString t;
    QJsonObject e;

public:
    OutputText(const QJsonObject& extra = {})
        : e{extra}
    {}
    OutputText(const QString& text, const QJsonObject& extra = {})
        : t{text}
        , e{extra}
    {}

    [[nodiscard]] AiObjectType objectType() const { return AiObjectType::OutputText; }

    [[nodiscard]] QJsonObject extra() const { return e; }

    [[nodiscard]] QString text() const { return t; }
    OutputText& setText(const QString& text)
    {
        t = text;
        return *this;
    }

    [[nodiscard]] bool operator==(const OutputText& that) const
    {
        return t == that.t && e == that.e;
    }

    [[nodiscard]] bool isEmpty() const { return t.isEmpty() && e.isEmpty(); }
    [[nodiscard]] bool isValid() const { return true; }

    QJsonObject toJson() const
    {
        QJsonObject json = e;
        json[QStringLiteral("text")] = t;
        json[QStringLiteral("type")] = QStringLiteral("output_text");
        return json;
    }

    static OutputText fromJson(const QJsonObject& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        if (json.value(QStringLiteral("type")).toString() != QStringLiteral("output_text")) {
            if (ok)
                *ok = false;
            return {json};
        }

        QJsonObject extra = json;
        extra.remove(QStringLiteral("type"));

        QString text;

        if (json.contains(QStringLiteral("text"))) {
            if (const auto v = json.value(QStringLiteral("text")); v.isString()) {
                text = v.toString();
                extra.remove(QStringLiteral("text"));
            } else if (ok)
                *ok = false;
        }
        /*
        if (json.contains(QStringLiteral("annotations"))) {
            if (const auto v = json.value(QStringLiteral("annotations")); v.isArray()) {
                // text = v.toString();
                extra.remove(QStringLiteral("annotations"));
            } else if (ok)
                *ok = false;
        }

        if (json.contains(QStringLiteral("logprobs"))) {
            if (const auto v = json.value(QStringLiteral("logprobs")); v.isArray()) {
                // text = v.toString();
                extra.remove(QStringLiteral("logprobs"));
            } else if (ok)
                *ok = false;
        }
*/
        return {text, extra};
    }
};

class OutputMessageContent
{
    Q_GADGET
    Q_PROPERTY(OutputText text READ text WRITE setText FINAL)
    Q_PROPERTY(Refusal refusal READ refusal WRITE setRefusal FINAL)
    // Q_PROPERTY(InputFile file READ file WRITE setFile FINAL)
    // Q_PROPERTY(InputAudio audio READ audio WRITE setAudio FINAL)
    Q_PROPERTY(QJsonObject extra READ extra FINAL)
    Q_PROPERTY(bool empty READ isEmpty FINAL)
    Q_PROPERTY(bool valid READ isValid FINAL)

    using Variant = std::variant<Empty, OutputText, Refusal>;
    Variant d;
    QJsonObject e;

public:
    OutputMessageContent(const QJsonObject& extra = {})
        : e{extra}
    {}
    OutputMessageContent(const Variant& input, const QJsonObject& extra = {})
        : d{input}
        , e{extra}
    {}

    [[nodiscard]] QJsonObject extra() const { return e; }

    [[nodiscard]] bool isText() const { return d.index() == 1; }
    [[nodiscard]] bool isRefusal() const { return d.index() == 2; }

    [[nodiscard]] OutputText text() const
    {
        return isText() ? std::get<OutputText>(d) : OutputText{};
    }
    OutputMessageContent& setText(const OutputText& text)
    {
        std::get<OutputText>(d) = text;
        return *this;
    }

    [[nodiscard]] Refusal refusal() const { return isRefusal() ? std::get<Refusal>(d) : Refusal{}; }
    OutputMessageContent& setRefusal(const Refusal& refusal)
    {
        std::get<Refusal>(d) = refusal;
        return *this;
    }

    [[nodiscard]] bool operator==(const OutputMessageContent& that) const
    {
        return d == that.d && e == that.e;
    }

    [[nodiscard]] bool isEmpty() const
    {
        return (d.index() == 0 || (isText() && text().isEmpty())
                || (isRefusal() && refusal().isEmpty()))
               && e.isEmpty();
    }
    [[nodiscard]] bool isValid() const { return (isText() && text().isValid()); }

    QJsonObject toJson() const
    {
        switch (d.index()) {
        case 1:
            return text().toJson();
        case 2:
            return refusal().toJson();
        default:
            return {};
        }
    }

    static OutputMessageContent fromJson(const QJsonObject& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        if (const auto v = json.value(QStringLiteral("type")).toString();
            v == QStringLiteral("output_text"))
            return {OutputText::fromJson(json, ok)};

        else if (v == QStringLiteral("refusal"))
            return {Refusal::fromJson(json, ok)};

        if (ok)
            *ok = false;

        return {json};
    }
};

class OutputMessageContentList : public QList<OutputMessageContent>
{
public:
    OutputMessageContentList(const QList<OutputMessageContent>& items = {})
        : QList<OutputMessageContent>{items}
    {}

    [[nodiscard]] ai::AiObjectType objectType() const
    {
        return ai::AiObjectType::OutputMessageContentList;
    }

    [[nodiscard]] bool isValid() const { return !isEmpty(); }

    QJsonArray toJson() const
    {
        QJsonArray array;
        for (const auto& item : *this)
            array.append(item.toJson());
        return array;
    }

    static OutputMessageContentList fromJson(const QJsonArray& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        OutputMessageContentList list;

        for (const auto& i : json)
            list.append(OutputMessageContent::fromJson(i.toObject(), ok));

        return list;
    }
};

class OutputMessage : public Message
{
    Q_GADGET
    Q_PROPERTY(OutputMessageContentList content READ content WRITE setContent FINAL)

private:
    OutputMessageContentList c;

public:
    OutputMessage(const QJsonObject& extra = {})
        : Message{extra}
    {}
    OutputMessage(const OutputMessageContentList& content,
                  const QString& role,
                  Status status,
                  const QJsonObject& extra = {})
        : Message{role, status, extra}
        , c{content}
    {}
    OutputMessage(const OutputMessageContentList& content,
                  const QString& role = QStringLiteral("user"),
                  const QString& id = {},
                  Status status = Status::InProgress,
                  const QJsonObject& extra = {})
        : Message{role, id, status, extra}
        , c{content}
    {}

    [[nodiscard]] AiObjectType objectType() const { return AiObjectType::OutputMessage; }

    [[nodiscard]] OutputMessageContentList content() const { return c; }
    OutputMessage& setContent(const OutputMessageContentList& content)
    {
        c = content;
        return *this;
    }

    [[nodiscard]] bool operator==(const OutputMessage& that) const
    {
        return c == that.c && Message::operator==(that);
    }

    [[nodiscard]] bool isEmpty() const { return c.isEmpty() && Message::isEmpty(); }
    [[nodiscard]] bool isValid() const { return c.isValid() && Message::isValid(); }

    QJsonValue toJson() const
    {
        QJsonObject json = Message::toJson().toObject();

        if (!c.isEmpty())
            json[QStringLiteral("content")] = c.toJson();

        return json;
    }

    static OutputMessage fromJson(const QJsonObject& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        if (json.value(QStringLiteral("type")).toString() != QStringLiteral("message")) {
            if (ok)
                *ok = false;
            return {};
        }

        QJsonObject extra = json;
        extra.remove(QStringLiteral("type"));

        OutputMessage message;

        if (json.contains(QStringLiteral("role"))) {
            if (const auto v = json.value(QStringLiteral("role")); !v.isString()) {
                if (ok)
                    *ok = false;
            } else {
                message.setRole(v.toString());
                extra.remove(QStringLiteral("role"));
            }
        }

        if (json.contains(QStringLiteral("status"))) {
            if (const auto v = json.value(QStringLiteral("status")); !v.isString()) {
                if (ok)
                    *ok = false;
            } else {
                message.setStatus(toStatus(v.toString()));
                extra.remove(QStringLiteral("status"));
            }
        }

        if (json.contains(QStringLiteral("id"))) {
            if (const auto v = json.value(QStringLiteral("id")); !v.isString()) {
                if (ok)
                    *ok = false;
            } else {
                message.setId(v.toString());
                extra.remove(QStringLiteral("id"));
            }
        }

        if (json.contains(QStringLiteral("content"))) {
            if (const auto v = json.value(QStringLiteral("content")); v.isArray()) {
                message.c = OutputMessageContentList::fromJson(v.toArray());
                extra.remove(QStringLiteral("content"));
            } else {
                if (ok)
                    *ok = false;
            }
        }

        // message. = extra;
        return message;
    }
};

} // namespace ai

#endif // AI_CONFIG_OUTPUTMESSAGE_H
