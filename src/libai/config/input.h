#ifndef AI_CONFIG_INPUT_H
#define AI_CONFIG_INPUT_H

#include "../json.h"
#include "message.h"

namespace ai {

class ItemReference
{
    Q_GADGET
    Q_PROPERTY(AiObjectType objectType READ objectType CONSTANT FINAL)
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

    [[nodiscard]] AiObjectType objectType() const { return AiObjectType::ItemReference; }

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

class InputItem
{
    using Variant = std::variant<Empty, Message, ItemReference>;
    Variant d;
    QJsonObject e;

public:
    InputItem(const QJsonObject& extra = {})
        : InputItem{{}, extra}
    {}
    InputItem(const Variant& item, const QJsonObject& extra = {})
        : d{item}
        , e{extra}
    {}

    [[nodiscard]] QJsonObject extra() const { return e; }

    [[nodiscard]] bool isMessage() const { return d.index() == 1; }
    [[nodiscard]] bool isItemReference() const { return d.index() == 2; }

    [[nodiscard]] Message message() const { return std::get<1>(d); }
    InputItem& setMessage(const Message& message)
    {
        std::get<1>(d) = message;
        return *this;
    }

    [[nodiscard]] ItemReference itemReference() const { return std::get<2>(d); }
    InputItem& setItemReference(const ItemReference& itemReference)
    {
        std::get<2>(d) = itemReference;
        return *this;
    }

    [[nodiscard]] bool operator==(const InputItem& that) const
    {
        return d == that.d && e == that.e;
    }

    [[nodiscard]] bool isEmpty() const
    {
        if (isMessage())
            return message().isEmpty() && e.isEmpty();

        if (isItemReference())
            return itemReference().isEmpty() && e.isEmpty();

        return e.isEmpty();
    }
    [[nodiscard]] bool isValid() const
    {
        if (isMessage())
            return message().isValid();

        if (isItemReference())
            return itemReference().isValid();

        return false;
    }

    QJsonValue toJson() const
    {
        if (isMessage())
            return message().toJson();

        if (isItemReference())
            return itemReference().toJson();

        return e;
    }

    static InputItem fromJson(const QJsonObject& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        if (const auto v = json.value(QStringLiteral("type")).toString();
            v == QStringLiteral("message"))
            return {Message::fromJson(json, ok)};

        else if (v == QStringLiteral("item_reference"))
            return {ItemReference::fromJson(json, ok)};

        return {{}, json};
    }
};

class InputItemList : public QList<InputItem>
{
public:
    InputItemList(const QList<InputItem>& items = {})
        : QList<InputItem>{items}
    {}

    [[nodiscard]] ai::AiObjectType objectType() const { return ai::AiObjectType::InputItemList; }

    [[nodiscard]] bool isValid() const { return !isEmpty(); }

    QJsonArray toJson() const
    {
        QJsonArray array;
        for (const auto& item : *this)
            array.append(item.toJson());
        return array;
    }

    static InputItemList fromJson(const QJsonArray& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        InputItemList list;

        for (const auto& i : json)
            list.append(InputItem::fromJson(i.toObject(), ok));

        return list;
    }
};

class Input
{
    Q_GADGET
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(InputItemList items READ items WRITE setItems)

    using Variant = std::variant<Empty, QString, InputItemList>;

    // struct Data : public QSharedData
    // {
    //     Data(const Variant& data = {}, const QJsonObject& extra = {})
    //         : data{data}
    //         , extra{extra}
    //     {}

    //     Variant data;
    //     QJsonObject extra;
    // };

    // QSharedPointer<Data> d;

    Variant d;

public:
    Input()
        : Input{{}}
    {}
    Input(const Variant& data)
        : d{data}
    {}

    // Input(const Input& rhs)
    //     : d{rhs.d}
    // {}
    // Input(Input&& rhs)
    //     : d{std::move(rhs.d)}
    // {}
    // Input& operator=(const Input& rhs)
    // {
    //     if (this != &rhs)
    //         d = rhs.d;
    //     return *this;
    // }
    // Input& operator=(Input&& rhs)
    // {
    //     if (this != &rhs)
    //         d = std::move(rhs.d);
    //     return *this;
    // }

    [[nodiscard]] bool isText() const { return d.index() == 1; }
    [[nodiscard]] bool isInputItemList() const { return d.index() == 2; }

    [[nodiscard]] QString text() const { return isText() ? std::get<1>(d) : QString{}; }
    Input& setText(const QString& text)
    {
        if (text.isEmpty())
            d = Empty{};
        else
            d = text;
        return *this;
    }

    [[nodiscard]] InputItemList items() const
    {
        return isInputItemList() ? std::get<2>(d) : InputItemList{};
    }
    Input& setItems(const InputItemList& items)
    {
        if (items.isEmpty())
            d = Empty{};
        else
            d = items;
        return *this;
    }

    [[nodiscard]] bool operator==(const Input& that) const { return d == that.d; }

    [[nodiscard]] bool isEmpty() const { return !isText() && !isInputItemList(); }
    [[nodiscard]] bool isValid() const
    {
        return (isText() && !text().isEmpty()) || (isInputItemList() && items().isValid());
    }

    QJsonValue toJson() const
    {
        if (isText())
            return text();

        if (isInputItemList())
            return items().toJson();

        return {};
    }

    static Input fromJson(const QJsonValue& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        if (json.isString() && !json.toString().isEmpty())
            return {json.toString()};

        else if (json.isArray() && !json.toArray().isEmpty())
            return {InputItemList::fromJson(json.toArray(), ok)};

        else if (ok)
            *ok = false;

        return {};
    }

    static Input fromJson(const QJsonArray& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        if (json.isEmpty())
            return {};

        InputItemList items;

        for (const auto& i : json) {
            items.append(InputItem::fromJson(i.toObject()));
        }

        return {items};
    }

    // Input& operator=(const Input& that)
    // {
    //     d = that.d;
    //     return *this;
    // }
};

} // namespace ai

#endif // AI_CONFIG_INPUT_H
