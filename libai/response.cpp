#include "response.h"
#include "client.h"
#include <QSharedData>
#include <utility>

namespace ai {

bool Response::readJson(const QJsonObject& json, QStringList* errors)
{
    mExtra = json;

    if (mExtra.contains(QStringLiteral("id"))) {
        if (const auto v = mExtra.value(QStringLiteral("id")); v.isString()) {
            setId(v.toString());
            mExtra.remove(QStringLiteral("id"));
        } else {
            if (errors)
                errors->append(QStringLiteral("'id' is not a string"));
            return false;
        }
    }

    if (mExtra.contains(QStringLiteral("error"))) {
        if (const auto v = mExtra.value(QStringLiteral("error")); v.isObject()) {
            setError(Error::fromJson(v.toObject()));
            mExtra.remove(QStringLiteral("error"));
        } else if (!v.isNull()) {
            if (errors)
                errors->append(QStringLiteral("'error' is not an object"));
            return false;
        }
    }

    return true;
}

bool Response::writeJson(QJsonObject& json, bool full) const
{
    if (!mError.isEmpty()) {
        json["error"] = mError.toJson();

        if (!full)
            return true;
    }

    if (full || !mId.isEmpty())
        json[QStringLiteral("id")] = mId;

    return true;
}

Response::Response(const Request &request, QNetworkReply *reply, Client *client)
    : QObject{client}
    , mRequest{request}
    , mReply{reply}
    , mClient{client}
{
    if (mClient) {
        // if (!parent())
        //     setParent(client);
    }

    if (mReply) {
        connect(mReply, &QNetworkReply::destroyed, this, [this]() { mReply = nullptr; });
        connect(mReply, &QNetworkReply::errorOccurred, this, &Response::handleErrorOccurred);
        connect(mReply, &QNetworkReply::requestSent, this, &Response::handleRequestSent);
        connect(mReply, &QNetworkReply::finished, this, &Response::handleFinished);
        connect(mReply, &QNetworkReply::readyRead, this, &Response::handleReadyRead);
    }
}

Response::~Response()
{
}

void Response::setError(const Error& error)
{
    mError = error;
    if (mError.code() != Error::NoError) {
        emit errorOccurred(mError, QPrivateSignal{});
    }
}

void Response::handleRequestSent()
{
    emit requestSent(QPrivateSignal{});
}

void Response::handleReadyRead()
{
    emit readyRead(QPrivateSignal{});
}

void Response::handleFinished()
{
    if (!mReply) {
        setError({Error::InternalErrorType,
                  Error::InternalError,
                  QStringLiteral("handleFinished: Reply is null")});
        return;
    }

    QJsonDocument doc;

    const auto data = mReply->readAll();

    qDebug().noquote().nospace() << "RECEIVE: " << data;

    doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) {
        setError({Error::InternalErrorType, Error::InternalError, "Failed to parse response data"});
        return;
    }

    const auto json = doc.object();

    // qDebug().noquote() << QJsonDocument{json}.toJson();

    QStringList errors;
    if (!readJson(json, &errors)) {
        setError({Error::InternalErrorType, Error::InternalError, errors.join("\n")});
    }

    qDebug().noquote().nospace() << "RESPONSE: " << prettyJson();

    emit finished(QPrivateSignal{});
}

void Response::handleErrorOccurred(QNetworkReply::NetworkError error)
{
    const auto e = QMetaEnum::fromType<QNetworkReply::NetworkError>().valueToKey(error);
    setError({Error::NetworkErrorType,
              Error::NetworkError,
              mReply ? QStringLiteral("%1: %2").arg(e).arg(mReply->errorString()) : e});
}

void Response::handleSslErrors(const QList<QSslError>& errors)
{
    // qWarning() << "handleSslErrors()" << errors;>
    QStringList list;
    for (const auto& e : errors)
        list.append(QStringLiteral("%1: %2").arg(e.error()).arg(e.errorString()));
    setError({Error::NetworkErrorType, Error::SslError, list.join("\n")});
}

} // namespace ai
