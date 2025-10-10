#include "request.h"

namespace ai::responses {

Request::Request() {}

bool Request::readJson(const QJsonObject &json, QStringList *errors)
{
    bool ok = ai::Request::readJson(json);

    if (mExtra.contains(QStringLiteral("background"))) {
        if (const auto v = mExtra.value(QStringLiteral("background")); v.isBool()) {
            setBackground(v.toBool());
            mExtra.remove(QStringLiteral("background"));
        } else {
            if (errors)
                errors->append("background is not a bool");
            ok = false;
        }
    }

    if (mExtra.contains(QStringLiteral("conversation"))) {
        if (const auto v = mExtra.value(QStringLiteral("conversation")); v.isObject()) {
            setConversation(Conversation::fromJson(v.toObject()));
            mExtra.remove(QStringLiteral("conversation"));
        } else {
            if (errors)
                errors->append("conversation is not an object");
            ok = false;
        }
    }

    if (mExtra.contains(QStringLiteral("include"))) {
        if (const auto v = mExtra.value(QStringLiteral("include")); v.isArray()) {
            setInclude(IncludeList::fromJson(v.toArray()));
            mExtra.remove(QStringLiteral("include"));
        } else {
            if (errors)
                errors->append("include is not an array");
            ok = false;
        }
    }

    if (mExtra.contains(QStringLiteral("input"))) {
        if (const auto v = mExtra.value(QStringLiteral("input")); v.isObject()) {
            setInput(Input::fromJson(v.toObject()));
            mExtra.remove(QStringLiteral("input"));
        } else {
            if (errors)
                errors->append("input is not an object");
            ok = false;
        }
    }

    if (mExtra.contains(QStringLiteral("instructions"))) {
        if (const auto v = mExtra.value(QStringLiteral("instructions")); v.isString()) {
            setInstructions(v.toString());
            mExtra.remove(QStringLiteral("instructions"));
        } else {
            if (errors)
                errors->append("instructions is not a string");
            ok = false;
        }
    }

    if (mExtra.contains(QStringLiteral("max_output_tokens"))) {
        if (const auto v = mExtra.value(QStringLiteral("max_output_tokens")); v.isDouble()) {
            setMaxOutputTokens(v.toInt());
            mExtra.remove(QStringLiteral("max_output_tokens"));
        } else {
            if (errors)
                errors->append("max_output_tokens is not an int");
            ok = false;
        }
    }

    if (mExtra.contains(QStringLiteral("max_tool_calls"))) {
        if (const auto v = mExtra.value(QStringLiteral("max_tool_calls")); v.isDouble()) {
            setMaxToolCalls(v.toInt());
            mExtra.remove(QStringLiteral("max_tool_calls"));
        } else {
            if (errors)
                errors->append("max_tool_calls is not an int");
            ok = false;
        }
    }

    if (mExtra.contains(QStringLiteral("metadata"))) {
        if (const auto v = mExtra.value(QStringLiteral("metadata")); v.isObject()) {
            setMetadata(v.toObject().toVariantMap());
            mExtra.remove(QStringLiteral("metadata"));
        } else {
            if (errors)
                errors->append("metadata is not an object");
            ok = false;
        }
    }

    if (mExtra.contains(QStringLiteral("model"))) {
        if (const auto v = mExtra.value(QStringLiteral("model")); v.isString()) {
            setModel(v.toString());
            mExtra.remove(QStringLiteral("model"));
        } else {
            if (errors)
                errors->append("model is not a string");
            ok = false;
        }
    }

    if (mExtra.contains(QStringLiteral("parallel_tool_calls"))) {
        if (const auto v = mExtra.value(QStringLiteral("parallel_tool_calls")); v.isBool()) {
            setParallelToolCalls(v.toBool());
            mExtra.remove(QStringLiteral("parallel_tool_calls"));
        } else {
            if (errors)
                errors->append("parallel_tool_calls is not a boolean");
            ok = false;
        }
    }

    if (mExtra.contains(QStringLiteral("previous_response_id"))) {
        if (const auto v = mExtra.value(QStringLiteral("previous_response_id")); v.isString()) {
            setPreviousResponseId(v.toString());
            mExtra.remove(QStringLiteral("previous_response_id"));
        } else {
            if (errors)
                errors->append("previous_response_id is not a string");
            ok = false;
        }
    }

    if (mExtra.contains(QStringLiteral("prompt"))) {
        if (const auto v = mExtra.value(QStringLiteral("prompt")); v.isObject()) {
            setPrompt(Prompt::fromJson(v.toObject()));
            mExtra.remove(QStringLiteral("prompt"));
        } else {
            if (errors)
                errors->append("prompt is not an object");
            ok = false;
        }
    }

    if (mExtra.contains(QStringLiteral("reasoning"))) {
        if (const auto v = mExtra.value(QStringLiteral("reasoning")); v.isObject()) {
            setReasoning(Reasoning::fromJson(v.toObject()));
            mExtra.remove(QStringLiteral("reasoning"));
        } else {
            if (errors)
                errors->append("reasoning is not an object");
            ok = false;
        }
    }

    if (mExtra.contains(QStringLiteral("safety_identifier"))) {
        if (const auto v = mExtra.value(QStringLiteral("safety_identifier")); v.isString()) {
            setSafetyIdentifier(v.toString());
            mExtra.remove(QStringLiteral("safety_identifier"));
        } else {
            if (errors)
                errors->append("safety_identifier is not a string");
            ok = false;
        }
    }

    if (mExtra.contains(QStringLiteral("service_tier"))) {
        if (const auto v = mExtra.value(QStringLiteral("service_tier")); v.isString()) {
            setServiceTier(v.toString());
            mExtra.remove(QStringLiteral("service_tier"));
        } else {
            if (errors)
                errors->append("service_tier is not a string");
            ok = false;
        }
    }

    if (mExtra.contains(QStringLiteral("store"))) {
        if (const auto v = mExtra.value(QStringLiteral("store")); v.isBool()) {
            setStored(v.toBool());
            mExtra.remove(QStringLiteral("store"));
        } else {
            if (errors)
                errors->append("store is not a boolean");
            ok = false;
        }
    }

    if (mExtra.contains(QStringLiteral("stream"))) {
        if (const auto v = mExtra.value(QStringLiteral("stream")); v.isBool()) {
            setStreaming(v.toBool());
            mExtra.remove(QStringLiteral("stream"));
        } else {
            if (errors)
                errors->append("stream is not a boolean");
            ok = false;
        }
    }

    if (mExtra.contains(QStringLiteral("stream_options"))) {
        if (const auto v = mExtra.value(QStringLiteral("stream_options")); v.isObject()) {
            setStreamOptions(StreamOptions::fromJson(v.toObject()));
            mExtra.remove(QStringLiteral("stream_options"));
        } else {
            if (errors)
                errors->append("stream_options is not an object");
            ok = false;
        }
    }

    // TemperatureAttribute,
    //     TextAttribute,
    //     ToolChoiceAttribute,
    //     ToolsAttribute,
    //     TopLogprobsAttribute,
    //     TopPAttribute,
    //     TruncationAttribute,

    return ok;
}

bool Request::writeJson(QJsonObject &json, bool full) const
{
    if (!ai::Request::writeJson(json, full))
        return false;

    if (full || mBackground)
        json[QStringLiteral("background")] = mBackground;

    if (full || !mConversation.isEmpty())
        json[QStringLiteral("conversation")] = mConversation.toJson();

    if (full || !mInclude.isEmpty())
        json[QStringLiteral("include")] = mInclude.toJson();

    if (full || !mInput.isEmpty())
        json[QStringLiteral("input")] = mInput.toJson();

    if (full || !mInstructions.isEmpty())
        json[QStringLiteral("instructions")] = mInstructions;

    if (full || mMaxOutputTokens != 0)
        json[QStringLiteral("max_output_tokens")] = mMaxOutputTokens;

    if (full || mMaxToolCalls != 0)
        json[QStringLiteral("max_tool_calls")] = mMaxToolCalls;

    if (full || !mMetadata.isEmpty())
        json[QStringLiteral("metadata")] = QJsonObject::fromVariantMap(mMetadata);

    if (const auto model = modelAsString(); full || !model.isEmpty())
        json[QStringLiteral("model")] = model;

    if (full || mParallelToolCalls != 0)
        json[QStringLiteral("parallel_tool_calls")] = mParallelToolCalls;

    if (full || !mPreviousResponseId.isEmpty())
        json[QStringLiteral("previous_response_id")] = mPreviousResponseId;

    if (full || !mPrompt.isEmpty())
        json[QStringLiteral("prompt")] = mPrompt.toJson();

    if (full || !mPromptCacheKey.isEmpty())
        json[QStringLiteral("prompt_cache_key")] = mPromptCacheKey;

    if (full || !mReasoning.isEmpty())
        json[QStringLiteral("reasoning")] = mReasoning.toJson();

    if (full || !mSafetyIdentifier.isEmpty())
        json[QStringLiteral("safety_identifier")] = mSafetyIdentifier;

    if (full || mServiceTier != ServiceTier_Auto)
        json[QStringLiteral("service_tier")] = serviceTierAsString();

    if (full || !mStore)
        json[QStringLiteral("store")] = mStore;

    if (full || mStream)
        json[QStringLiteral("stream")] = mStream;

    if (full || !mStreamOptions.isEmpty())
        json[QStringLiteral("stream_options")] = mStreamOptions.toJson();

    if (full || mTemperature != 1.0)
        json[QStringLiteral("temperature")] = mTemperature;

    if (full || mTopLogprobs != 0)
        json[QStringLiteral("top_logprobs")] = mTopLogprobs;

    if (full || mTopP != 1.0)
        json[QStringLiteral("top_p")] = mTopP;

    if (full || mTruncation != Truncation_Disabled)
        json[QStringLiteral("truncation")] = truncationAsString();

    return true;
}

const QMap<int, QString> Request::ModelKV{{Model_Gpt5, QStringLiteral("gpt-5")},
                                          {Model_Gpt5Nano, QStringLiteral("gpt-5-nano")},
                                          {Model_Gpt5Mini, QStringLiteral("gpt-5-mini")},
                                          {Model_Gpt5Pro, QStringLiteral("gpt-5-pro")},
                                          {Model_Gpt41, QStringLiteral("gpt-4.1")},
                                          {Model_Gpt41Mini, QStringLiteral("gpt-4.1-mini")}};

const QMap<int, QString> Request::ServiceTierKV{{ServiceTier_Auto, QStringLiteral("auto")},
                                                {ServiceTier_Default, QStringLiteral("default")},
                                                {ServiceTier_Flex, QStringLiteral("flex")},
                                                {ServiceTier_Priority, QStringLiteral("priority")}};

const QMap<int, QString> Request::TruncationKV{{Truncation_Auto, QStringLiteral("auto")},
                                               {Truncation_Disabled, QStringLiteral("disabled")}};

} // namespace ai::responses
