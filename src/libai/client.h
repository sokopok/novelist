#ifndef AI_CLIENT_H
#define AI_CLIENT_H

#include <QObject>
#include "request.h"

class QNetworkAccessManager;
class QNetworkRequest;
class QNetworkReply;

namespace ai {

class TokenProvider
{
public:
    virtual ~TokenProvider() = default;
    virtual QByteArray apiKey() const = 0;
    QByteArray bearerToken() const
    {
        const QByteArray k = apiKey();
        return k.isEmpty() ? QByteArray() : QByteArray("Bearer ") + k;
    }
};

class EnvironmentalTokenProvider : public QObject, public TokenProvider
{
public:
    EnvironmentalTokenProvider(QObject* parent = nullptr)
        : QObject{parent}
    {}

    QByteArray apiKey() const override
    {
        const auto key = qgetenv("OPENAI_API_KEY");
        return key;
    }
};

class Client : public QObject
{
    Q_OBJECT

protected:
    QSharedDataPointer<RequestData> d;
    QUrl mApiUrl;
    Error mError;

public:
    explicit Client(QObject* parent = nullptr);

    [[nodiscard]] Error error() const { return mError; }

    // virtual Q_INVOKABLE Response* post(const Request& request, QIODevice* device = nullptr) = 0;

    [[nodiscard]] QByteArray apiKey() const { return d->apiKey(); }
    virtual Client& setApiKey(const QByteArray& apiKey)
    {
        if (d->setApiKey(apiKey))
            emit apiKeyChanged(QPrivateSignal{});
        return *this;
    }
    virtual Client& resetApiKey() { return setApiKey({}); }

    [[nodiscard]] QUrl apiUrl() const { return mApiUrl; }
    virtual Client& setApiUrl(const QUrl& apiUrl)
    {
        if (mApiUrl == apiUrl)
            return *this;
        mApiUrl = apiUrl;
        emit apiUrlChanged(QPrivateSignal{});
        return *this;
    }
    virtual Client& resetApiUrl() { return setApiUrl({}); }

    [[nodiscard]] QVariantMap metadata() const { return d->metadata(); }
    virtual Client& setMetadata(const QVariantMap& metadata)
    {
        if (d->setMetadata(metadata))
            emit metadataChanged(QPrivateSignal{});
        return *this;
    }
    virtual Client& resetMetadata() { return setMetadata({}); }

    bool putMetadata(const QString& key, const QVariant& value)
    {
        if (d->putMetadata(key, value)) {
            emit metadataChanged(QPrivateSignal{});
            return true;
        }
        return false;
    }
    QVariant takeMetadata(const QString& key)
    {
        if (d->metadata().contains(key)) {
            const auto v = d->takeMetadata(key);
            emit metadataChanged(QPrivateSignal{});
            return v;
        }
        return {};
    }

    [[nodiscard]] QString model() const { return d->model(); }
    virtual Client& setModel(const QString& model)
    {
        if (d->setModel(model))
            emit modelChanged(QPrivateSignal{});
        return *this;
    }
    virtual Client& resetModel() { return setModel("gpt-4.1-mini"); }

    [[nodiscard]] bool isStreaming() const { return d->isStreaming(); }
    virtual Client& setStreaming(bool streaming)
    {
        if (d->setStreaming(streaming))
            emit streamingChanged(QPrivateSignal{});
        return *this;
    }
    virtual Client& resetStreaming() { return setStreaming(false); }

    [[nodiscard]] StreamOptions streamOptions() const { return d->streamOptions(); }
    virtual Client& setStreamOptions(const StreamOptions& streamOptions)
    {
        if (d->setStreamOptions(streamOptions))
            emit streamOptionsChanged(QPrivateSignal{});
        return *this;
    }
    virtual Client& resetStreamOptions()
    {
        d->resetStreamOptions();
        return *this;
    }

