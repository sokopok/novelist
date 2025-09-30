#ifndef AI_REQUEST_H
#define AI_REQUEST_H

#include <QNetworkReply>
#include <QObject>
#include "config.h"

class QNetworkAccessManager;
class QNetworkRequest;
class QNetworkReply;

namespace ai {

class Client;
class Response;

class RequestData : public QSharedData
{
    StreamOptions mStreamOptions;
    QVariantMap mMetadata;
    QString mModel;
    QString mId;
    QByteArray mApiKey;
    bool mStreaming = false;

public:
    [[nodiscard]] bool operator==(const RequestData& that) const
    {
        return apiKey() == that.apiKey()
               && metadata() == that.metadata()
               && model() == that.model()
               && isStreaming() == that.isStreaming()
               && streamOptions() == that.streamOptions();
    }

    [[nodiscard]] QString id() const { return mId; }
    bool setId(const QString& id)
    {
        if (mId == id)
            return false;
        mId = id;
        return true;
    }

    /** metadata
        map
        Optional
        Set of 16 key-value pairs that can be attached to an object. This can be useful for storing additional information about the object in a structured format, and querying for objects via API or the dashboard.
        Keys are strings with a maximum length of 64 characters. Values are strings with a maximum length of 512 characters.
    */
    [[nodiscard]] QVariantMap metadata() const { return mMetadata; }
    bool setMetadata(const QVariantMap& metadata)
    {
        if (mMetadata == metadata)
            return false;
        mMetadata = metadata;
        return true;
    }
    void resetMetadata() { setMetadata({}); }

    [[nodiscard]] QVariant metadata(const QString& key) const { return mMetadata.value(key); }
    bool putMetadata(const QString& key, const QVariant& value)
    {
        if (key.isEmpty())
            return false;
        mMetadata[key] = value;
        return true;
    }
    QVariant takeMetadata(const QString& key) { return mMetadata.take(key); }

    /** model
        string
        Optional
        Model ID used to generate the response, like gpt-4o or o3. OpenAI offers a wide range of models with different capabilities, performance characteristics, and price points. Refer to the model guide to browse and compare available models.
    */
    [[nodiscard]] QString model() const { return mModel; }
    bool setModel(const QString& model)
    {
        if (mModel == model)
            return false;
        mModel = model;
        return true;
    }
    void resetModel() { setModel({}); }

    /** stream
        boolean
        Optional
        Defaults to false
        If set to true, the model response data will be streamed to the client as it is generated using server-sent events. See the Streaming section below for more information.
    */
    [[nodiscard]] bool isStreaming() const { return mStreaming; }
    bool setStreaming(bool streaming)
    {
        if (mStreaming == streaming)
            return false;
        mStreaming = streaming;
        return true;
    }
    void resetStreaming() { setStreaming(false); }

    /** stream_options
        object
        Optional
        Defaults to null
        Options for streaming responses. Only set this when you set stream: true.
    */
    [[nodiscard]] StreamOptions streamOptions() const { return mStreamOptions; }
    bool setStreamOptions(const StreamOptions& streamOptions)
    {
        if (mStreamOptions == streamOptions)
            return false;
        mStreamOptions = streamOptions;
        return true;
    }
    void resetStreamOptions() { setStreamOptions({}); }

    [[nodiscard]] QByteArray apiKey() const { return mApiKey; }
    bool setApiKey(const QByteArray& apiKey)
    {
        if (mApiKey == apiKey)
            return false;
        mApiKey = apiKey;
        return true;
    }
    void resetApiKey() { setApiKey({}); }

    QJsonObject toJson(bool full = false) const
    {
        QJsonObject json;
        return writeJson(json, full) ? json : QJsonObject{};
    }

    virtual bool readJson(const QJsonObject& json);
    virtual bool writeJson(QJsonObject& json, bool full = false) const;
};

class Request : public QNetworkRequest
{
    Q_GADGET

protected:
    QSharedDataPointer<RequestData> d;

public:
    enum Error { NoError, NetworkError, SslError };
    Q_ENUM(Error)

    Request();

