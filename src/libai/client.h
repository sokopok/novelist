#ifndef AI_CLIENT_H
#define AI_CLIENT_H

#include <QObject>
#include "request.h"

class QNetworkAccessManager;
class QNetworkRequest;
class QNetworkReply;

namespace ai {

class TokenProvider;

class Client : public QObject
{
    Q_OBJECT

protected:
    QSharedDataPointer<RequestData> d;

public:
    explicit Client(QObject* parent = nullptr);
    virtual ~Client() = default;

    virtual Q_INVOKABLE Response* post(const Request& request, QIODevice* device = nullptr);

    [[nodiscard]] QByteArray apiKey() const { return d->apiKey(); }
    Client& setApiKey(const QByteArray& apiKey)
    {
        d->setApiKey(apiKey);
        return *this;
    }
    Client& resetApiKey()
    {
        d->resetApiKey();
        return *this;
    }

    [[nodiscard]] QUrl apiUrl() const { return d->apiUrl(); }
    Client& setApiUrl(const QUrl& apiUrl)
    {
        d->setApiUrl(apiUrl);
        return *this;
    }
    Client& resetApiUrl()
    {
        d->resetApiUrl();
        return *this;
    }

    [[nodiscard]] QVariantMap metadata() const { return d->metadata(); }
    Client& setMetadata(const QVariantMap& metadata)
    {
        d->setMetadata(metadata);
        return *this;
    }
    Client& resetMetadata()
    {
        d->resetMetadata();
        return *this;
    }

    bool putMetadata(const QString& key, const QVariant& value)
    {
        return d->putMetadata(key, value);
    }
    QVariant takeMetadata(const QString& key) { return d->takeMetadata(key); }

    [[nodiscard]] QString model() const { return d->model(); }
    Client& setModel(const QString& model)
    {
        d->setModel(model);
        return *this;
    }
    Client& resetModel()
    {
        d->resetModel();
        return *this;
    }

    [[nodiscard]] bool isStreaming() const { return d->isStreaming(); }
    Client& setStreaming(bool streaming)
    {
        d->setStreaming(streaming);
        return *this;
    }
    Client& resetStreaming()
    {
        d->resetStreaming();
        return *this;
    }

    [[nodiscard]] StreamOptions streamOptions() const { return d->streamOptions(); }
    Client& setStreamOptions(const StreamOptions& streamOptions)
    {
        d->setStreamOptions(streamOptions);
        return *this;
    }
    Client& resetStreamOptions()
    {
        d->resetStreamOptions();
        return *this;
    }

    [[nodiscard]] TokenProvider* tokenProvider() const;
    void setTokenProvider(TokenProvider* tokenProvider);
    void resetTokenProvider();

    [[nodiscard]] QNetworkAccessManager* networkAccessManager() const
    {
        return mNetworkAccessManager;
    }
    void setNetworkAccessManager(QNetworkAccessManager* networkAccessManager);
    void resetNetworkAccessManager();

signals:
    void requestDataChanged(QPrivateSignal);

    void tokenProviderChanged(QPrivateSignal);
    void networkAccessManagerChanged(QPrivateSignal);

    void recycled(ai::Request* request, QPrivateSignal);
    void revived(ai::Request* request, QPrivateSignal);

protected:
    void recycle(Request* request)
    {
        if (!request)
            return;
        recycledRequests().append(request);
        emit recycled(request, QPrivateSignal{});
    }
    void revive(Request* request)
    {
        if (!request || !recycledRequests().removeOne(request))
            return;
        emit revived(request, QPrivateSignal{});
    }

    virtual Request* createRequest() { return nullptr; }

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
    RequestData* mRequestData = nullptr;
};

} // namespace ai

#endif // AI_CLIENT_H