    [[nodiscard]] TokenProvider* tokenProvider() const { return mTokenProvider; }
    virtual Client& setTokenProvider(TokenProvider* tokenProvider)
    {
        if (mTokenProvider == tokenProvider)
            return *this;
        mTokenProvider = tokenProvider;
        emit tokenProviderChanged(QPrivateSignal{});
        return *this;
    }
    virtual Client& resetTokenProvider()
    {
        setTokenProvider(new EnvironmentalTokenProvider{this});
        return *this;
    }

    [[nodiscard]] QNetworkAccessManager* networkAccessManager() const
    {
        return mNetworkAccessManager;
    }
    virtual Client& setNetworkAccessManager(QNetworkAccessManager* networkAccessManager)
    {
        if (mNetworkAccessManager == networkAccessManager)
            return *this;
        mNetworkAccessManager = networkAccessManager;
        emit networkAccessManagerChanged(QPrivateSignal{});
        return *this;
    }
    virtual Client& resetNetworkAccessManager()
    {
        return setNetworkAccessManager(new QNetworkAccessManager{this});
    }

    QJsonObject toJson(bool full = false) const
    {
        QJsonObject json;
        return writeJson(json, full) ? json : QJsonObject{};
    }
    QString formattedJson(bool full = false) const { return QJsonDocument{toJson(full)}.toJson(); }

signals:
    void apiKeyChanged(QPrivateSignal);
    void apiUrlChanged(QPrivateSignal);
    void metadataChanged(QPrivateSignal);
    void modelChanged(QPrivateSignal);
    void streamingChanged(QPrivateSignal);
    void streamOptionsChanged(QPrivateSignal);

    void errorOccurred(const ai::Error& error, QPrivateSignal);

    void tokenProviderChanged(QPrivateSignal);
    void networkAccessManagerChanged(QPrivateSignal);

    void recycled(ai::Request* request, QPrivateSignal);
    void revived(ai::Request* request, QPrivateSignal);

protected:
    Client(RequestData* requestData, QObject* parent = nullptr);

    virtual void recycle(Request* request)
    {
        if (!request)
            return;
        recycledRequests().append(request);
        emit recycled(request, QPrivateSignal{});
    }
    virtual void revive(Request* request)
    {
        if (!request || !recycledRequests().removeOne(request))
            return;
        emit revived(request, QPrivateSignal{});
    }

    [[nodiscard]] virtual bool prepareRequest(Request& prep, const Request& request) const;
    [[nodiscard]] virtual bool validateRequest(const Request& request) const;

    virtual bool readJson(const QJsonObject& json) { return d->readJson(json); }
    virtual bool writeJson(QJsonObject& json, bool full = false) const
    {
        if (full) {
            json[QStringLiteral("apiUrl")] = mApiUrl.toString();
        }

        return d->writeJson(json, full);
    }

    void setError(const Error& error);

private:
    QMap<QString, Request*> pendingRequests() const;
    QMap<QString, Request*>& pendingRequests();

    Request* pendingRequest(const QString& id) const { return pendingRequests().value(id); }
    void addPendingRequest(const QString& id, Request* request)
    {
        if (id.isEmpty() || !request)
            return;
        pendingRequests()[id] = request;
    }
    Request* takePendingRequest(const QString& id) { return pendingRequests().take(id); }

    QList<Request*> recycledRequests() const;
    QList<Request*>& recycledRequests();

    Request* recycledRequest() const
    {
        if (recycledRequests().isEmpty())
            return nullptr;
        return recycledRequests().at(recycledRequests().size() - 1);
    }
    void addRecycledRequest(Request* request);
    Request* takeRecycledRequest()
    {
        if (recycledRequests().isEmpty())
            return nullptr;
        return recycledRequests().takeLast();
    }

    QMap<QString, Request*> mPendingRequests;
    QList<Request*> mRecycledRequests;
    QNetworkAccessManager* mNetworkAccessManager = nullptr;
    TokenProvider* mTokenProvider = nullptr;
};

} // namespace ai

#endif // AI_CLIENT_H
