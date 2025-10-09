#ifndef AI_CONFIG_BASE_H
#define AI_CONFIG_BASE_H

#include <QBitArray>
#include <QJsonArray>
#include <QJsonObject>
#include <QMetaEnum>
#include <QObject>

namespace ai {

enum struct AiObjectType {
    Error,
    InputText,
    InputImage,
    OutputMessageContentList,
    InputFile,
    InputAudio,
    MessageContentInputItemList,
    InputItemList,
    OutputItemList,
    Refusal,
    Prompt,
    OutputText,
    OutputMessageContentItemList,
    OutputMessageContentItem,
    OutputMessage,
    ImageGenerationCall,
    ItemReference,
    Conversation,
    Message,
    Reasoning,
    StreamOptions,
    StringList,
    IncludeList
};

class Empty
{
public:
    [[nodiscard]] bool operator==(const Empty &) const { return true; }
};

} // namespace ai

#endif // AI_CONFIG_BASE_H
