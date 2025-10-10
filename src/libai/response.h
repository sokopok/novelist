#ifndef AI_RESPONSE_H
#define AI_RESPONSE_H

#include <QNetworkReply>
#include <QObject>
#include "config.h"
#include "request.h"

class QNetworkAccessManager;
class QNetworkRequest;
class QNetworkReply;

namespace ai {

class ResponseData
{
protected:
    QJsonObject mExtra;
    QString mId;
    QVariantMap mMetadata;
    QString mModel;
    bool mStreaming = false;
    StreamOptions mStreamOptions;

public:
    virtual ~ResponseData() = default;

    [[nodiscard]] virtual ResponseData* clone() const { return new ResponseData{*this}; }

    [[nodiscard]] bool operator==(const ResponseData& that) const
    {
        return metadata() == that.metadata() && model() == that.model()
               && isStreaming() == that.isStreaming() && streamOptions() == that.streamOptions();
    }

    [[nodiscard]] QString id() const { return mId; }
    bool setId(const QString& id)
    {
        if (mId == id)
            return false;
        mId = id;
        return true;
    }
    void resetId() { setId({}); }

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

    [[nodiscard]] QString model() const { return mModel; }
    bool setModel(const QString& model)
    {
        if (mModel == model)
            return false;
        mModel = model;
        return true;
    }
    void resetModel() { setModel({}); }

    [[nodiscard]] bool isStreaming() const { return mStreaming; }
    bool setStreaming(bool streaming)
    {
        if (mStreaming == streaming)
            return false;
        mStreaming = streaming;
        return true;
    }
    void resetStreaming() { setStreaming(false); }

    [[nodiscard]] StreamOptions streamOptions() const { return mStreamOptions; }
    bool setStreamOptions(const StreamOptions& streamOptions)
    {
        if (mStreamOptions == streamOptions)
            return false;
        mStreamOptions = streamOptions;
        return true;
    }
    void resetStreamOptions() { setStreamOptions({}); }

    QJsonObject toJson(bool full = false) const
    {
        QJsonObject json;
        return writeJson(json, full) ? json : QJsonObject{};
    }
    QString formattedJson(bool full = false) const { return QJsonDocument{toJson(full)}.toJson(); }

    // protected:
    virtual bool readJson(const QJsonObject& json, QStringList* errors = nullptr);
    virtual bool writeJson(QJsonObject& json, bool full = false) const;
};

class Response : public QObject
{
    Q_OBJECT

public:
    enum Attribute { IdAttribute, NumAttributes };
    Q_ENUM(Attribute)

    virtual ~Response();

    [[nodiscard]] Error error() const { return mError; }

    void abort()
    {
        if (mReply)
            mReply->abort();
    }

    [[nodiscard]] bool isRunning() const { return mReply ? mReply->isRunning() : false; }
    [[nodiscard]] bool isFinished() const { return mReply ? mReply->isFinished() : false; }

    [[nodiscard]] Client* client() const { return mClient; }
    [[nodiscard]] QNetworkReply* reply() const { return mReply; }
    [[nodiscard]] const Request& request() const { return mRequest; }

    [[nodiscard]] QString id() const { return mId; }
    bool setId(const QString& id)
    {
        if (mId == id)
            return false;
        mId = id;
        emit idChanged(QPrivateSignal{});
        return true;
    }
    bool resetId() { return setId({}); }

    [[nodiscard]] QJsonObject extra() const { return mExtra; }

    QJsonObject toJson() const
    {
        QJsonObject json;
        return writeJson(json) ? json : QJsonObject{};
    }
    QByteArray prettyJson() const { return QJsonDocument{toJson()}.toJson(); }

signals:
    void requestSent(QPrivateSignal);
    void readyRead(QPrivateSignal);
    void finished(QPrivateSignal);
    void errorOccurred(const ai::Error& error, QPrivateSignal);

    void idChanged(QPrivateSignal);

protected:
    Response(const Request& request, QNetworkReply* reply, Client* client);

    [[nodiscard]] QJsonObject& extra() { return mExtra; }

    void setError(const Error& error);

    void reset(const Request& request, QNetworkReply* reply, Client* client = nullptr);

    virtual bool readJson(const QJsonObject& json, QStringList* errors = nullptr);
    virtual bool writeJson(QJsonObject& json, bool full = false) const;

    void handleRequestSent();
    void handleReadyRead();
    void handleFinished();
    void handleErrorOccurred(QNetworkReply::NetworkError error);
    void handleSslErrors(const QList<QSslError>& errors);

    QJsonObject mExtra;
    QString mId;
    Request mRequest;
    Error mError;
    QNetworkReply* mReply = nullptr;
    Client* mClient = nullptr;

    friend class Client;
};

} // namespace ai

#endif // AI_RESPONSE_H
