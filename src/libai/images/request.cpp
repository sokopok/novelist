#include "request.h"

namespace ai::images {

RequestData *Request::d()
{
    return static_cast<RequestData *>(ai::Request::d.data());
}

const RequestData *Request::d() const
{
    return static_cast<const RequestData *>(ai::Request::d.data());
}

Request::Request()
    : Request(new RequestData)
{}

QString Request::prompt() const
{
    return d()->prompt();
}

Request &Request::setPrompt(const QString &prompt)
{
    d()->setPrompt(prompt);
    return *this;
}

Request &Request::resetPrompt()
{
    d()->resetPrompt();
    return *this;
}

Request::Background Request::background() const
{
    return d()->background();
}

Request &Request::setBackground(Request::Background background)
{
    d()->setBackground(background);
    return *this;
}

Request &Request::setBackground(const QString &background)
{
    d()->setBackground(background);
    return *this;
}

Request &Request::resetBackground()
{
    d()->resetBackground();
    return *this;
}

Request::Model Request::model() const
{
    return d()->model();
}

Request &Request::setModel(Model model)
{
    d()->setModel(model);
    return *this;
}

Request &Request::setModel(const QString &model)
{
    d()->setModel(model);
    return *this;
}

Request &Request::resetModel()
{
    d()->resetModel();
    return *this;
}

Request::Moderation Request::moderation() const
{
    return d()->moderation();
}

Request &Request::setModeration(Moderation moderation)
{
    d()->setModeration(moderation);
    return *this;
}

Request &Request::setModeration(const QString &moderation)
{
    d()->setModeration(moderation);
    return *this;
}

Request &Request::resetModeration()
{
    d()->resetModeration();
    return *this;
}

int Request::n() const
{
    return d()->n();
}

Request &Request::setN(int n)
{
    d()->setN(n);
    return *this;
}

Request &Request::resetN()
{
    d()->resetN();
    return *this;
}

int Request::outputCompression() const
{
    return d()->outputCompression();
}

Request &Request::setOutputCompression(int outputCompression)
{
    d()->setOutputCompression(outputCompression);
    return *this;
}

Request &Request::resetOutputCompression()
{
    setOutputCompression({});
    return *this;
}

Request::OutputFormat Request::outputFormat() const
{
    return d()->outputFormat();
}

Request &Request::setOutputFormat(OutputFormat outputFormat)
{
    d()->setOutputFormat(outputFormat);
    return *this;
}

Request &Request::setOutputFormat(const QString &outputFormat)
{
    d()->setOutputFormat(outputFormat);
    return *this;
}

Request &Request::resetOutputFormat()
{
    d()->resetOutputFormat();
    return *this;
}

int Request::partialImages() const
{
    return d()->partialImages();
}

Request &Request::setPartialImages(int partialImages)
{
    d()->setPartialImages(partialImages);
    return *this;
}

Request &Request::resetPartialImages()
{
    d()->resetPartialImages();
    return *this;
}

Request::Quality Request::quality() const
{
    return d()->quality();
}

Request &Request::setQuality(Quality quality)
{
    d()->setQuality(quality);
    return *this;
}

Request &Request::setQuality(const QString &quality)
{
    d()->setQuality(quality);
    return *this;
}

Request &Request::resetQuality()
{
    d()->resetQuality();
    return *this;
}

Request::ResponseFormat Request::responseFormat() const
{
    return d()->responseFormat();
}

Request &Request::setResponseFormat(ResponseFormat responseFormat)
{
    d()->setResponseFormat(responseFormat);
    return *this;
}

Request &Request::setResponseFormat(const QString &responseFormat)
{
    d()->setResponseFormat(responseFormat);
    return *this;
}

Request &Request::resetResponseFormat()
{
    d()->resetResponseFormat();
    return *this;
}

QString Request::size() const
{
    return d()->size();
}

Request &Request::setSize(const QString &size)
{
    d()->setSize(size);
    return *this;
}

Request &Request::resetSize()
{
    d()->resetSize();
    return *this;
}

bool Request::isStreaming() const
{
    return d()->isStreaming();
}

Request &Request::setStreaming(bool streaming)
{
    d()->setStreaming(streaming);
    return *this;
}

Request &Request::resetStreaming()
{
    d()->resetStreaming();
    return *this;
}

QString Request::style() const
{
    return d()->style();
}

Request &Request::setStyle(const QString &style)
{
    d()->setStyle(style);
    return *this;
}

Request &Request::resetStyle()
{
    d()->resetStyle();
    return *this;
}

QString Request::user() const
{
    return d()->user();
}

Request &Request::setUser(const QString &user)
{
    d()->setUser(user);
    return *this;
}

Request &Request::resetUser()
{
    d()->resetUser();
    return *this;
}

Request::Request(RequestData* data)
    : ai::Request{data ? data : new RequestData}
{}

bool RequestData::readJson(const QJsonObject &json, QStringList *errors)
{
    bool ok = ai::RequestData::readJson(json);

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

} // namespace ai::images
