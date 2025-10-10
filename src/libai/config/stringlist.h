#ifndef AI_CONFIG_STRINGIST_H
#define AI_CONFIG_STRINGIST_H

#include "common.h"

namespace ai::config {

class StringList : public QStringList
{
public:
    StringList(const QStringList& items = {})
        : QStringList{items}
    {}

    [[nodiscard]] ai::config::Type objectType() const { return ai::config::Type::Type_StringList; }

    [[nodiscard]] bool isValid() const { return !isEmpty(); }

    QJsonArray toJson() const
    {
        QJsonArray array;
        for (const auto& item : *this)
            array.append(item);
        return array;
    }

    static StringList fromJson(const QJsonArray& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        StringList list;

        for (const auto& i : json)
            list.append(i.toString());

        return list;
    }
};

} // namespace ai::config

#endif // AI_CONFIG_STRINGIST_H
