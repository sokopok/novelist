#ifndef AI_JSON_H
#define AI_JSON_H

#include <QJsonObject>

namespace ai {

inline QJsonObject merge(const QJsonObject& object, const QJsonObject& additions)
{
    QJsonObject result = object;
    for (auto it = additions.begin(); it != additions.end(); ++it)
        result.insert(it.key(), it.value());
    return result;
}

} // namespace ai
#endif // AI_JSON_H
