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

class Request : public QNetworkRequest
{
    Q_GADGET

public:
    enum Attribute { IdAttribute, ApiKeyAttribute, UrlAttribute, NumAttributes };
    Q_ENUM(Attribute)

    enum Error { NoError, NetworkError, SslError };
    Q_ENUM(Error)

    Request();

    virtual ~Request() {}

    [[nodiscard]] QVariant attribute(Attribute code) const;
    bool setAttribute(Attribute code, const QVariant& value);
    using QNetworkRequest::setAttribute;

    bool resetUrl()
    {
        QUrl u{"https://api.openai.com/v1/images/generations"};
        if (url() == u)
            return false;
        setUrl(u);
        return true;
    }

    [[nodiscard]] QString id() const { return mId; }
    bool setId(const QString& id)
    {
        if (mId == id)
            return false;
        mId = id;
        return true;
    }
    bool resetId() { return setId({}); }

    [[nodiscard]] QByteArray apiKey() const { return mApiKey; }
    bool setApiKey(const QByteArray& apiKey)
    {
        if (mApiKey == apiKey)
            return false;
        mApiKey = apiKey;
        setRawHeader("Authorization", mApiKey.isEmpty() ? QByteArray{} : "Bearer " + mApiKey);
        return true;
    }
    bool resetApiKey() { return setApiKey({}); }

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

#endif // AI_REQUEST_H
