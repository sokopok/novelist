#ifndef LIBAI_RESPONSE_H
#define LIBAI_RESPONSE_H

#include "request.h"
#include "responseutils.h"

#include <QNetworkReply>
#include <QObject>

class QNetworkAccessManager;
class QNetworkRequest;
class QNetworkReply;

namespace ai {

class Response : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(Response)
    QML_UNCREATABLE("Response is created internally")
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged FINAL)
    Q_PROPERTY(bool isRunning READ isRunning NOTIFY runningChanged FINAL)
    Q_PROPERTY(bool isFinished READ isFinished NOTIFY finishedChanged FINAL)
    Q_PROPERTY(Client* client READ client CONSTANT FINAL)
    Q_PROPERTY(Request request READ request CONSTANT FINAL)

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
    [[nodiscard]] bool isFinished() const { return mReply ? mReply->isFinished() : true; }

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
    void runningChanged(QPrivateSignal);
    void finishedChanged(QPrivateSignal);

protected:
    Response(const Request& request, QNetworkReply* reply, Client* client);

    [[nodiscard]] QJsonObject& extra() { return mExtra; }

    void clearError() { setError({}); }
    void setError(const Error& error);

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

#endif // LIBAI_RESPONSE_H
