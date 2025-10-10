#ifndef AI_CONFIG_COMMON_H
#define AI_CONFIG_COMMON_H

#include <QBitArray>
#include <QJsonArray>
#include <QJsonObject>
#include <QMetaEnum>
#include <QObject>

namespace ai::config {

enum struct Type {
    Type_Empty,
    Type_Error,
    Type_ImageResponseData,
    Type_ImageResponseUsage,
    Type_InputText,
    Type_InputImage,
    Type_OutputMessageContentList,
    Type_InputFile,
    Type_InputAudio,
    Type_MessageContentInputItemList,
    Type_InputItemList,
    Type_OutputItemList,
    Type_Refusal,
    Type_Prompt,
    Type_OutputText,
    Type_OutputMessageContentItemList,
    Type_OutputMessageContentItem,
    Type_OutputMessage,
    Type_ImageGenerationCall,
    Type_ItemReference,
    Type_Conversation,
    Type_ImageGenerationTool,
    Type_Message,
    Type_Reasoning,
    Type_StreamOptions,
    Type_StringList,
    Type_IncludeList
};

} // namespace ai::config

#endif // AI_CONFIG_COMMON_H
