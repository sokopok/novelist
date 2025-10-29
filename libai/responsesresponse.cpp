#include "responsesresponse.h"
#include "responsesclient.h"

namespace ai {

bool ResponsesResponse::readJson(const QJsonObject &json, QStringList *errors)
{
    if (json.value(QStringLiteral("object")).toString() != QStringLiteral("response"))
        return false;

    if (!Response::readJson(json, errors))
        return false;

    if (extra().contains(QStringLiteral("background"))) {
        if (const auto v = extra().value(QStringLiteral("background")); v.isBool()) {
            setBackground(v.toBool());
            extra().remove(QStringLiteral("background"));
        } else if (errors) {
            errors->append(QStringLiteral("'background' is not a boolean"));
            return false;
        } else
            return false;
    }

    if (extra().contains(QStringLiteral("conversation"))) {
        if (const auto v = extra().value(QStringLiteral("conversation")); v.isObject()) {
            setConversation(Conversation::fromJson(v.toObject()));
            extra().remove(QStringLiteral("conversation"));
        } else if (const auto v = json.value("conversation"); v.isString()) {
            setConversation({v.toString()});
            extra().remove(QStringLiteral("conversation"));
        } else if (!v.isNull()) {
            if (errors)
                errors->append(QStringLiteral("'conversation' is not a string or object"));
            return false;
        }
    }

    // if (extra().contains(QStringLiteral("input"))) {
    //     if (const auto v = extra().value(QStringLiteral("input")); v.isArray()) {
    //         setInput(Input::fromJson(v.toArray()));
    //         extra().remove(QStringLiteral("input"));
    //     } else if (const auto v = json.value("input"); v.isString()) {
    //         setInput({v.toString()});
    //         extra().remove(QStringLiteral("input"));
    //     } else if (errors) {
    //         errors->append(QStringLiteral("input is not a string or array"));
    //         return false;
    //     } else
    //         return false;
    // }

    if (extra().contains(QStringLiteral("instructions"))) {
        if (const auto v = extra().value(QStringLiteral("instructions")); v.isString()) {
            setInstructions({v.toString()});
            extra().remove(QStringLiteral("instructions"));
        } else if (!v.isNull()) {
            if (errors)
                errors->append(QStringLiteral("'instructions' is not a string"));
            return false;
        }
    }

    if (extra().contains(QStringLiteral("max_output_tokens"))) {
        if (const auto v = extra().value(QStringLiteral("max_output_tokens")); v.isDouble()) {
            setMaxOutputTokens(v.toInt());
            extra().remove(QStringLiteral("max_output_tokens"));
        } else if (!v.isNull()) {
            if (errors)
                errors->append(QStringLiteral("'max_output_tokens' is not an integer"));
            return false;
        }
    }

    if (extra().contains(QStringLiteral("max_tool_calls"))) {
        if (const auto v = extra().value(QStringLiteral("max_tool_calls")); v.isDouble()) {
            setMaxToolCalls(v.toInt());
            extra().remove(QStringLiteral("max_tool_calls"));
        } else if (!v.isNull()) {
            if (errors)
                errors->append(QStringLiteral("'max_tool_calls' is not an integer"));
            return false;
        }
    }

    if (extra().contains(QStringLiteral("output"))) {
        if (const auto v = extra().value(QStringLiteral("output")); v.isArray()) {
            QList<OutputItem> output;
            const auto a = v.toArray();
            for (const auto o : a)
                output.append(OutputItem::fromJson(o.toObject()));
            setOutput(output);
            extra().remove(QStringLiteral("output"));
        } else if (!v.isNull()) {
            if (errors)
                errors->append(QStringLiteral("'output' is not a an array"));
            return false;
        }
    }

    if (extra().contains(QStringLiteral("parallel_tool_calls"))) {
        if (const auto v = extra().value(QStringLiteral("parallel_tool_calls")); v.isBool()) {
            setParallelToolCalls(v.toBool());
            extra().remove(QStringLiteral("parallel_tool_calls"));
        } else if (!v.isNull()) {
            if (errors)
                errors->append(QStringLiteral("'parallel_tool_calls' is not a boolean"));
            return false;
        }
    }

    if (extra().contains(QStringLiteral("previous_response_id"))) {
        if (const auto v = extra().value(QStringLiteral("previous_response_id")); v.isString()) {
            setPreviousResponseId(v.toString());
            extra().remove(QStringLiteral("previous_response_id"));
        } else if (!v.isNull()) {
            if (errors)
                errors->append(QStringLiteral("'previous_response_id' is not a string"));
            return false;
        }
    }

    if (extra().contains(QStringLiteral("prompt_cache_key"))) {
        if (const auto v = extra().value(QStringLiteral("prompt_cache_key")); v.isString()) {
            setPromptCacheKey(v.toString());
            extra().remove(QStringLiteral("prompt_cache_key"));
        } else if (!v.isNull()) {
            if (errors)
                errors->append(QStringLiteral("'prompt_cache_key' is not a string"));
            return false;
        }
    }

    if (extra().contains(QStringLiteral("safety_identifier"))) {
        if (const auto v = extra().value(QStringLiteral("safety_identifier")); v.isString()) {
            setSafetyIdentifier(v.toString());
            extra().remove(QStringLiteral("safety_identifier"));
        } else if (!v.isNull()) {
            if (errors)
                errors->append(QStringLiteral("'safety_identifier' is not a string"));
            return false;
        }
    }

    if (extra().contains(QStringLiteral("service_tier"))) {
        if (const auto v = extra().value(QStringLiteral("service_tier")); v.isString()) {
            setServiceTier(v.toString());
            extra().remove(QStringLiteral("service_tier"));
        } else if (!v.isNull()) {
            if (errors)
                errors->append(QStringLiteral("'service_tier' is not a string"));
            return false;
        }
    }

    if (extra().contains(QStringLiteral("store"))) {
        if (const auto v = extra().value(QStringLiteral("store")); v.isBool()) {
            setStored(v.toBool());
            extra().remove(QStringLiteral("store"));
        } else if (!v.isNull()) {
            if (errors)
                errors->append(QStringLiteral("'store' is not a boolean"));
            return false;
        }
    }

    if (extra().contains(QStringLiteral("temperature"))) {
        if (const auto v = extra().value(QStringLiteral("temperature")); v.isDouble()) {
            setTemperature(v.toInt());
            extra().remove(QStringLiteral("temperature"));
        } else if (!v.isNull()) {
            if (errors)
                errors->append(QStringLiteral("'temperature' is not a double"));
            return false;
        }
    }

    if (extra().contains(QStringLiteral("top_logprobs"))) {
        if (const auto v = extra().value(QStringLiteral("top_logprobs")); v.isDouble()) {
            setTopLogprobs(v.toInt());
            extra().remove(QStringLiteral("top_logprobs"));
        } else if (!v.isNull()) {
            if (errors)
                errors->append(QStringLiteral("'top_logprobs' is not an integer"));
            return false;
        }
    }

    if (extra().contains(QStringLiteral("top_p"))) {
        if (const auto v = extra().value(QStringLiteral("top_p")); v.isDouble()) {
            setTopP(v.toDouble());
            extra().remove(QStringLiteral("top_p"));
        } else if (!v.isNull()) {
            if (errors)
                errors->append(QStringLiteral("'top_p' is not a double"));
            return false;
        }
    }

    if (extra().contains(QStringLiteral("truncation"))) {
        if (const auto v = extra().value(QStringLiteral("truncation")); v.isString()) {
            setTruncation(v.toString());
            extra().remove(QStringLiteral("truncation"));
        } else if (!v.isNull()) {
            if (errors)
                errors->append(QStringLiteral("'truncation' is not a string"));
            return false;
        }
    }

    return true;
}

bool ResponsesResponse::writeJson(QJsonObject &json, bool full) const
{
    if (!Response::writeJson(json, full))
        return false;

    if (full || mBackground)
        json[QStringLiteral("background")] = mBackground;

    if (full || !mConversation.isEmpty())
        json[QStringLiteral("conversation")] = mConversation.toJson();

    // if (const auto v = input(); full || !v.isEmpty())
    //     json[QStringLiteral("input")] = v.toJson();

    if (full || !mInstructions.isEmpty())
        json[QStringLiteral("instructions")] = mInstructions;

    if (full || mMaxOutputTokens != 0)
        json[QStringLiteral("max_output_tokens")] = mMaxOutputTokens;

    if (full || mMaxToolCalls != 0)
        json[QStringLiteral("max_tool_calls")] = mMaxToolCalls;

    if (full || mParallelToolCalls == false)
        json[QStringLiteral("parallel_tool_calls")] = mParallelToolCalls;

    if (full || !mPreviousResponseId.isEmpty())
        json[QStringLiteral("previous_response_id")] = mPreviousResponseId;

    if (full || !mPromptCacheKey.isEmpty())
        json[QStringLiteral("prompt_cache_key")] = mPromptCacheKey;

    if (full || !mReasoning.isEmpty())
        json[QStringLiteral("reasoning")] = mReasoning.toJson();

    if (full || !mSafetyIdentifier.isEmpty())
        json[QStringLiteral("safety_identifier")] = mSafetyIdentifier;

    if (full || mServiceTier != ResponsesRequest::ServiceTier_Default)
        json[QStringLiteral("service_tier")] = serviceTierAsString();

    if (full || !mStored)
        json[QStringLiteral("store")] = mStored;

    if (full || mTemperature != 1.0)
        json[QStringLiteral("temperature")] = mTemperature;

    if (full || mTopLogprobs != 0)
        json[QStringLiteral("top_logprobs")] = mTopLogprobs;

    if (full || mTopP != 1.0)
        json[QStringLiteral("top_p")] = mTopP;

    if (full || mTruncation != ResponsesRequest::Truncation_Disabled)
        json[QStringLiteral("truncation")] = truncationAsString();

    if (full || !mOutput.isEmpty()) {
        QJsonArray a;
        for (const auto &output : mOutput)
            a.append(output.toJson());
        json[QStringLiteral("output")] = a;
    }

    return true;
}

const QMap<int, QString>
    ResponsesResponse::StatusKV{{Status_Cancelled, QStringLiteral("cancelled")},
                                {Status_Completed, QStringLiteral("completed")},
                                {Status_Failed, QStringLiteral("failed")},
                                {Status_InProgress, QStringLiteral("in_progress")},
                                {Status_Incomplete, QStringLiteral("incomplete")},
                                {Status_Queued, QStringLiteral("queued")}};

ResponsesClient *ResponsesResponse::client() const
{
    return qobject_cast<ResponsesClient *>(Response::client());
}

ResponsesResponse::ResponsesResponse(const ResponsesRequest &request,
                                     QNetworkReply *reply,
                                     ResponsesClient *client)
    : Response(request, reply, client)
    , mRequest{request}
{
    QObject::connect(this, &ResponsesResponse::finished, this, [this]() {
        for (const auto &output : std::as_const(mOutput)) {
            if (output.isImageGenerationCall()) {
                emit imageGenerated(output.imageGenerationCall().result(), QPrivateSignal{});
            } else if (output.isMessage()) {
                const auto message = output.message();
                QString text;
                for (const auto &content : message.content()) {
                    if (!text.isEmpty())
                        text += '\n';
                    if (content.isText())
                        text += content.text().text();
                    else if (content.isRefusal())
                        text += content.refusal().refusal();
                }
                emit textGenerated(text, QPrivateSignal{});
            } else if (output.isReasoning()) {
            }
        }
    });
}

// bool ResponsesResponse::readJson(const QJsonObject &json)
// {
//     if (!ai::ResponsesResponse::readJson(json))
//         return false;

//     if (const auto v = json.value("background"); v.isBool())
//         setBackground(v.toBool());

//     if (const auto v = json.value("conversation"); v.isString())
//         setConversation({v.toString()});
//     else if (v.isObject())
//         setConversation(Conversation::fromJson(v.toObject()));

//     if (const auto v = json.value("input"); v.isString())
//         setInput({v.toString()});
//     else if (v.isArray())
//         setInput(Input::fromJson(v.toArray()));

//     return true;
// }

// bool ResponsesResponse::writeJson(QJsonObject &json) const
// {
//     if (!ai::ResponsesResponse::writeJson(json))
//         return false;

//     if (const auto v = background())
//         json[QStringLiteral("background")] = v;

//     if (const auto v = conversation(); !v.isEmpty())
//         json[QStringLiteral("conversation")] = v.toJson();

//     if (const auto v = input(); !v.isEmpty())
//         json[QStringLiteral("input")] = v.toJson();

//     return true;
// }

} // namespace ai
