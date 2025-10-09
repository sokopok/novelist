#include "request.h"
#include "client.h"

namespace ai {

// bool Request::start()
// {
//     auto* network = networkAccessManager();
//     if (!network) {
//         qCWarning(LOGAI) << "No networkAccessManager";
//         return false;
//     }

//     const auto json = requestData().toJson();

//     const QByteArray data = QJsonDocument{json}.toJson(QJsonDocument::Compact);

//     mReply = network->post(mRequest, data);

//     connect(mReply, &QNetworkReply::requestSent, this, &Request::handleReplyRequestSent);
//     connect(mReply, &QNetworkReply::readyRead, this, &Request::handleReplyReadyRead);
//     connect(mReply, &QNetworkReply::finished, this, &Request::handleReplyFinished);
//     connect(mReply, &QNetworkReply::errorOccurred, this, &Request::handleReplyErrorOccurred);
//     connect(mReply, &QNetworkReply::sslErrors, this, &Request::handleReplySslErrors);

//     return true;
// }

// void Request::abort()
// {
//     if (mReply)
//         mReply->abort();
// }

// bool Request::reset(const QVariantMap& input)
// {
//     abort();
//     return true;
// }

bool RequestData::readJson(const QJsonObject& json, QStringList* errors)
{
    bool ok = true;
    mExtra = json;

    if (json.contains(QStringLiteral("metadata"))) {
        if (const auto v = json.value(QStringLiteral("metadata")); v.isObject()) {
            setMetadata(v.toObject().toVariantMap());
            mExtra.remove(QStringLiteral("metadata"));
        } else {
            if (errors)
                errors->append("metadata is not an object");
            ok = false;
        }
    }

    if (json.contains(QStringLiteral("model"))) {
        if (const auto v = json.value(QStringLiteral("model")); v.isObject()) {
            setModel(v.toString());
            mExtra.remove(QStringLiteral("model"));
        } else {
            if (errors)
                errors->append("model is not a string");
            ok = false;
        }
    }

    if (json.contains(QStringLiteral("stream"))) {
        if (const auto v = json.value(QStringLiteral("stream")); v.isBool()) {
            setStreaming(v.toBool());
            mExtra.remove(QStringLiteral("stream"));
        } else {
            if (errors)
                errors->append("stream is not a boolean");
            ok = false;
        }
    }

    if (json.contains(QStringLiteral("stream_options"))) {
        if (const auto v = json.value(QStringLiteral("stream_options")); v.isObject()) {
            setStreamOptions(StreamOptions::fromJson(v.toObject()));
            mExtra.remove(QStringLiteral("stream_options"));
        } else {
            if (errors)
                errors->append("stream_options is not an object");
            ok = false;
        }
    }

    return ok;
}

bool RequestData::writeJson(QJsonObject& json, bool full) const
{
    if (full || !metadata().isEmpty())
        json[QStringLiteral("metadata")] = QJsonObject::fromVariantMap(metadata());

    if (full || !model().isEmpty())
        json[QStringLiteral("model")] = model();

    if (full || isStreaming()) {
        json[QStringLiteral("stream")] = isStreaming();

        if (full || !streamOptions().isEmpty())
            json[QStringLiteral("stream_options")] = streamOptions().toJson();
    }

    return true;
}

Request::Request()
    : Request(new RequestData)
{}

QVariant Request::attribute(Attribute code) const
{
    return mAttributes.value(code);
}

Request &Request::setAttribute(Attribute code, const QVariant &value)
{
    if (!value.isValid())
        mAttributes.remove(code);
    mAttributes[code] = value;
    return *this;
}

Request &Request::setAttribute(QNetworkRequest::Attribute code, const QVariant &value)
{
    QNetworkRequest::setAttribute(code, value);
    return *this;
}

Request &Request::setDecompressedSafetyCheckThreshold(qint64 threshold)
{
    QNetworkRequest::setDecompressedSafetyCheckThreshold(threshold);
    return *this;
}

Request &Request::setHeader(KnownHeaders header, const QVariant &value)
{
    QNetworkRequest::setHeader(header, value);
    return *this;
}

Request &Request::setHeaders(QHttpHeaders &&newHeaders)
{
    QNetworkRequest::setHeaders(newHeaders);
    return *this;
}

Request &Request::setHeaders(const QHttpHeaders &newHeaders)
{
    QNetworkRequest::setHeaders(newHeaders);
    return *this;
}

Request &Request::setHttp1Configuration(const QHttp1Configuration &configuration)
{
    QNetworkRequest::setHttp1Configuration(configuration);
    return *this;
}

Request &Request::setHttp2Configuration(const QHttp2Configuration &configuration)
{
    QNetworkRequest::setHttp2Configuration(configuration);
    return *this;
}

Request &Request::setMaximumRedirectsAllowed(int maxRedirectsAllowed)
{
    QNetworkRequest::setMaximumRedirectsAllowed(maxRedirectsAllowed);
    return *this;
}

Request &Request::setOriginatingObject(QObject *object)
{
    QNetworkRequest::setOriginatingObject(object);
    return *this;
}

Request &Request::setPeerVerifyName(const QString &peerName)
{
    QNetworkRequest::setPeerVerifyName(peerName);
    return *this;
}

Request &Request::setPriority(Priority priority)
{
    QNetworkRequest::setPriority(priority);
    return *this;
}

Request &Request::setRawHeader(const QByteArray &headerName, const QByteArray &headerValue)
{
    QNetworkRequest::setRawHeader(headerName, headerValue);
    return *this;
}

Request &Request::setSslConfiguration(const QSslConfiguration &config)
{
    QNetworkRequest::setSslConfiguration(config);
    return *this;
}

Request &Request::setTransferTimeout(int timeout)
{
    QNetworkRequest::setTransferTimeout(timeout);
    return *this;
}

Request &Request::setTransferTimeout(std::chrono::milliseconds duration)
{
    QNetworkRequest::setTransferTimeout(duration);
    return *this;
}

Request &Request::setUrl(const QUrl &url)
{
    QNetworkRequest::setUrl(url);
    d->explicits().setBit(Request::UrlAttribute);
    return *this;
}

Request &Request::resetUrl()
{
    setUrl({});
    return *this;
}

QString Request::id() const
{
    return d->id();
}

Request &Request::setId(const QString &id)
{
    d->setId(id);
    return *this;
}

QByteArray Request::apiKey() const
{
    return d->apiKey();
}

Request &Request::setApiKey(const QByteArray &apiKey)
{
    d->setApiKey(apiKey, SetExplicit);
    setRawHeader("Authorization", apiKey.isEmpty() ? QByteArray{} : "Bearer " + apiKey);
    return *this;
}

Request &Request::resetApiKey()
{
    d->resetApiKey(ClearExplicit);
    setRawHeader("Authorization", {});
    return *this;
}

QVariantMap Request::metadata() const
{
    return d->metadata();
}

Request &Request::setMetadata(const QVariantMap &metadata)
{
    d->setMetadata(metadata, SetExplicit);
    return *this;
}

Request &Request::resetMetadata()
{
    d->resetMetadata(ClearExplicit);
    return *this;
}

bool Request::putMetadata(const QString &key, const QVariant &value)
{
    return d->putMetadata(key, value, SetExplicit);
}

bool Request::putMetadata(const QVariantMap &map)
{
    for (auto it = map.begin(); it != map.end(); ++it)
        putMetadata(it.key(), it.value());
    return true;
}

QVariant Request::takeMetadata(const QString &key)
{
    return d->takeMetadata(key);
}

QString Request::model() const
{
    return d->model();
}

Request &Request::setModel(const QString &model)
{
    d->setModel(model, SetExplicit);
    return *this;
}

Request &Request::setModel(Model model)
{
    d->setModel(model, SetExplicit);
    return *this;
}

Request &Request::resetModel()
{
    d->resetModel(ClearExplicit);
    return *this;
}

bool Request::isStreaming() const
{
    return d->isStreaming();
}

Request &Request::setStreaming(bool streaming)
{
    d->setStreaming(streaming, SetExplicit);

    setRawHeader("Accept", isStreaming() ? "text/event-stream" : "application/json");

#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
    setTransferTimeout(isStreaming() ? 0 : 60000);
#endif

    return *this;
}

Request &Request::resetStreaming()
{
    d->resetStreaming(ClearExplicit);

    setRawHeader("Accept", isStreaming() ? "text/event-stream" : "application/json");

#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
    setTransferTimeout(isStreaming() ? 0 : 60000);
#endif

    return *this;
}

StreamOptions Request::streamOptions() const
{
    return d->streamOptions();
}

Request &Request::setStreamOptions(const StreamOptions &streamOptions)
{
    d->setStreamOptions(streamOptions, SetExplicit);
    return *this;
}

Request &Request::resetStreamOptions()
{
    d->resetStreamOptions(ClearExplicit);
    return *this;
}

QJsonObject Request::toJson(bool full) const
{
    QJsonObject json;
    return writeJson(json, full) ? json : QJsonObject{};
}

QString Request::formattedJson(bool full) const
{
    return QJsonDocument{toJson(full)}.toJson();
}

Request::Request(RequestData* data)
    : d{data ? data : new RequestData}
{
    setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    setRawHeader("Authorization", "Bearer " + apiKey());

    setRawHeader("Accept", isStreaming() ? "text/event-stream" : "application/json");

#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
    setTransferTimeout(isStreaming() ? 0 : 60000);
#endif
}

bool Request::readJson(const QJsonObject &json, QStringList *errors)
{
    return d->readJson(json, errors);
}

bool Request::writeJson(QJsonObject &json, bool full) const
{
    if (full) {
        json[QStringLiteral("url")] = url().toString();
    }

    return d->writeJson(json, full);
}

bool Request::isExplicit(int attribute) const
{
    return d->isExplicit(attribute);
}

} // namespace ai
