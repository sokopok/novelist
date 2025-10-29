#ifndef LIBAI_REQUEST_H
#define LIBAI_REQUEST_H

#include <QJsonObject>
#include <QNetworkReply>
#include <QObject>
#include <qqmlintegration.h>

class QNetworkAccessManager;
class QNetworkRequest;
class QNetworkReply;

namespace ai {

class Client;
class Response;

class Request : public QNetworkRequest
{
    Q_GADGET
    QML_VALUE_TYPE(request)
    QML_CONSTRUCTIBLE_VALUE
    Q_PROPERTY(QUrl url READ url WRITE setUrl FINAL)
    Q_PROPERTY(QString id READ id WRITE setId FINAL)
    Q_PROPERTY(QByteArray apiKey READ apiKey WRITE setApiKey FINAL)

public:
    enum Attribute { IdAttribute, ApiKeyAttribute, UrlAttribute, NumAttributes };
    Q_ENUM(Attribute)

    enum Error { NoError, NetworkError, SslError };
    Q_ENUM(Error)

    Request(const QUrl& url = {})
        : QNetworkRequest{url}
    {
        resetApiKey();
        resetId();
        resetUrl();

        setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        setRawHeader("Accept", "application/json");
        setTransferTimeout(60000);
    }

    virtual ~Request() {}

    [[nodiscard]] QVariant attribute(Attribute code) const;
    bool setAttribute(Attribute code, const QVariant& value);
    using QNetworkRequest::setAttribute;

    virtual bool resetUrl()
    {
        setUrl({});
        return true;
    }

    [[nodiscard]] QString id() const { return mId; }
    virtual bool setId(const QString& id)
    {
        if (mId == id)
            return false;
        mId = id;
        return true;
    }
    virtual bool resetId() { return setId({}); }

    [[nodiscard]] QByteArray apiKey() const { return mApiKey; }
    virtual bool setApiKey(const QByteArray& apiKey)
    {
        if (mApiKey == apiKey)
            return false;
        mApiKey = apiKey;
        setRawHeader("Authorization", mApiKey.isEmpty() ? QByteArray{} : "Bearer " + mApiKey);
        return true;
    }
    virtual bool resetApiKey() { return setApiKey({}); }

    [[nodiscard]] QJsonObject extra() const { return mExtra; }

    QJsonObject toJson(bool full = false) const;
    QByteArray prettyJson(bool full = false) const;

protected:
    virtual bool readJson(const QJsonObject& json, QStringList* errors = nullptr);
    virtual bool writeJson(QJsonObject& json, bool full = false) const;

    [[nodiscard]] QJsonObject& extra() { return mExtra; }

    friend class Client;

    QString mId;
    QByteArray mApiKey;
    QJsonObject mExtra;
};

} // namespace ai

#endif // LIBAI_REQUEST_H
