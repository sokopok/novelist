#include "request.h"
#include "client.h"
#include "logging.h"

namespace ai {

// bool Request::start()
// {
//     auto* network = networkAccessManager();
//     if (!network) {
//         qCWarning(LOGAI) << "No networkAccessManager";
//         return false;
//     }

//     const auto json = requestData().toJson();

//     const QByteArray data = QJsonDocument{json}.toJson(QJsonDocument::Compact);

//     mReply = network->post(mRequest, data);

//     connect(mReply, &QNetworkReply::requestSent, this, &Request::handleReplyRequestSent);
//     connect(mReply, &QNetworkReply::readyRead, this, &Request::handleReplyReadyRead);
//     connect(mReply, &QNetworkReply::finished, this, &Request::handleReplyFinished);
//     connect(mReply, &QNetworkReply::errorOccurred, this, &Request::handleReplyErrorOccurred);
//     connect(mReply, &QNetworkReply::sslErrors, this, &Request::handleReplySslErrors);

//     return true;
// }

// void Request::abort()
// {
//     if (mReply)
//         mReply->abort();
// }

// bool Request::reset(const QVariantMap& input)
// {
//     abort();
//     return true;
// }

bool RequestData::readJson(const QJsonObject& json)
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

bool RequestData::writeJson(QJsonObject& json, bool full) const
{
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

Request::Request()
    : Request(new RequestData)
{}

Request::Request(RequestData* data)
    : d{data ? data : new RequestData}
{
    setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    setRawHeader("Authorization", "Bearer " + apiKey());

    setRawHeader("Accept", isStreaming() ? "text/event-stream" : "application/json");

#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
    setTransferTimeout(isStreaming() ? 0 : 60000);
#endif
}

} // namespace ai
