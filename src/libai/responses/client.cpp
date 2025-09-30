#include "client.h"
#include "response.h"

namespace ai::responses {

Client::Client(QObject *parent)
    : Client{new RequestData, parent}
{}

Client::Client(RequestData *data, QObject *parent)
    : ai::Client{data ? data : new RequestData, parent}
{
    resetApiKey();
    resetApiUrl();
    resetMetadata();
    resetModel();
    resetStreaming();
    resetStreamOptions();
}

Response *Client::post(const Request &request, QIODevice *device)
{
    auto *network = networkAccessManager();
    if (!network) {
        setError({Error::InternalErrorType, Error::InternalError, "No networkAccessManager"});
        return nullptr;
    }

    Request r;

    if (!prepareRequest(r, request)) {
        setError({Error::InternalErrorType, Error::InternalError, "Couldn't prepare request"});
        return nullptr;
    }

    if (!validateRequest(r)) {
        setError({Error::InternalErrorType, Error::InternalError, "Couldn't validate request"});
        return nullptr;
    }

    const auto data = QJsonDocument{r.toJson()}.toJson();

    qDebug().noquote().nospace() << toJson(true);
    qDebug().noquote().nospace() << r.url().toString() << '\n' << data;

    return new Response{r, network->post(r, data), this};
}

bool Client::validateRequest(const Request &request) const
{
    if (!ai::Client::validateRequest(request))
        return false;

    if (!request.conversation().isValid()) {
        return false;
    }

    if (!request.input().isValid()) {
        return false;
    }

    return true;
}

} // namespace ai::responses
