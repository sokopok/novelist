#include "response.h"
#include "client.h"
#include "logging.h"

namespace ai {

bool ResponseData::readJson(const QJsonObject& json)
{
    if (const auto v = json.value("metadata"); v.isObject())
        setMetadata(v.toObject().toVariantMap());

    if (const auto v = json.value("model"); v.isString())
        setModel(v.toString());

    if (const auto v = json.value("stream"); v.isBool())
        setStreaming(v.toBool());

    if (const auto v = json.value("stream_options"); v.isObject())
        setStreamOptions(StreamOptions::fromJson(v.toObject()));

    return true;
}

bool ResponseData::writeJson(QJsonObject& json) const
{
    if (!metadata().isEmpty())
        json[QStringLiteral("metadata")] = QJsonObject::fromVariantMap(metadata());

    if (!model().isEmpty())
        json[QStringLiteral("model")] = model();

    if (isStreaming()) {
        json[QStringLiteral("streaming")] = isStreaming();

        if (!streamOptions().isEmpty())
            json[QStringLiteral("stream_options")] = streamOptions().toJson();
    }

    return true;
}

Response::Response(const Request& request, QNetworkReply* reply, Client* client)
    : Response{new ResponseData, request, reply, client}
{
}

Response::Response(ResponseData* data, const Request& request, QNetworkReply* reply, Client* client)
    : d{data}
{
    reset(request, reply, client);
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

    if (mReply) {
        if (mSetParentToReply)
            setParent(mReply);

        connect(mReply, &QNetworkReply::errorOccurred, this, &Response::handleErrorOccurred);
        connect(mReply, &QNetworkReply::requestSent, this, &Response::handleRequestSent);
        connect(mReply, &QNetworkReply::finished, this, &Response::handleFinished);
        connect(mReply, &QNetworkReply::readyRead, this, &Response::handleReadyRead);
    }
}

void Response::handleRequestSent()
{
    qCWarning(LOGAI) << "handleRequestSent()";
    emit requestSent(QPrivateSignal{});
}

void Response::handleReadyRead()
{
    qCWarning(LOGAI) << "handleReadyRead()";
    emit readyRead(QPrivateSignal{});
}

void Response::handleFinished()
{
    qCWarning(LOGAI) << "handleFinished()";

    if (!mReply) {
        qCWarning(LOGAI) << "Reply is null";
        return;
    }

    const auto doc = QJsonDocument::fromJson(mReply->readAll());
    if (!doc.isObject()) {
        qCWarning(LOGAI) << "Failed to parse response data to json";
        return;
    }

    const auto json = doc.object();

    if (!readJson(json))
        qCWarning(LOGAI) << "Failed to parse response json to response";

    emit finished(QPrivateSignal{});

    if (mDeleteReplyWhenFinished) {
        mReply->deleteLater();
        mReply = nullptr;
    }
}

void Response::handleErrorOccurred(QNetworkReply::NetworkError error)
{
    qCWarning(LOGAI) << "handleErrorOccurred()" << error << mReply->errorString();
    emit errorOccurred(NetworkError,
                       QStringLiteral("%1 (%2)").arg(mReply->errorString()).arg(error),
                       QPrivateSignal{});
}

void Response::handleSslErrors(const QList<QSslError>& errors)
{
    qCWarning(LOGAI) << "handleSslErrors()" << errors;
    QStringList list;
    for (const auto& e : errors)
        list.append(QStringLiteral("%1 (%2)").arg(e.errorString()).arg(e.error()));
    emit errorOccurred(SslError, list.join("; "), QPrivateSignal{});
}

} // namespace ai
