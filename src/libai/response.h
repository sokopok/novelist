#ifndef AI_RESPONSE_H
#define AI_RESPONSE_H

#include <QNetworkReply>
#include <QObject>
#include "request.h"

class QNetworkAccessManager;
class QNetworkRequest;
class QNetworkReply;

namespace ai {

class ResponseData : public QSharedData
{
protected:
    QVariantMap mMetadata;
    QString mModel;
    bool mStreaming = false;
    StreamOptions mStreamOptions;

public:
    [[nodiscard]] bool operator==(const ResponseData& that) const
    {
        return metadata() == that.metadata() && model() == that.model()
               && isStreaming() == that.isStreaming() && streamOptions() == that.streamOptions();
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

    QJsonObject toJson() const
    {
        QJsonObject json;
        return writeJson(json) ? json : QJsonObject{};
    }

    virtual bool readJson(const QJsonObject& json);
    virtual bool writeJson(QJsonObject& json) const;
};

class Response : public QObject
{
    Q_OBJECT

    Request mRequest;
    QNetworkReply* mReply = nullptr;
    Client* mClient = nullptr;
    bool mSetParentToReply = true;
    bool mDeleteReplyWhenFinished = true;

    QSharedDataPointer<ResponseData> d;

public:
    enum Error { NoError, NetworkError, SslError };
    Q_ENUM(Error)

    Response(const Request& request, QNetworkReply* reply, Client* client);

    [[nodiscard]] Error error() const;

    void abort()
    {
        if (mReply)
            mReply->abort();
    }

    [[nodiscard]] bool isRunning() const { return mReply ? mReply->isRunning() : false; }
    [[nodiscard]] bool isFinished() const { return mReply ? mReply->isFinished() : false; }

    [[nodiscard]] Client* client() const { return mClient; }
    [[nodiscard]] QNetworkReply* reply() const { return mReply; }
    [[nodiscard]] Request request() const { return mRequest; }

    [[nodiscard]] QVariantMap metadata() const { return d->metadata(); }
    Response& setMetadata(const QVariantMap& metadata)
    {
        if (d->setMetadata(metadata))
            emit metadataChanged(QPrivateSignal{});
        return *this;
    }
    void resetMetadata() { d->resetMetadata(); }

    bool putMetadata(const QString& key, const QVariant& value)
    {
        return d->putMetadata(key, value);
    }
    QVariant takeMetadata(const QString& key) { return d->takeMetadata(key); }

    [[nodiscard]] QString model() const { return d->model(); }
    Response& setModel(const QString& model)
    {
        if (d->setModel(model))
            emit modelChanged(QPrivateSignal{});
        return *this;
    }
    void resetModel() { d->resetModel(); }

    [[nodiscard]] bool isStreaming() const { return d->isStreaming(); }
    Response& setStreaming(bool streaming)
    {
        if (d->setStreaming(streaming))
            emit streamingChanged(QPrivateSignal{});
        return *this;
    }
    void resetStreaming() { d->resetStreaming(); }

    [[nodiscard]] StreamOptions streamOptions() const { return d->streamOptions(); }
    Response& setStreamOptions(const StreamOptions& streamOptions)
    {
        if (d->setStreamOptions(streamOptions))
            emit streamOptionsChanged(QPrivateSignal{});
        return *this;
    }
    void resetStreamOptions() { d->resetStreamOptions(); }

    virtual QJsonObject toJson() const
    {
        QJsonObject json;
        return writeJson(json) ? json : QJsonObject{};
    }

signals:
    void requestSent(QPrivateSignal);
    void readyRead(QPrivateSignal);
    void finished(QPrivateSignal);
    void errorOccurred(ai::Response::Error error, const QString& message, QPrivateSignal);

    void metadataChanged(QPrivateSignal);
    void modelChanged(QPrivateSignal);
    void streamingChanged(QPrivateSignal);
    void streamOptionsChanged(QPrivateSignal);
    void apiUrlChanged(QPrivateSignal);

protected:
    Response(ResponseData* data,
             const Request& request,
             QNetworkReply* reply,
             Client* client = nullptr);

    void reset(const Request& request, QNetworkReply* reply, Client* client = nullptr);

    virtual bool readJson(const QJsonObject& json) { return d->readJson(json); }
    virtual bool writeJson(QJsonObject& json) const { return d->writeJson(json); }

    void handleRequestSent();
    void handleReadyRead();
    void handleFinished();
    void handleErrorOccurred(QNetworkReply::NetworkError error);
    void handleSslErrors(const QList<QSslError>& errors);
};

} // namespace ai

#endif // AI_RESPONSE_H
