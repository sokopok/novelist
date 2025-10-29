#ifndef LIBAI_CLIENT_H
#define LIBAI_CLIENT_H

#include "response.h"
#include <QImage>
#include <QObject>
#include <qqmlintegration.h>

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
    QML_NAMED_ELEMENT(Client)
    QML_UNCREATABLE("Client is a base class")

public:
    virtual ~Client() override;

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

    void responseErrorOccurred(ai::Response* response, const ai::Error& error, QPrivateSignal);
    void responseRequestSent(ai::Response* response, QPrivateSignal);
    void responseReadyRead(ai::Response* response, QPrivateSignal);
    void responseFinished(ai::Response* response, QPrivateSignal);
    void responseTextGenerated(ai::Response* response, const QString& text, QPrivateSignal);
    void responseImageGenerated(ai::Response* response, const QImage& image, QPrivateSignal);

    void tokenProviderChanged(QPrivateSignal);
    void networkAccessManagerChanged(QPrivateSignal);

protected:
    explicit Client(QObject* parent = nullptr);

    void clearError() { setError({}); }
    void setError(const Error& error);

    void initialize();

    void emitResponseErrorOccurred(Response* response, const ai::Error& error)
    {
        emit responseErrorOccurred(response, error, QPrivateSignal{});
    }
    void emitResponseRequestSent(Response* response)
    {
        emit responseRequestSent(response, QPrivateSignal{});
    }
    void emitResponseReadyRead(Response* response)
    {
        emit responseReadyRead(response, QPrivateSignal{});
    }
    void emitResponseFinished(Response* response)
    {
        emit responseFinished(response, QPrivateSignal{});
    }
    void emitResponseTextGenerated(Response* response, const QString& text)
    {
        emit responseTextGenerated(response, text, QPrivateSignal{});
    }
    void emitResponseImageGenerated(Response* response, const QImage& image)
    {
        emit responseImageGenerated(response, image, QPrivateSignal{});
    }

private:
    QByteArray mApiKey;
    QUrl mApiUrl;
    Error mError;
    QNetworkAccessManager* mNetworkAccessManager = nullptr;
    TokenProvider* mTokenProvider = nullptr;
};

} // namespace ai

#endif // LIBAI_CLIENT_H
