#ifndef AI_CLIENT_H
#define AI_CLIENT_H

#include <QObject>
#include "config/error.h"
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
    QByteArray mApiKey;
    QUrl mApiUrl;
    Error mError;

public:
    [[nodiscard]] static Client* create(QObject* parent = nullptr);

    virtual ~Client();

    [[nodiscard]] Error error() const { return mError; }

    // virtual Q_INVOKABLE Response* post(const Request& request, QIODevice* device = nullptr) = 0;

    [[nodiscard]] QByteArray apiKey() const { return mApiKey; }
    virtual bool setApiKey(const QByteArray& apiKey)
    {
        if (mApiKey == apiKey)
            return false;
        mApiKey = apiKey;
        emit apiKeyChanged(QPrivateSignal{});
        return true;
    }
    virtual bool resetApiKey() { return setApiKey({}); }

    [[nodiscard]] QUrl apiUrl() const { return mApiUrl; }
    virtual bool setApiUrl(const QUrl& apiUrl)
    {
        if (mApiUrl == apiUrl)
            return false;
        mApiUrl = apiUrl;
        emit apiUrlChanged(QPrivateSignal{});
        return true;
    }
    virtual bool resetApiUrl() { return setApiUrl({}); }

    [[nodiscard]] TokenProvider* tokenProvider() const { return mTokenProvider; }
    virtual bool setTokenProvider(TokenProvider* tokenProvider)
    {
        if (mTokenProvider == tokenProvider)
            return false;
        mTokenProvider = tokenProvider;
        emit tokenProviderChanged(QPrivateSignal{});
        return true;
    }
    virtual bool resetTokenProvider()
    {
        return setTokenProvider(new EnvironmentalTokenProvider{this});
    }

    [[nodiscard]] QNetworkAccessManager* networkAccessManager() const
    {
        return mNetworkAccessManager;
    }
    virtual bool setNetworkAccessManager(QNetworkAccessManager* networkAccessManager)
    {
        if (mNetworkAccessManager == networkAccessManager)
            return false;
        mNetworkAccessManager = networkAccessManager;
        emit networkAccessManagerChanged(QPrivateSignal{});
        return true;
    }
    virtual bool resetNetworkAccessManager()
    {
        return setNetworkAccessManager(new QNetworkAccessManager{this});
    }

    // QJsonObject toJson(bool full = false) const
    // {
    //     QJsonObject json;
    //     return writeJson(json, full) ? json : QJsonObject{};
    // }
    // QString formattedJson(bool full = false) const { return QJsonDocument{toJson(full)}.toJson(); }

signals:
    void apiKeyChanged(QPrivateSignal);
    void apiUrlChanged(QPrivateSignal);

    void errorOccurred(const ai::Error& error, QPrivateSignal);

    void tokenProviderChanged(QPrivateSignal);
    void networkAccessManagerChanged(QPrivateSignal);

    void recycled(ai::Request* request, QPrivateSignal);
    void revived(ai::Request* request, QPrivateSignal);

protected:
    explicit Client(QObject* parent = nullptr);

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

    // [[nodiscard]] virtual bool prepareRequest(Request* request);
    // [[nodiscard]] virtual bool validateRequest(const Request& request) const;

    // virtual bool readJson(const QJsonObject& json);
    // virtual bool writeJson(QJsonObject& json, bool full = false) const;

    void setError(const Error& error);

    virtual void initialize();

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
