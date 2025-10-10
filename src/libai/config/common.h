#ifndef AI_CONFIG_COMMON_H
#define AI_CONFIG_COMMON_H

#include <QBitArray>
#include <QJsonArray>
#include <QJsonObject>
#include <QMetaEnum>
#include <QObject>

namespace ai {

enum UtilityType {
    UtilityType_Empty,
    UtilityType_Error,
    UtilityType_ImageResponseData,
    UtilityType_ImageResponseUsage,
    UtilityType_InputText,
    UtilityType_InputImage,
    UtilityType_OutputMessageContentList,
    UtilityType_InputFile,
    UtilityType_InputAudio,
    UtilityType_MessageContentInputItemList,
    UtilityType_InputItemList,
    UtilityType_OutputItemList,
    UtilityType_Refusal,
    UtilityType_Prompt,
    UtilityType_OutputText,
    UtilityType_OutputMessageContentItemList,
    UtilityType_OutputMessageContentItem,
    UtilityType_OutputMessage,
    UtilityType_ImageGenerationCall,
    UtilityType_ItemReference,
    UtilityType_Conversation,
    UtilityType_ImageGenerationTool,
    UtilityType_Message,
    UtilityType_Reasoning,
    UtilityType_StreamOptions,
    UtilityType_StringList,
    UtilityType_IncludeList
};

} // namespace ai

#endif // AI_CONFIG_COMMON_H
