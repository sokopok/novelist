#ifndef AI_CONFIG_EMPTY_H
#define AI_CONFIG_EMPTY_H

#include "common.h"

namespace ai {

class Empty
{
    Q_GADGET
    Q_PROPERTY(ai::UtilityType utilityType READ utilityType CONSTANT FINAL)
    Q_PROPERTY(QJsonObject extra READ extra FINAL)
    Q_PROPERTY(bool empty READ isEmpty FINAL)
    Q_PROPERTY(bool valid READ isValid FINAL)

public:
    Empty(const QJsonObject& extra = {})
        : x{extra}
    {}

    [[nodiscard]] ai::UtilityType utilityType() const { return UtilityType_Empty; }

    [[nodiscard]] QJsonObject extra() const { return x; }

    [[nodiscard]] bool operator==(const Empty& that) const { return x == that.x; }

    [[nodiscard]] bool isEmpty() const { return x.isEmpty(); }
    [[nodiscard]] bool isValid() const { return false; }

    QJsonObject toJson() const { return x; }

    static Empty fromJson(const QJsonObject& json, QStringList* errors = nullptr)
    {
        return {json};
        Q_UNUSED(errors)
    }

private:
    QJsonObject x;
};

} // namespace ai

#endif // AI_CONFIG_EMPTY_H