    Request& setAttribute(QNetworkRequest::Attribute code, const QVariant& value)
    {
        QNetworkRequest::setAttribute(code, value);
        return *this;
    }
    Request& setDecompressedSafetyCheckThreshold(qint64 threshold)
    {
        QNetworkRequest::setDecompressedSafetyCheckThreshold(threshold);
        return *this;
    }
    Request& setHeader(QNetworkRequest::KnownHeaders header, const QVariant& value)
    {
        QNetworkRequest::setHeader(header, value);
        return *this;
    }
    Request& setHeaders(QHttpHeaders&& newHeaders)
    {
        QNetworkRequest::setHeaders(newHeaders);
        return *this;
    }
    Request& setHeaders(const QHttpHeaders& newHeaders)
    {
        QNetworkRequest::setHeaders(newHeaders);
        return *this;
    }
    Request& setHttp1Configuration(const QHttp1Configuration& configuration)
    {
        QNetworkRequest::setHttp1Configuration(configuration);
        return *this;
    }
    Request& setHttp2Configuration(const QHttp2Configuration& configuration)
    {
        QNetworkRequest::setHttp2Configuration(configuration);
        return *this;
    }
    Request& setMaximumRedirectsAllowed(int maxRedirectsAllowed)
    {
        QNetworkRequest::setMaximumRedirectsAllowed(maxRedirectsAllowed);
        return *this;
    }
    Request& setOriginatingObject(QObject* object)
    {
        QNetworkRequest::setOriginatingObject(object);
        return *this;
    }
    Request& setPeerVerifyName(const QString& peerName)
    {
        QNetworkRequest::setPeerVerifyName(peerName);
        return *this;
    }
    Request& setPriority(QNetworkRequest::Priority priority)
    {
        QNetworkRequest::setPriority(priority);
        return *this;
    }
    Request& setRawHeader(const QByteArray& headerName, const QByteArray& headerValue)
    {
        QNetworkRequest::setRawHeader(headerName, headerValue);
        return *this;
    }
    Request& setSslConfiguration(const QSslConfiguration& config)
    {
        QNetworkRequest::setSslConfiguration(config);
        return *this;
    }
    Request& setTransferTimeout(int timeout)
    {
        QNetworkRequest::setTransferTimeout(timeout);
        return *this;
    }
    Request& setTransferTimeout(std::chrono::milliseconds duration = DefaultTransferTimeout)
    {
        QNetworkRequest::setTransferTimeout(duration);
        return *this;
    }
    Request& setUrl(const QUrl& url)
    {
        QNetworkRequest::setUrl(url);
        return *this;
    }
    Request& resetUrl()
    {
        setUrl({});
        return *this;
    }

    [[nodiscard]] QString id() const { return d->id(); }
    Request& setId(const QString& id)
    {
        d->setId(id);
        return *this;
    }

    [[nodiscard]] QByteArray apiKey() const { return d->apiKey(); }
    Request& setApiKey(const QByteArray& apiKey)
    {
        d->setApiKey(apiKey);
        setRawHeader("Authorization", apiKey.isEmpty() ? "" : "Bearer " + apiKey);
        return *this;
    }
    Request& resetApiKey()
    {
        setApiKey({});
        return *this;
    }

    [[nodiscard]] QVariantMap metadata() const { return d->metadata(); }
    Request& setMetadata(const QVariantMap& metadata)
    {
        d->setMetadata(metadata);
        return *this;
    }
    Request& resetMetadata()
    {
        d->resetMetadata();
        return *this;
    }

    bool putMetadata(const QString& key, const QVariant& value)
    {
        return d->putMetadata(key, value);
    }
    bool putMetadata(const QVariantMap& map)
    {
        for (auto it = map.begin(); it != map.end(); ++it)
            putMetadata(it.key(), it.value());
        return true;
    }
    QVariant takeMetadata(const QString& key) { return d->takeMetadata(key); }

    [[nodiscard]] QString model() const { return d->model(); }
    Request& setModel(const QString& model)
    {
        d->setModel(model);
        return *this;
    }
    Request& resetModel()
    {
        d->resetModel();
        return *this;
    }

    [[nodiscard]] bool isStreaming() const { return d->isStreaming(); }
    Request& setStreaming(bool streaming)
    {
        d->setStreaming(streaming);

        setRawHeader("Accept", isStreaming() ? "text/event-stream" : "application/json");

#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
        setTransferTimeout(isStreaming() ? 0 : 60000);
#endif

        return *this;
    }
    Request& resetStreaming()
    {
        setStreaming(false);
        return *this;
    }

    [[nodiscard]] StreamOptions streamOptions() const { return d->streamOptions(); }
    Request& setStreamOptions(const StreamOptions& streamOptions)
    {
        d->setStreamOptions(streamOptions);
        return *this;
    }
    Request& resetStreamOptions()
    {
        d->resetStreamOptions();
        return *this;
    }

    QJsonObject toJson(bool full = false) const
    {
        QJsonObject json;
        return writeJson(json, full) ? json : QJsonObject{};
    }
    QString formattedJson(bool full = false) const { return QJsonDocument{toJson(full)}.toJson(); }

protected:
    Request(RequestData* data);

    virtual bool readJson(const QJsonObject& json) { return d->readJson(json); }
    virtual bool writeJson(QJsonObject& json, bool full = false) const
    {
        if (full) {
            json[QStringLiteral("url")] = url().toString();
        }

        return d->writeJson(json, full);
    }
};

} // namespace ai

#endif // AI_REQUEST_H
