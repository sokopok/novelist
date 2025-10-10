#ifndef AI_CONFIG_INPUTITEM_H
#define AI_CONFIG_INPUTITEM_H

#include "empty.h"
#include "itemreference.h"
#include "message.h"

namespace ai {

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

    [[nodiscard]] ai::UtilityType utilityType() const { return UtilityType_InputItemList; }

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

} // namespace ai

#endif // AI_CONFIG_INPUTITEM_H
