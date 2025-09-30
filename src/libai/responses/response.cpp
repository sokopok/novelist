#include "response.h"
#include "client.h"

namespace ai::responses {

bool ResponseData::readJson(const QJsonObject &json, QStringList *errors)
{
    if (json.value(QStringLiteral("object")).toString() != QStringLiteral("response"))
        return false;

    if (!ai::ResponseData::readJson(json, errors))
        return false;

    if (mExtra.contains(QStringLiteral("background"))) {
        if (const auto v = mExtra.value(QStringLiteral("background")); v.isBool()) {
            setBackground(v.toBool());
            mExtra.remove(QStringLiteral("background"));
        } else if (errors) {
            errors->append(QStringLiteral("background is not a boolean"));
            return false;
        } else
            return false;
    }

    if (mExtra.contains(QStringLiteral("conversation"))) {
        if (const auto v = mExtra.value(QStringLiteral("conversation")); v.isObject()) {
            setConversation(Conversation::fromJson(v.toObject()));
            mExtra.remove(QStringLiteral("conversation"));
        } else if (const auto v = json.value("conversation"); v.isString()) {
            setConversation({v.toString()});
            mExtra.remove(QStringLiteral("conversation"));
        } else if (errors) {
            errors->append(QStringLiteral("conversation is not a string or object"));
            return false;
        } else
            return false;
    }

    if (mExtra.contains(QStringLiteral("input"))) {
        if (const auto v = mExtra.value(QStringLiteral("input")); v.isArray()) {
            setInput(Input::fromJson(v.toArray()));
            mExtra.remove(QStringLiteral("input"));
        } else if (const auto v = json.value("input"); v.isString()) {
            setInput({v.toString()});
            mExtra.remove(QStringLiteral("input"));
        } else if (errors) {
            errors->append(QStringLiteral("input is not a string or array"));
            return false;
        } else
            return false;
    }

    if (mExtra.contains(QStringLiteral("instructions"))) {
        if (const auto v = mExtra.value(QStringLiteral("instructions")); v.isString()) {
            setInstructions({v.toString()});
            mExtra.remove(QStringLiteral("instructions"));
        } else if (errors) {
            errors->append(QStringLiteral("instructions is not a string"));
            return false;
        } else
            return false;
    }

    if (mExtra.contains(QStringLiteral("max_output_tokens"))) {
        if (const auto v = mExtra.value(QStringLiteral("max_output_tokens")); v.isDouble()) {
            setMaxOutputTokens(v.toInt());
            mExtra.remove(QStringLiteral("max_output_tokens"));
        } else if (errors) {
            errors->append(QStringLiteral("max_output_tokens is not an integer"));
            return false;
        } else
            return false;
    }

    if (mExtra.contains(QStringLiteral("max_tool_calls"))) {
        if (const auto v = mExtra.value(QStringLiteral("max_tool_calls")); v.isDouble()) {
            setMaxToolCalls(v.toInt());
            mExtra.remove(QStringLiteral("max_tool_calls"));
        } else if (errors) {
            errors->append(QStringLiteral("max_tool_calls is not an integer"));
            return false;
        } else
            return false;
    }

    if (mExtra.contains(QStringLiteral("output"))) {
        if (const auto v = mExtra.value(QStringLiteral("output")); v.isArray()) {
            setOutput(Output::fromJson(v.toArray()));
            mExtra.remove(QStringLiteral("output"));
        } else if (errors) {
            errors->append(QStringLiteral("output is not a an array"));
            return false;
        } else
            return false;
    }

    if (mExtra.contains(QStringLiteral("parallel_tool_calls"))) {
        if (const auto v = mExtra.value(QStringLiteral("parallel_tool_calls")); v.isBool()) {
            setParallelToolCalls(v.toBool());
            mExtra.remove(QStringLiteral("parallel_tool_calls"));
        } else if (errors) {
            errors->append(QStringLiteral("max_tool_calls is not a boolean"));
            return false;
        } else
            return false;
    }

    if (mExtra.contains(QStringLiteral("previous_response_id"))) {
        if (const auto v = mExtra.value(QStringLiteral("previous_response_id")); v.isString()) {
            setPreviousResponseId(v.toString());
            mExtra.remove(QStringLiteral("previous_response_id"));
        } else if (errors) {
            errors->append(QStringLiteral("previous_response_id is not a string"));
            return false;
        } else
            return false;
    }

    if (mExtra.contains(QStringLiteral("prompt_cache_key"))) {
        if (const auto v = mExtra.value(QStringLiteral("prompt_cache_key")); v.isString()) {
            setPromptCacheKey(v.toString());
            mExtra.remove(QStringLiteral("prompt_cache_key"));
        } else if (errors) {
            errors->append(QStringLiteral("prompt_cache_key is not a string"));
            return false;
        } else
            return false;
    }

    if (mExtra.contains(QStringLiteral("safety_identifier"))) {
        if (const auto v = mExtra.value(QStringLiteral("safety_identifier")); v.isString()) {
            setSafetyIdetifier(v.toString());
            mExtra.remove(QStringLiteral("safety_identifier"));
        } else if (errors) {
            errors->append(QStringLiteral("safety_identifier is not a string"));
            return false;
        } else
            return false;
    }

    if (mExtra.contains(QStringLiteral("service_tier"))) {
        if (const auto v = mExtra.value(QStringLiteral("service_tier")); v.isString()) {
            setServiceTier(v.toString());
            mExtra.remove(QStringLiteral("service_tier"));
        } else if (errors) {
            errors->append(QStringLiteral("service_tier is not a string"));
            return false;
        } else
            return false;
    }

    if (mExtra.contains(QStringLiteral("stored"))) {
        if (const auto v = mExtra.value(QStringLiteral("stored")); v.isBool()) {
            setStored(v.toBool());
            mExtra.remove(QStringLiteral("stored"));
        } else if (errors) {
            errors->append(QStringLiteral("stored is not a boolean"));
            return false;
        } else
            return false;
    }

    if (mExtra.contains(QStringLiteral("temperature"))) {
        if (const auto v = mExtra.value(QStringLiteral("temperature")); v.isDouble()) {
            setTemperature(v.toInt());
            mExtra.remove(QStringLiteral("temperature"));
        } else if (errors) {
            errors->append(QStringLiteral("temperature is not a double"));
            return false;
        } else
            return false;
    }

    if (mExtra.contains(QStringLiteral("top_logprobs"))) {
        if (const auto v = mExtra.value(QStringLiteral("top_logprobs")); v.isDouble()) {
            setTopLogprobs(v.toInt());
            mExtra.remove(QStringLiteral("top_logprobs"));
        } else if (errors) {
            errors->append(QStringLiteral("top_logprobs is not an integer"));
            return false;
        } else
            return false;
    }

    if (mExtra.contains(QStringLiteral("top_p"))) {
        if (const auto v = mExtra.value(QStringLiteral("top_p")); v.isDouble()) {
            setTopP(v.toDouble());
            mExtra.remove(QStringLiteral("top_p"));
        } else if (errors) {
            errors->append(QStringLiteral("top_p is not a double"));
            return false;
        } else
            return false;
    }

    if (mExtra.contains(QStringLiteral("truncation"))) {
        if (const auto v = mExtra.value(QStringLiteral("truncation")); v.isDouble()) {
            setTruncation(toTruncation(v.toInt()));
            mExtra.remove(QStringLiteral("truncation"));
        } else if (v.isString()) {
            setTruncation(v.toString());
            mExtra.remove(QStringLiteral("truncation"));
        } else if (errors) {
            errors->append(QStringLiteral("truncation is not a string or integer"));
            return false;
        } else
            return false;
    }

    return true;
}

bool ResponseData::writeJson(QJsonObject &json, bool full) const
{
    if (!ai::ResponseData::writeJson(json, full))
        return false;

    if (const auto v = background(); full || v)
        json[QStringLiteral("background")] = v;

    if (const auto v = conversation(); full || !v.isEmpty())
        json[QStringLiteral("conversation")] = v.toJson();

    if (const auto v = input(); full || !v.isEmpty())
        json[QStringLiteral("input")] = v.toJson();

    if (const auto v = instructions(); full || !v.isEmpty())
        json[QStringLiteral("instructions")] = v;

    if (const auto v = maxOutputTokens(); full || v != 0)
        json[QStringLiteral("max_output_tokens")] = v;

    if (const auto v = maxToolCalls(); full || v != 0)
        json[QStringLiteral("max_tool_calls")] = v;

    if (const auto v = parallelToolCalls(); full || v != 0)
        json[QStringLiteral("parallel_tool_calls")] = v;

    if (const auto v = previousResponseId(); full || !v.isEmpty())
        json[QStringLiteral("previous_response_id")] = v;

    if (const auto v = promptCacheKey(); full || !v.isEmpty())
        json[QStringLiteral("prompt_cache_key")] = v;

    if (const auto v = reasoning(); full || !v.isEmpty())
        json[QStringLiteral("reasoning")] = v.toJson();

    if (const auto v = safetyIdentifier(); full || !v.isEmpty())
        json[QStringLiteral("safety_identifier")] = v;

    if (const auto v = serviceTier(); full || !v.isEmpty())
        json[QStringLiteral("service_tier")] = v;

    json[QStringLiteral("stored")] = isStored();

    json[QStringLiteral("temperature")] = temperature();
    json[QStringLiteral("top_logprobs")] = topLogprobs();
    json[QStringLiteral("top_p")] = topP();
    json[QStringLiteral("truncation")] = toString(truncation());

    if (const auto v = safetyIdentifier(); full || !v.isEmpty())
        json[QStringLiteral("safety_identifier")] = v;

    if (const auto v = safetyIdentifier(); full || !v.isEmpty())
        json[QStringLiteral("safety_identifier")] = v;

    if (const auto v = output(); full || !v.isEmpty())
        json[QStringLiteral("output")] = v.toJson();

    return true;
}

Response::Response(const Request &request, QNetworkReply *reply, Client *client)
    : Response(new ResponseData, request, reply, client)
{}

Response::Response(ResponseData *data, const Request &request, QNetworkReply *reply, Client *client)
    : ai::Response{data ? data : new ResponseData, request, reply, client}
{}

// bool Response::readJson(const QJsonObject &json)
// {
//     if (!ai::Response::readJson(json))
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

// bool Response::writeJson(QJsonObject &json) const
// {
//     if (!ai::Response::writeJson(json))
//         return false;

//     if (const auto v = background())
//         json[QStringLiteral("background")] = v;

//     if (const auto v = conversation(); !v.isEmpty())
//         json[QStringLiteral("conversation")] = v.toJson();

//     if (const auto v = input(); !v.isEmpty())
//         json[QStringLiteral("input")] = v.toJson();

//     return true;
// }

} // namespace ai::responses
