#include "request.h"

namespace ai::images {

Request::Request()
{}

bool Request::readJson(const QJsonObject &json, QStringList *errors)
{
    bool ok = ai::Request::readJson(json);

    if (json.contains(QStringLiteral("prompt"))) {
        if (const auto v = json.value(QStringLiteral("prompt")); v.isString()) {
            if (const auto prompt = v.toString(); !prompt.isEmpty()) {
                setPrompt(v.toString());
                extra().remove(QStringLiteral("prompt"));
            } else {
                if (errors)
                    errors->append("prompt must not be empty");
                ok = false;
            }
        } else {
            if (errors)
                errors->append("prompt is not a string");
            ok = false;
        }
    }

    if (json.contains(QStringLiteral("background"))) {
        if (const auto v = json.value(QStringLiteral("background")); v.isString()) {
            setBackground(v.toString());
            extra().remove(QStringLiteral("background"));
        } else if (v.isDouble()) {
            setBackground(Request::toBackground(v.toInt()));
            extra().remove(QStringLiteral("background"));
        } else {
            if (errors)
                errors->append("background is not a string");
            ok = false;
        }
    }

    if (json.contains(QStringLiteral("model"))) {
        if (const auto v = json.value(QStringLiteral("model")); v.isString()) {
            setModel(v.toString());
            extra().remove(QStringLiteral("model"));
        } else if (v.isDouble()) {
            setModel(Request::toModel(v.toInt()));
            extra().remove(QStringLiteral("model"));
        } else {
            if (errors)
                errors->append("model is not a string");
            ok = false;
        }
    }

    if (json.contains(QStringLiteral("moderation"))) {
        if (const auto v = json.value(QStringLiteral("moderation")); v.isString()) {
            setModeration(v.toString());
            extra().remove(QStringLiteral("moderation"));
        } else if (v.isDouble()) {
            setModeration(Request::toModeration(v.toInt()));
            extra().remove(QStringLiteral("moderation"));
        } else {
            if (errors)
                errors->append("moderation is not a string");
            ok = false;
        }
    }

    if (json.contains(QStringLiteral("n"))) {
        if (const auto v = json.value(QStringLiteral("n")); v.isDouble()) {
            setN(v.toInt());
            extra().remove(QStringLiteral("n"));
        } else {
            if (errors)
                errors->append("n is not an integer");
            ok = false;
        }
    }

    return ok;
}

bool Request::writeJson(QJsonObject &json, bool full) const
{
    if (!ai::Request::writeJson(json, full))
        return false;

    json[QStringLiteral("prompt")] = prompt();
    json[QStringLiteral("model")] = modelAsString();
    // json[QStringLiteral("quality")] = qualityAsString();
    // json[QStringLiteral("stream")] = isStreaming();
    json[QStringLiteral("size")] = sizeAsString();

    if (mResponseFormat != ResponseFormat_Url)
        json[QStringLiteral("response_format")] = responseFormatAsString();

    if (mPartialImages != 0)
        json[QStringLiteral("partial_images")] = partialImages();

    if (mN != 1)
        json[QStringLiteral("n")] = n();

    if (mModel == Model_GptImage1) {
        json[QStringLiteral("background")] = backgroundAsString();
        json[QStringLiteral("moderation")] = moderationAsString();
        json[QStringLiteral("output_format")] = outputFormatAsString();
        json[QStringLiteral("style")] = styleAsString();
        if (mOutputFormat == OutputFormat_Png || mOutputFormat == OutputFormat_Jpeg)
            json[QStringLiteral("output_compression")] = outputCompression();
    }

    return true;
}

} // namespace ai::images
