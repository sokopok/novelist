#include "response.h"
#include "client.h"

namespace ai::images {

bool Response::readJson(const QJsonObject &json, QStringList *errors)
{
    if (!ai::Response::readJson(json, errors))
        return false;

    if (extra().contains(QStringLiteral("background"))) {
        if (const auto v = extra().value(QStringLiteral("background")); v.isString()) {
            setBackground(v.toString());
            extra().remove(QStringLiteral("background"));
        } else if (errors) {
            errors->append(QStringLiteral("background is not a string"));
            return false;
        } else
            return false;
    }

    if (extra().contains(QStringLiteral("created"))) {
        if (const auto v = extra().value(QStringLiteral("created")); v.isDouble()) {
            setCreated(v.toInt());
            extra().remove(QStringLiteral("created"));
        } else if (errors) {
            errors->append(QStringLiteral("created is not an int"));
            return false;
        } else
            return false;
    }

    if (extra().contains(QStringLiteral("data"))) {
        if (const auto v = extra().value(QStringLiteral("data")); v.isObject()) {
            setData(ImageResponseData::fromJson(v.toObject()));
            extra().remove(QStringLiteral("data"));
        } else if (errors) {
            errors->append(QStringLiteral("data is not an object"));
            return false;
        } else
            return false;
    }

    if (extra().contains(QStringLiteral("output_format"))) {
        if (const auto v = extra().value(QStringLiteral("output_format")); v.isString()) {
            setOutputFormat(v.toString());
            extra().remove(QStringLiteral("output_format"));
        } else if (errors) {
            errors->append(QStringLiteral("output_format is not a string"));
            return false;
        } else
            return false;
    }

    if (extra().contains(QStringLiteral("quality"))) {
        if (const auto v = extra().value(QStringLiteral("quality")); v.isString()) {
            setQuality(v.toString());
            extra().remove(QStringLiteral("quality"));
        } else if (errors) {
            errors->append(QStringLiteral("quality is not a string"));
            return false;
        } else
            return false;
    }

    if (extra().contains(QStringLiteral("size"))) {
        if (const auto v = extra().value(QStringLiteral("size")); v.isString()) {
            setSize(v.toString());
            extra().remove(QStringLiteral("size"));
        } else if (errors) {
            errors->append(QStringLiteral("size is not a string"));
            return false;
        } else
            return false;
    }

    if (extra().contains(QStringLiteral("usage"))) {
        if (const auto v = extra().value(QStringLiteral("usage")); v.isObject()) {
            setUsage(ImageResponseUsage::fromJson(v.toObject()));
            extra().remove(QStringLiteral("usage"));
        } else if (errors) {
            errors->append(QStringLiteral("usage is not an object"));
            return false;
        } else
            return false;
    }

    return true;
}

bool Response::writeJson(QJsonObject &json, bool full) const
{
    if (!ai::Response::writeJson(json, full))
        return false;

    if (full || mBackground != Request::Background_Auto)
        json[QStringLiteral("background")] = backgroundAsString();

    if (full || mCreated != 0)
        json[QStringLiteral("created")] = mCreated;

    if (full || !mData.isEmpty())
        json[QStringLiteral("data")] = mData.toJson();

    if (full || mOutputFormat != Request::OutputFormat_Png)
        json[QStringLiteral("output_format")] = outputFormatAsString();

    if (full || mQuality != Request::Quality_Auto)
        json[QStringLiteral("quality")] = qualityAsString();

    if (full || mSize != Request::Size_Auto)
        json[QStringLiteral("size")] = sizeAsString();

    if (full || !mUsage.isEmpty())
        json[QStringLiteral("usage()")] = mUsage.toJson();

    return true;
}

Response::Response(const Request &request, QNetworkReply *reply, Client *client)
    : ai::Response(request, reply, client)
    , mRequest{request}
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

} // namespace ai::images
