#ifndef AI_AIREQUEST_H
#define AI_AIREQUEST_H

#include <QObject>
#include "request.h"

namespace ai {

class AiRequest : public QObject, public Request
{
    Q_OBJECT

public:
    explicit AiRequest(AiClient* client, QObject* parent = nullptr);

    virtual bool start();
    virtual void abort();

    virtual bool reset(const QVariantMap& input)
    {
        if (isStarted())
            return warnCantWhileStarted("reset"), false;

        if (!clearError())
            return warnCantClearError("reset"), false;

        return true;

        Q_UNUSED(input)
    }

    //

    [[nodiscard]] bool isStarted() const { return flags(StartedFlag); }
    [[nodiscard]] bool isFinished() const { return flags(FinishedFlag); }

    //

    [[nodiscard]] QByteArray id() const { return mId; }

    //

    //

    [[nodiscard]] AiClient* client() const { return mClient; }
    virtual void setClient(AiClient* client);

    [[nodiscard]] AiResponse* response() const { return mResponse; }

    //

    [[nodiscard]] QByteArray apiKey() const;
    void setApiKey(const QByteArray& apiKey)
    {
        if (!isReady())
            return warnSetPropertyWhenNotReady(QStringLiteral("apiKey"));

        if (mApiKey == apiKey)
            return;

        mApiKey = apiKey;
        emit apiKeyChanged();
    }
    void resetApiKey() { setApiKey({}); }

    [[nodiscard]] QUrl apiUrl() const;
    void setApiUrl(const QUrl& apiUrl)
    {
        if (!isReady())
            return warnSetPropertyWhenNotReady(QStringLiteral("apiUrl"));

        if (mApiUrl == apiUrl)
            return;

        mApiUrl = apiUrl;
        emit apiUrlChanged();
    }
    void resetApiUrl() { setApiUrl({}); }

    /** metadata
        map
        Optional
        Set of 16 key-value pairs that can be attached to an object. This can be useful for storing additional information about the object in a structured format, and querying for objects via API or the dashboard.
        Keys are strings with a maximum length of 64 characters. Values are strings with a maximum length of 512 characters.
    */
    [[nodiscard]] QVariantMap metadata() const { return mMetadata; }
    [[nodiscard]] QVariant metadata(const QString& key) const { return metadata().value(key); }
    void setMetadata(const QVariantMap& metadata)
    {
        if (mMetadata == metadata)
            return;

        mMetadata = metadata;
        emit metadataChanged();
    }
    void resetMetadata() { setMetadata({}); }
    void addMetadata(const QString& key, const QVariant& value)
    {
        if (key.isEmpty())
            return;

        mMetadata[key] = value;
    }
    QVariant takeMetadata(const QString& key)
    {
        if (key.isEmpty())
            return {};

        return mMetadata.take(key);
    }

    /** model
        string
        Optional
        Model ID used to generate the response, like gpt-4o or o3. OpenAI offers a wide range of models with different capabilities, performance characteristics, and price points. Refer to the model guide to browse and compare available models.
    */
    [[nodiscard]] QByteArray model() const;
    void setModel(const QByteArray& model)
    {
        if (mModel == model)
            return;

        mModel = model;
        emit modelChanged();
    }
    void resetModel() { setModel({}); }

    /** stream
        boolean
        Optional
        Defaults to false
        If set to true, the model response data will be streamed to the client as it is generated using server-sent events. See the Streaming section below for more information.
    */
    [[nodiscard]] bool isStreaming() const { return flags(StreamingFlag); }
    void setStreaming(bool streaming)
    {
        if (isStreaming() == streaming)
            return;

        streaming ? addFlags(StreamingFlag) : removeFlags(StreamingFlag);

        emit streamingChanged();
    }
    void resetStreaming();

    /** stream_options
        object
        Optional
        Defaults to null
        Options for streaming responses. Only set this when you set stream: true.
    */
    [[nodiscard]] AiStreamOptions streamOptions() const { return mStreamOptions; }
    void setStreamOptions(const AiStreamOptions& streamOptions)
    {
        if (mStreamOptions == streamOptions)
            return;
        mStreamOptions = streamOptions;
        emit streamOptionsChanged();
    }
    void resetStreamOptions() { setStreamOptions({}); }

    //

    [[nodiscard]] QNetworkAccessManager* networkAccessManager() const;
    virtual void setNetworkAccessManager(QNetworkAccessManager* networkAccessManager)
    {
        if (!isReady())
            return warnSetPropertyWhenNotReady(QStringLiteral("networkAccessManager"));

        if (mNetworkAccessManager == networkAccessManager)
            return;

        if (mNetworkAccessManager)
            mNetworkAccessManager->disconnect(this);

        mNetworkAccessManager = networkAccessManager;

        if (mNetworkAccessManager) {
        }

        emit networkAccessManagerChanged();
    }
    void resetNetworkAccessManager() { setNetworkAccessManager(nullptr); }

