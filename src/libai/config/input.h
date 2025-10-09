#ifndef AI_CONFIG_INPUT_H
#define AI_CONFIG_INPUT_H

#include "../json.h"
#include "inputitem.h"

namespace ai {

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
        : Input{Empty{}}
    {}
    // Input(const QString& data)
    //     : d{data}
    // {}
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

    [[nodiscard]] bool isEmpty() const { return !isValid(); }
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

    Input merge(const Input& that) const
    {
        InputItemList list = items();
        if (isText())
            list.append({Message{{text()}, QStringLiteral("user")}});

        if (that.isText())
            list.append({Message{{that.text()}, QStringLiteral("user")}});
        else
            list.append(that.items());

        return {list};
    }
    // Input& operator=(const Input& that)
    // {
    //     d = that.d;
    //     return *this;
    // }
};

} // namespace ai

#endif // AI_CONFIG_INPUT_H
