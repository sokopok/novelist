#include "client.h"
#include "logging.h"
#include "response.h"

namespace ai {

Client::Client(QObject *parent)
    : QObject{parent}
{}

Response *Client::post(const Request &request, QIODevice *device)
{
    if (auto *network = networkAccessManager())
        return new Response{request, network->post(request, device), this};
    return nullptr;
}

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
