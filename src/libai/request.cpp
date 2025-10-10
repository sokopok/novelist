#include "request.h"
#include "client.h"

namespace ai {

bool Request::readJson(const QJsonObject& json, QStringList* errors)
{
    bool ok = true;
    mExtra = json;

    if (mExtra.contains(QStringLiteral("id"))) {
        if (const auto v = mExtra.value(QStringLiteral("id")); v.isString()) {
            setId(v.toString());
            mExtra.remove(QStringLiteral("id"));
        } else {
            if (errors)
                errors->append("id is not a string");
            ok = false;
        }
    }

    if (mExtra.contains(QStringLiteral("url"))) {
        if (const auto v = mExtra.value(QStringLiteral("url")); v.isString()) {
            setUrl(v.toString());
            mExtra.remove(QStringLiteral("url"));
        } else {
            if (errors)
                errors->append("url is not a string");
            ok = false;
        }
    }

    return ok;
}

bool Request::writeJson(QJsonObject& json, bool full) const
{
    if (full) {
        json[QStringLiteral("id")] = mId;
        json[QStringLiteral("url")] = url().toString();
    }
    return true;
}

QVariant Request::attribute(Attribute code) const
{
    switch (code) {
    case IdAttribute:
        return id();
    case ApiKeyAttribute:
        return apiKey();
    default:
        return {};
    }
}

bool Request::setAttribute(Attribute code, const QVariant &value)
{
    switch (code) {
    case IdAttribute:
        return setId(value.toString());
    case ApiKeyAttribute:
        return setApiKey(value.toByteArray());
    default:
        return false;
    }
}

QJsonObject Request::toJson(bool full) const
{
    QJsonObject json;
    return writeJson(json, full) ? json : QJsonObject{};
}

QByteArray Request::prettyJson(bool full) const
{
    return QJsonDocument{toJson(full)}.toJson();
}

Request::Request()
    : QNetworkRequest{}
{
    resetApiKey();
    resetId();
    resetUrl();

    setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    setRawHeader("Accept", "application/json");
    setTransferTimeout(60000);
}

} // namespace ai
