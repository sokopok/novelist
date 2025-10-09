#include "client.h"
#include "response.h"

namespace ai {

Client::Client(QObject *parent)
    : Client{new RequestData, parent}
{}

Client::Client(RequestData *requestData, QObject *parent)
    : QObject{parent}
    , d{requestData ? requestData : new RequestData}
{}

Client::~Client()
{
    delete d;
}

Client *Client::create(QObject *parent)
{
    Client *client = new Client{parent};
    client->initialize();
    return client;
}

bool Client::prepareRequest(Request *request)
{
    if (!request->isExplicit(Request::UrlAttribute)) {
        if (d->isExplicit(Request::UrlAttribute))
            request->setUrl(apiUrl());
        else {
            setError({Error::InternalErrorType, Error::InternalError, "prepareRequest", "url"});
            return false;
        }
    }

    if (!request->isExplicit(Request::ApiKeyAttribute)) {
        if (d->isExplicit(Request::ApiKeyAttribute))
            request->setApiKey(apiKey());
        else {
            setError({Error::InternalErrorType, Error::InternalError, "prepareRequest", "apiKey"});
            return false;
        }
    }

    if (!request->isExplicit(Request::MetadataAttribute)) {
        if (d->isExplicit(Request::MetadataAttribute))
            request->setMetadata(metadata());
    } else if (d->isExplicit(Request::MetadataAttribute)) {
        auto md = metadata();
        for (auto it = request->metadata().begin(), end = request->metadata().end(); it != end; ++it)
            md[it.key()] = it.value();
        request->setMetadata(md);
    }

    if (!request->isExplicit(Request::ModelAttribute)) {
        if (d->isExplicit(Request::ModelAttribute))
            request->setModel(model());
        else {
            setError({Error::InternalErrorType, Error::InternalError, "prepareRequest", "model"});
            return false;
        }
    }

    if (!request->isExplicit(Request::StreamingAttribute)) {
        if (d->isExplicit(Request::StreamingAttribute))
            request->setStreaming(isStreaming());
        else {
            setError({Error::InternalErrorType, Error::InternalError, "prepareRequest", "stream"});
            return false;
        }
    }

    if (!request->isExplicit(Request::StreamOptionsAttribute)
        && d->isExplicit(Request::StreamOptionsAttribute))
        request->setStreamOptions(streamOptions());

    return true;
}

[[nodiscard]] bool Client::validateRequest(const Request &request) const
{
    if (request.url().isEmpty() || !request.url().isValid()) {
        return false;
    }

    if (request.apiKey().isEmpty()) {
        return false;
    }

    if (request.model().isEmpty()) {
        return false;
    }

    if (!request.streamOptions().isValid()) {
        return false;
    }

    return true;
}

void Client::setError(const Error &error)
{
    mError = error;
    if (mError.code() != Error::NoError) {
        // qCWarning(LOGAI)
        //     << "ERROR!"
        //     << mError.type()
        //     << mError.code()
        //     << mError.message()
        //     << mError.param();
        emit errorOccurred(mError, QPrivateSignal{});
    }
}

void Client::initialize()
{
    resetNetworkAccessManager();
    resetTokenProvider();
    resetApiKey();
    resetApiUrl();
    resetMetadata();
    resetModel();
    resetStreaming();
    resetStreamOptions();

    // setApiUrl(QUrl{"https://api.openai.com/v1/responses"});
    // setApiKey(QByteArray{"sk-proj-BIMS9hXqa-TurELZofPOGNECAULkl3f2L3atzXyaeXDU1uVVCvBb0Txg4sBH_"
    //                      "KQOL4kVZaWMXvT3BlbkFJW0NTHPaxqjSjvqfbDGAE7_xSOFurIWZ61iq4pTp-"
    //                      "8tS9Qe0bLHSjlATLLfhtt8A7oz2ujE9aYA"});
}

// Response *Client::post(const Request &request, QIODevice *device)
// {
//     if (auto *network = networkAccessManager()) {
//         Request r;

//         if (!prepareRequest(r, request)) {
//             return nullptr;
//         }

//         if (!validateRequest(r)) {
//             return nullptr;
//         }

//         qDebug() << "BEFORE REAL POST" << r.url() << r.toJson();
//         return new Response{r, network->post(r, device), this};
//     }

//     return nullptr;
// }

QMap<QString, Request *> Client::pendingRequests() const
{
    return mPendingRequests;
}

QMap<QString, Request *> &Client::pendingRequests()
{
    return mPendingRequests;
}

void Client::addRecycledRequest(Request *request)
{
    if (!request) {
        qWarning() << "No request";
        return;
    }
    recycledRequests().append(request);
}

QList<Request *> Client::recycledRequests() const
{
    return mRecycledRequests;
}

QList<Request *> &Client::recycledRequests()
{
    return mRecycledRequests;
}

} // namespace ai