    [[nodiscard]] QNetworkRequest request() const { return mRequest; }

    [[nodiscard]] QNetworkReply* reply() const { return mReply; }

    //

    //

    [[nodiscard]] QJsonObject json() const { return mJson; }
    void setJson(const QJsonObject& json)
    {
        if (mJson == json)
            return;
        mJson = json;
        emit jsonChanged();
    }

    //

    virtual AiResponse* createResponse() = 0;

signals:
    void started();
    void finished();

    void metadataChanged();
    void modelChanged();
    void streamingChanged();
    void streamOptionsChanged();

    void responseChanged();
    void apiKeyChanged();
    void apiUrlChanged();
    void networkAccessManagerChanged();
    void replyChanged();
    void requestChanged();
    void jsonChanged();
    void idChanged();
    void deleteWhenFinishedChanged();
    void reuseWhenFinishedChanged();
    void clientChanged();

protected:
    void setId(const QByteArray& id)
    {
        // if (!isReady())
        //     return warnSetPropertyWhenNotReady(QStringLiteral("requestId"));

        if (mId == id)
            return;

        mId = id;

        emit idChanged();
    }

    virtual void setResponse(AiResponse* response);
    virtual void setRequest(const QNetworkRequest& request);
    virtual void setReply(QNetworkReply* reply);

    virtual void handleResponseStarted();
    virtual void handleResponseFinished();
    virtual void handleResponseError(const QString& message);

    enum Flag {
        PreparedFlag = ErrorFlag << 1,
        StartedFlag = ErrorFlag << 2,
        FinishedFlag = ErrorFlag << 3,
        DeleteWhenFinishedFlag = 0x80000000,
        ExplicitDeleteWhenFinishedFlag = 0x40000000,
        ReuseWhenFinishedFlag = 0x20000000,
        ExplicitReuseWhenFinishedFlag = 0x10000000,
        StreamingFlag = 0x08000000,
        ExplicitStreamingFlag = 0x04000000
    };

private:
    friend class AiResponse;

    QNetworkRequest mRequest;
    QByteArray mApiKey;
    QUrl mApiUrl;
    QByteArray mModel;
    QByteArray mId;
    QJsonObject mJson;
    AiClient* mClient = nullptr;
    AiResponse* mResponse = nullptr;
    QNetworkReply* mReply = nullptr;
    QNetworkAccessManager* mNetworkAccessManager = nullptr;
    int mFlags = NoFlag;
    QVariantMap mMetadata;
    AiStreamOptions mStreamOptions;

    friend class AiResponse;

    Q_PROPERTY(AiClient* client READ client NOTIFY clientChanged FINAL)
    Q_PROPERTY(AiResponse* response READ response NOTIFY responseChanged FINAL)
    Q_PROPERTY(QNetworkAccessManager* networkAccessManager READ networkAccessManager NOTIFY
                   networkAccessManagerChanged FINAL)
    Q_PROPERTY(QNetworkReply* reply READ reply NOTIFY replyChanged FINAL)
    Q_PROPERTY(QNetworkRequest request READ request WRITE setRequest NOTIFY requestChanged FINAL)

    Q_PROPERTY(QByteArray requestId READ requestId NOTIFY requestIdChanged FINAL)
    Q_PROPERTY(QJsonObject json READ json NOTIFY jsonChanged FINAL)

    Q_PROPERTY(QByteArray apiKey READ apiKey WRITE setApiKey NOTIFY apiKeyChanged FINAL)
    Q_PROPERTY(QUrl apiUrl READ apiUrl WRITE setApiUrl NOTIFY apiUrlChanged FINAL)
    Q_PROPERTY(QByteArray model READ model WRITE setModel NOTIFY modelChanged FINAL)
    Q_PROPERTY(bool streaming READ isStreaming WRITE setStreaming RESET resetStreaming NOTIFY
                   streamingChanged FINAL)

    Q_PROPERTY(bool deleteWhenFinished READ deleteWhenFinished WRITE setDeleteWhenFinished RESET
                   resetDeleteWhenFinished NOTIFY deleteWhenFinishedChanged FINAL)
    Q_PROPERTY(bool reuseWhenFinished READ reuseWhenFinished WRITE setReuseWhenFinished RESET
                   resetReuseWhenFinished NOTIFY reuseWhenFinishedChanged FINAL)
};

} // namespace ai

#endif // AI_AIREQUEST_H
