#include "client.h"
#include "logging.h"
#include "response.h"

namespace ai {

Client::Client(QObject *parent)
    : Client{new RequestData, parent}
{}

Client::Client(RequestData *requestData, QObject *parent)
    : QObject{parent}
    , d{requestData ? requestData : new RequestData}
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

bool Client::prepareRequest(Request &prep, const Request &request) const
{
    prep.setUrl(request.url().isEmpty() ? apiUrl() : request.url());
    prep.setApiKey(request.apiKey().isEmpty() ? apiKey() : request.apiKey());
    prep.setMetadata(metadata());
    prep.putMetadata(request.metadata());
    prep.setModel(request.model().isEmpty() ? model() : request.model());
    prep.setStreaming(request.isStreaming());
    prep.setStreamOptions(request.streamOptions().isEmpty() ? streamOptions()
                                                            : request.streamOptions());
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
        qCWarning(LOGAI) << "No request";
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
