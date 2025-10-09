#include "response.h"
#include "client.h"
#include "config.h"

namespace ai {

bool ResponseData::readJson(const QJsonObject& json, QStringList* errors)
{
    mExtra = json;

    if (mExtra.contains(QStringLiteral("id"))) {
        if (const auto v = mExtra.value(QStringLiteral("id")); v.isString()) {
            setId(v.toString());
            mExtra.remove(QStringLiteral("id"));
        } else if (errors) {
            errors->append(QStringLiteral("id is not a string"));
            return false;
        } else
            return false;
    }

    if (mExtra.contains(QStringLiteral("metadata"))) {
        if (const auto v = mExtra.value(QStringLiteral("metadata")); v.isObject()) {
            setMetadata(v.toObject().toVariantMap());
            mExtra.remove(QStringLiteral("metadata"));
        } else if (errors) {
            errors->append(QStringLiteral("metadata is not an object"));
            return false;
        } else
            return false;
    }

    if (mExtra.contains(QStringLiteral("model"))) {
        if (const auto v = mExtra.value(QStringLiteral("model")); v.isString()) {
            setModel(v.toString());
            mExtra.remove(QStringLiteral("model"));
        } else if (errors) {
            errors->append(QStringLiteral("model is not a string"));
            return false;
        } else
            return false;
    }

    if (mExtra.contains(QStringLiteral("stream"))) {
        if (const auto v = mExtra.value(QStringLiteral("stream")); v.isBool()) {
            setStreaming(v.toBool());
            mExtra.remove(QStringLiteral("stream"));
        } else if (errors) {
            errors->append(QStringLiteral("stream is not a boolean"));
            return false;
        } else
            return false;
    }

    if (mExtra.contains(QStringLiteral("stream_options"))) {
        if (const auto v = mExtra.value(QStringLiteral("stream_options")); v.isObject()) {
            setStreamOptions(StreamOptions::fromJson(v.toObject()));
            mExtra.remove(QStringLiteral("stream_options"));
        } else if (errors) {
            errors->append(QStringLiteral("stream_options is not an object"));
            return false;
        } else
            return false;
    }

    return true;
}

bool ResponseData::writeJson(QJsonObject& json, bool full) const
{
    if (full || !id().isEmpty())
        json[QStringLiteral("id")] = id();

    if (full || !metadata().isEmpty())
        json[QStringLiteral("metadata")] = QJsonObject::fromVariantMap(metadata());

    if (full || !model().isEmpty())
        json[QStringLiteral("model")] = model();

    if (full || isStreaming()) {
        json[QStringLiteral("streaming")] = isStreaming();

        if (full || !streamOptions().isEmpty())
            json[QStringLiteral("stream_options")] = streamOptions().toJson();
    }

    return true;
}

Response::Response(const Request& request, QNetworkReply* reply, Client* client)
    : Response{new ResponseData, request, reply, client}
{
}

Response::Response(ResponseData* data, const Request& request, QNetworkReply* reply, Client* client)
    : d{data ? data : new ResponseData}
{
    reset(request, reply, client);
}

void Response::setError(const Error& error)
{
    mError = error;
    if (mError.code() != Error::NoError) {
        // qWarning()
        //     << "ERROR!"
        //     << mError.type()
        //     << mError.code()
        //     << mError.message()
        //     << mError.param();
        emit errorOccurred(mError, QPrivateSignal{});
    }
}

void Response::reset(const Request& request, QNetworkReply* reply, Client* client)
{
    abort();

    if (client) {
        if (mClient)
            mClient->disconnect(this);

        mClient = client;

        // connect(mClient, &Client::networkAccessManagerChanged, this, &Response::handleFinished);

        if (!parent())
            setParent(client);
    }

    mRequest = request;

    if (mReply)
        mReply->disconnect(this);

    mReply = reply;

    if (mReply)
        connect(mReply, &QObject::destroyed, this, [this]() { mReply = nullptr; });

    if (mReply) {
        if (mSetParentToReply)
            setParent(mReply);

        connect(mReply, &QNetworkReply::errorOccurred, this, &Response::handleErrorOccurred);
        connect(mReply, &QNetworkReply::requestSent, this, &Response::handleRequestSent);
        connect(mReply, &QNetworkReply::finished, this, &Response::handleFinished);
        connect(mReply, &QNetworkReply::readyRead, this, &Response::handleReadyRead);
    }
}

bool Response::readJson(const QJsonObject& json, QStringList* errors)
{
    if (d->readJson(json, errors))
        return true;

    if (auto error = Error::fromJson(json); error.isError()) {
        setError(error);
        return true;
    }

    if (auto error = Error::fromJson(json.value(QStringLiteral("error")).toObject());
        error.isError()) {
        setError(error);
        return true;
    }

    return false;
}

bool Response::writeJson(QJsonObject& json, bool full) const
{
    if (!mError.isEmpty()) {
        json["error"] = mError.toJson();
        return true;
    }
    return d->writeJson(json, full);
}

void Response::handleRequestSent()
{
    // qWarning() << "handleRequestSent()" << mRequest.toJson();
    emit requestSent(QPrivateSignal{});
}

void Response::handleReadyRead()
{
    // qWarning() << "handleReadyRead()";
    emit readyRead(QPrivateSignal{});
}

void Response::handleFinished()
{
    // qWarning() << "handleFinished()";

    if (!mReply) {
        qWarning() << "Reply is null";
        return;
    }

    QJsonDocument doc;

    const auto data = mReply->readAll();

    // qDebug() << "DATA FROM SERVER:" << data;

    doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) {
        qWarning() << "Failed to parse response data to json: " << data;

        if (!mError.isEmpty()) {
            setError({Error::UnknownErrorType, Error::UnknownError, mError.message()});
            doc = QJsonDocument{mError.toJson()};
        }
    }

    const auto json = doc.object();

    qDebug().noquote() << QJsonDocument{json}.toJson();

    QStringList errors;
    if (!readJson(json, &errors)) {
        setError({Error::InternalErrorType, Error::InternalError, ""});
    }

    // if (!readJson(json))
    //     qWarning() << "Failed to parse response json to response";

    qDebug().noquote() << /*"FINAL RESPONSE JSON:" <<*/ QJsonDocument{toJson()}.toJson();

    emit finished(QPrivateSignal{});

    if (mDeleteReplyWhenFinished) {
        mReply->deleteLater();
        mReply = nullptr;
    }
}

void Response::handleErrorOccurred(QNetworkReply::NetworkError error)
{
    // qWarning() << "handleErrorOccurred()" << error;
    setError({Error::NetworkErrorType,
              Error::NetworkError,
              mReply ? mReply->errorString()
                     : QMetaEnum::fromType<QNetworkReply::NetworkError>().valueToKey(error)});
}

void Response::handleSslErrors(const QList<QSslError>& errors)
{
    // qWarning() << "handleSslErrors()" << errors;>
    QStringList list;
    for (const auto& e : errors)
        list.append(QStringLiteral("%1 (%2)").arg(e.errorString()).arg(e.error()));
    setError({Error::NetworkErrorType, Error::SslError, list.join("; ")});
}

} // namespace ai
