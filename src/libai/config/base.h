#ifndef AI_CONFIG_BASE_H
#define AI_CONFIG_BASE_H

#include <QJsonArray>
#include <QJsonObject>
#include <QMetaEnum>
#include <QObject>

namespace ai {

enum struct Type {
    InputText,
    InputImage,
    InputFile,
    InputAudio,
    MessageContentInputItemList,
    InputItemList,
    ItemReference,
    Conversation,
    Message
};

class Empty
{
public:
    [[nodiscard]] bool operator==(const Empty &) const { return true; }
};

} // namespace ai

#endif // AI_CONFIG_BASE_H
